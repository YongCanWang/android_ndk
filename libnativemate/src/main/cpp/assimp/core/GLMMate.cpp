//
// Created by Tom灿 on 2023/12/4.
//

#include "GLMMate.h"
#include <vector>
#include "ext/quaternion_float.hpp"
#include "ext/quaternion_trigonometric.hpp"
#include "gtx/quaternion.hpp"
#include "../../utils/LogUtil.h"


GLMMate::GLMMate(
        float FOV,
        float zPosition,
        float nearPlaneDistance,
        float farPlaneDistance) {

    // camera position is fixed
    glm::vec3 cameraPosition = glm::vec3(viewX, viewY, viewZ);
    viewMat = glm::lookAt(cameraPosition,        // Camera location in World Space  摄像机在世界空间中的位置
                          glm::vec3(0, 0,
                                    -1),   // direction in which camera it is pointed 相机指向的方向-世界坐标系的z轴负方向
                          glm::vec3(0, 1, 0));   // camera is pointing up  摄像机指向上方-世界坐标系的y轴正方向


    this->nearPlaneDistance = nearPlaneDistance;
    this->farPlaneDistance = farPlaneDistance;
    this->FOV = FOV;

    // 6DOF describing model's position
    deltaX = deltaY = deltaZ = 0;                  // translations

    modelQuaternion = glm::quat(glm::vec3(0, 0, 0)); // rotation
    translateMat = glm::mat4(1.0f);
    rotateMat = glm::mat4(1.0f);
    scaleMat = glm::mat4(1.0f);
    modelMat = glm::mat4(1.0f);

    mvpMat = glm::mat4(1.0f); // projection is not known -> initialize MVP to identity
}


/**
 * Use the display's aspect ratio to compute projection matrix
 * 使用显示器的宽高比来计算投影矩阵
 */
void GLMMate::SetAspectRatio(float aspect) {

    glm::mat4 projectionMat; // 投影矩阵
    projectionMat = glm::perspective(FOV * float(M_PI / 180), // camera's field-of-view
                                     aspect,                  // camera's aspect ratio
                                     nearPlaneDistance,       // distance to the near plane
                                     farPlaneDistance);       // distance to the far plane
    projectionViewMat = projectionMat * viewMat;  // 投影矩阵与相机视图矩阵相乘
    ComputeMVPMatrix();

}


/**
 * 根据显示器的宽高比来计算投影矩阵
 * @param aspect
 */
void GLMMate::setVewport(float aspect) {
    projectionMat = glm::perspective(FOV * float(M_PI / 180), // camera's field-of-view
                                     aspect,                  // camera's aspect ratio
                                     nearPlaneDistance,       // distance to the near plane
                                     farPlaneDistance);       // distance to the far plane
    ComputeMVPMatrix();
}

/**
 * Model's position has 6 degrees-of-freedom: 3 for x-y-z locations and
 * 3 for alpha-beta-gamma Euler angles
 * Convert euler angles to quaternion and update MVP
 * 模型的位置有6个自由度:3个用于x-y-z位置，3个用于α - β - γ欧拉角转换欧拉角四元数和更新MVP
 */
void GLMMate::SetModelPosition(std::vector<float> modelPosition) {

    deltaX = modelPosition[0];
    deltaY = modelPosition[1];
    deltaZ = modelPosition[2];
    LOGCATI("%s SetModelPosition->deltaX=%f,deltaY=%f,deltaZ=%f", TAG_GLMMate.c_str(), deltaX,
            deltaY,
            deltaZ);
    translateMat = glm::mat4(1, 0, 0, 0,                  // col0
                             0, 1, 0, 0,                  // col1
                             0, 0, 1, 0,                  // col2
                             deltaX, deltaY, deltaZ, 1);  // col3

    float pitchAngle = modelPosition[3];
    float yawAngle = modelPosition[4];
    float rollAngle = modelPosition[5];
    LOGCATI("%s SetModelPosition->pitchAngle=%f,yawAngle=%f,rollAngle=%f", TAG_GLMMate.c_str(),
            pitchAngle, yawAngle,
            rollAngle);
    modelQuaternion = glm::quat(glm::vec3(pitchAngle, yawAngle, rollAngle));
    rotateMat = glm::toMat4(modelQuaternion);

    ComputeMVPMatrix();
}


/**
 * displace model by changing x-y coordinates
 * 通过改变x-y坐标来置换模型
 */
void GLMMate::TranslateModel(float distanceX, float distanceY) {

    deltaX += XY_TRANSLATION_FACTOR * distanceX;
    deltaY += XY_TRANSLATION_FACTOR * distanceY;
    LOGCATI("%s TranslateModel->deltaX=%f,deltaY=%f,deltaZ=%f", TAG_GLMMate.c_str(), deltaX, deltaY,
            deltaZ);
    translateMat = glm::mat4(1, 0, 0, 0,                  // col0
                             0, 1, 0, 0,                  // col1
                             0, 0, 1, 0,                  // col2
                             deltaX, deltaY, deltaZ, 1);  // col3
    ComputeMVPMatrix();
}


/**
 * Simulate change in scale by pushing or pulling the model along Z axis
 * 通过沿Z轴推或拉模型来模拟比例的变化
 */
void GLMMate::ScaleModel(float scaleFactor) {
    deltaZ += SCALE_TO_Z_TRANSLATION * (scaleFactor - 1);
    LOGCATI("%s ScaleModel->deltaX=%f,deltaY=%f,deltaZ=%f", TAG_GLMMate.c_str(), deltaX, deltaY,
            deltaZ);
    translateMat = glm::mat4(1, 0, 0, 0,                  // col0
                             0, 1, 0, 0,                  // col1
                             0, 0, 1, 0,                  // col2
                             deltaX, deltaY, deltaZ, 1);  // col3
    ComputeMVPMatrix();
}

/**
 * Finger drag movements are converted to rotation of model by deriving a
 * quaternion from the drag movement
 * 通过从拖动运动中派生四元数，将手指拖动运动转换为模型的旋转
 */
void GLMMate::RotateModel(float distanceX, float distanceY,
                          float endPositionX, float endPositionY) {

    // algo in brief---
    // assume that a sphere with its center at (0,0), i.e., center of screen, and
    // radius 1 is placed on the device.
    // drag movement on the surface is translated to a drag on the imaginary sphere's surface
    // since we know (x,y) coordinates of the drag, we only need to determine z-coordinate
    // corresponding to the height of sphere's surface corresponding to the drag position.
    // begin and end of drag define two points on sphere and we create two vectors joining those
    // points with the origin (0,0).
    // lastly we create a quaternion responsible for rotation between the two vectors.


    /**
     * 简而言之——假设在设备上放置一个圆心为(0,0)，即屏幕圆心，半径为1的球体。
     * 表面上的拖动运动被转换为虚拟球体表面上的拖动，因为我们知道拖动的(x,y)坐标，我们只需要确定与球体表面高度对应的z坐标。
     * 拖动的开始和结束在球体上定义两个点，我们创建两个向量将这些点与原点(0,0)连接起来。最后，我们创建一个四元数负责两个向量之间的旋转。
     */

    // compute ending vector (using endPositionX, endPositionY)
    float dist = sqrt(fmin(1, endPositionX * endPositionX + endPositionY * endPositionY));
    float positionZ = sqrt(1 - dist * dist);
    glm::vec3 endVec = glm::vec3(endPositionX, endPositionY, positionZ);
    endVec = glm::normalize(endVec);

    // compute starting vector by adding (distanceX, distanceY) to ending positions
    endPositionX += distanceX;
    endPositionY += distanceY;
    dist = sqrt(fmin(1, endPositionX * endPositionX + endPositionY * endPositionY));
    positionZ = sqrt(1 - dist * dist);
    glm::vec3 beginVec = glm::vec3(endPositionX, endPositionY, positionZ);
    beginVec = glm::normalize(beginVec);

    // compute cross product of vectors to find axis of rotation
    glm::vec3 rotationAxis = glm::cross(beginVec, endVec);
    rotationAxis = glm::normalize(rotationAxis);

    // compute angle between vectors using the dot product
    float dotProduct = fmax(fmin(glm::dot(beginVec, endVec), 1.), -1.);
    float rotationAngle = TRANSLATION_TO_ANGLE * acos(dotProduct);

    // compute quat using above
    modelQuaternion = glm::angleAxis(rotationAngle, rotationAxis);
    rotateMat = glm::toMat4(modelQuaternion) * rotateMat;

    ComputeMVPMatrix();
}


/**
 * Compute the translation matrix from x-y-z position and rotation matrix from
 * quaternion describing the rotation
 * MVP = Projection * View * (Translation * Rotation)
 *  从x-y-z位置计算平移矩阵，从描述旋转的四元数计算旋转矩阵MVP =投影*视角*(平移*旋转)
 */
void GLMMate::ComputeMVPMatrix() {
    LOGCATD("%s ComputeMVPMatrix->deltaX=%f,deltaY=%f,deltaZ=%f", TAG_GLMMate.c_str(), deltaX,
            deltaY,
            deltaZ);
    LOGCATD("%s ComputeMVPMatrix->viewX=%f,viewY=%f,viewZ=%f", TAG_GLMMate.c_str(), viewX, viewY,
            viewZ);
    modelMat = translateMat * rotateMat;
    mvpMat = projectionMat * viewMat * modelMat;
}


/**
 * 设置相机位置（视点）
 * @param viewPosition
 */
void GLMMate::lookAt(std::vector<float> viewPosition) {
    viewX = viewPosition[0];
    viewY = viewPosition[1];
    viewZ = viewPosition[2];
    glm::vec3 cameraPosition = glm::vec3(viewX, viewY, viewZ);
    viewMat = glm::lookAt(cameraPosition,        // Camera location in World Space  摄像机在世界空间中的位置
                          glm::vec3(0, 0,
                                    -1),   // direction in which camera it is pointed 相机指向的方向-世界坐标系的z轴负方向
                          glm::vec3(0, 1, 0));   // camera is pointing up  摄像机指向上方-世界坐标系的y轴正方向
}


/**
 * TODO 错误使用
 * 伸缩相机
 * 改变视点z轴的大小(改变视点在z轴上的位置)
 * @param scaleFactor
 */
void GLMMate::scaleViewPosition(float scaleFactor) {
    viewZ += SCALE_TO_Z_TRANSLATION * (scaleFactor - 1);
    LOGCATI("%s scaleViewPosition->viewX=%f,viewY=%f,viewZ=%f", TAG_GLMMate.c_str(), viewX, viewY,
            viewZ);
    float pos[] = {viewX,  // x
                   viewY,  // y
                   viewZ,  // z
    };
    std::vector<float> viewPosition;
    std::copy(&pos[0], &pos[2], std::back_inserter(viewPosition));
    lookAt(viewPosition);
    ComputeMVPMatrix();
}


/**
 * 设置相机位置（视点）-把相机当作模型处理
 * @param viewModelPosition
 */
void GLMMate::setViewModelPosition(std::vector<float> viewModelPosition) {
    viewX = viewModelPosition[0];
    viewY = viewModelPosition[1];
    viewZ = viewModelPosition[2];
    LOGCATI("%s setViewPositionModel->viewX=%f,viewY=%f,viewZ=%f", TAG_GLMMate.c_str(), viewX,
            viewY,
            viewZ);
    viewMat = glm::mat4(1, 0, 0, 0,                  // col0
                        0, 1, 0, 0,                  // col1
                        0, 0, 1, 0,                  // col2
                        viewX, viewY, viewZ, 1);     // col3
    ComputeMVPMatrix();
}


/**
 * 设置相机位置（视点）-把相机当作模型处理
 * @param viewModelPosition
 */
void GLMMate::setViewModelPosition_Factor(std::vector<float> viewModelPosition) {
    viewX += XY_TRANSLATION_FACTOR * viewModelPosition[0];
    viewY += XY_TRANSLATION_FACTOR * viewModelPosition[1];
    viewZ += SCALE_TO_Z_TRANSLATION * (viewModelPosition[2] - 1);
    LOGCATI("%s setViewPositionModel_Factor->viewX=%f,viewY=%f,viewZ=%f", TAG_GLMMate.c_str(),
            viewX, viewY,
            viewZ);
    viewMat = glm::mat4(1, 0, 0, 0,                  // col0
                        0, 1, 0, 0,                  // col1
                        0, 0, 1, 0,                  // col2
                        viewX, viewY, viewZ, 1);     // col3
    ComputeMVPMatrix();
}


/**
 * 平移相机
 * 改变视点x、y轴的大小(改变视点在x、y轴上的位置)-把相机当作模型处理
 * @param distanceX
 * @param distanceY
 */
void GLMMate::translateViewModel(float distanceX, float distanceY) {
    viewX += XY_TRANSLATION_FACTOR * distanceX;
    viewY += XY_TRANSLATION_FACTOR * distanceY;
    LOGCATI("%s translateViewModel->viewX=%f,viewY=%f,viewZ=%f", TAG_GLMMate.c_str(), viewX, viewY,
            viewZ);
    viewMat = glm::mat4(1, 0, 0, 0,                  // col0
                        0, 1, 0, 0,                  // col1
                        0, 0, 1, 0,                  // col2
                        viewX, viewY, viewZ, 1);     // col3

    ComputeMVPMatrix();
}

/**
 * 伸缩相机
 * 改变视点z轴的大小(改变视点在z轴上的位置)-把相机当作模型处理
 * @param scaleFactor
 */
void GLMMate::scaleViewModel(float scaleFactor) {
    viewZ += SCALE_TO_Z_TRANSLATION * (scaleFactor - 1);
    LOGCATI("%s scaleViewModel->viewX=%f,viewY=%f,viewZ=%f", TAG_GLMMate.c_str(), viewX, viewY,
            viewZ);
    viewMat = glm::mat4(1, 0, 0, 0,                  // col0
                        0, 1, 0, 0,                  // col1
                        0, 0, 1, 0,                  // col2
                        viewX, viewY, viewZ, 1);  // col3
    ComputeMVPMatrix();
}


/**
 * 设置相机位置、方向
 * @param viewPosition
 */
void GLMMate::setViewPosition(std::vector<float> viewPosition) {
    viewX = viewPosition[0];
    viewY = viewPosition[1];
    viewZ = viewPosition[2];
    LOGCATI("%s setViewPosition->viewX=%f,viewY=%f,viewZ=%f", TAG_GLMMate.c_str(), viewX, viewY,
            viewZ);
    glm::vec3 cameraPosition = glm::vec3(viewX, viewY, viewZ);
    glm::vec3 cameraFront = glm::vec3(viewPosition[3], viewPosition[4],
                                      viewPosition[5]);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    viewMat = glm::lookAt(cameraPosition,        // Camera location in World Space  摄像机在世界空间中的位置
                          cameraFront,   // direction in which camera it is pointed 相机指向的方向-世界坐标系的z轴负方向
                          cameraUp);   // camera is pointing up  摄像机指向上方-世界坐标系的y轴正方向
    ComputeMVPMatrix();
}


/**
 * 平移相机
 * 改变视点x、y轴的大小(改变视点在x、y轴上的位置)，并同时改变视点的方向
 * @param distanceX
 * @param distanceY
 */
void GLMMate::translateView(float distanceX, float distanceY) {
    viewX += XY_TRANSLATION_FACTOR * distanceX;
    viewY += XY_TRANSLATION_FACTOR * distanceY;
    LOGCATI("%s translateView->viewX=%f,viewY=%f,viewZ=%f", TAG_GLMMate.c_str(), viewX, viewY,
            viewZ);
    glm::vec3 cameraPosition = glm::vec3(-viewX, -viewY, viewZ);  // 正值转为负值，负值转为正值：保证相机移动方向与手指移动方向相反
    glm::vec3 cameraFront = glm::vec3(-viewX, -viewY,
                                      -viewZ); // 相机指向的方向与相机位置一致，这样才不会造成倾斜视角，z轴保持负值，才能保证可以观察到模型(0.0方向)
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    viewMat = glm::lookAt(cameraPosition,        // Camera location in World Space  摄像机在世界空间中的位置
                          cameraFront,   // direction in which camera it is pointed 相机指向的方向-世界坐标系的z轴负方向
                          cameraUp);   // camera is pointing up  摄像机指向上方-世界坐标系的y轴正方向
    ComputeMVPMatrix();
}

/**
 * 伸缩相机
 * 改变视点z轴的大小(改变视点在z轴上的位置)
 * @param scaleFactor
 */
void GLMMate::scaleView(float scaleFactor) {
    LOGCATI("%s scaleView->scaleFactor=%f", TAG_GLMMate.c_str(), scaleFactor);
    viewZ += SCALE_TO_Z_TRANSLATION * (scaleFactor - 1);
    LOGCATI("%s scaleView->viewX=%f,viewY=%f,viewZ=%f", TAG_GLMMate.c_str(), viewX, viewY,
            viewZ);
    glm::vec3 cameraPosition = glm::vec3(-viewX, -viewY, viewZ); // 正值转为负值，负值转为正值：保证相机移动方向与手指移动方向相反
    glm::vec3 cameraFront = glm::vec3(-viewX, -viewY,
                                      -viewZ);  // 相机指向的方向与相机位置一致，这样才不会造成倾斜视角，z轴保持负值，才能保证可以观察到模型(0.0方向)
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    viewMat = glm::lookAt(cameraPosition,        // Camera location in World Space  摄像机在世界空间中的位置
                          cameraFront,   // direction in which camera it is pointed 相机指向的方向-世界坐标系的z轴负方向
                          glm::vec3(0, 1, 0));   // camera is pointing up  摄像机指向上方-世界坐标系的y轴正方向
    ComputeMVPMatrix();
}


/**
 *  平移
 */
void GLMMate::translateMethod() {
//    translateX += 1.0;
//    translateY += 1.0;
//    translateZ += 1.0;
    translateMat = glm::translate(translateMat,
                                  glm::vec3(translateX, translateY, translateZ));
    mvpMat = projectionMat * viewMat * translateMat;
}


/**
 *  旋转
 */
void GLMMate::rotateMethod() {
    degrees = -90.0;
    LOGCATI("%s rotateMethod->degrees=%f", TAG_GLMMate.c_str(), degrees);
    rotateMat = glm::rotate(rotateMat, glm::radians(degrees),  // 逆时针旋转
                            glm::vec3(0.0, 0.0, 1.0));
    LOGCATI("%s rotateMethod->degrees=%f", TAG_GLMMate.c_str(), degrees);
    mvpMat = projectionMat * viewMat * rotateMat;
}


/**
 * 缩放
 */
void GLMMate::scaleMethod() {
//    scale = 0.5; // 缩放0.5倍-缩小0.5倍
    scale = 1.5; // 缩放0.5倍-放大0.5倍
    scaleMat = glm::scale(scaleMat, glm::vec3(scale, scale, scale));
    mvpMat = projectionMat * viewMat * scaleMat;
}




