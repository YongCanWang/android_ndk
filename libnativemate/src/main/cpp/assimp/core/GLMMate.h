//
// Created by Tom灿 on 2023/12/4.
//

#ifndef ANDROID_JNI_GLMMATE_H
#define ANDROID_JNI_GLMMATE_H

#include"string"
#include "ext/quaternion_float.hpp"

// sensitivity coefficients for translating gestures to model's movements
#define SCALE_TO_Z_TRANSLATION  200
#define TRANSLATION_TO_ANGLE    5
#define XY_TRANSLATION_FACTOR   100

class GLMMate {
    const std::string TAG_GLMMate = "GLMMate-->";
public:
    GLMMate(
            float FOV = 45,          // in degrees
            float zPosition = 500,    // camera's location on Z axis  相机在Z轴上的位置
            float nearPlaneDistance = 1.0f, // as large as possible
            float farPlaneDistance = 2000.0f // as small as possible
    );

    glm::mat4 GetMVP() { return mvpMat; }


    void SetAspectRatio(float aspect);

    void setVewport(float aspect);


    void SetModelPosition(std::vector<float> modelPosition);

    void TranslateModel(float distanceX, float distanceY);

    void ScaleModel(float scaleFactor);

    void RotateModel(float distanceX, float distanceY, float endPositionX, float endPositionY);


    void lookAt(std::vector<float> viewPosition);

    void scaleViewPosition(float scaleFactor);


    void setViewModelPosition(std::vector<float> viewModelPosition);

    void setViewModelPosition_Factor(std::vector<float> viewModelPosition);

    void translateViewModel(float distanceX, float distanceY);

    void scaleViewModel(float scaleFactor);


    void setViewPosition(std::vector<float> viewPosition);

    void translateView(float distanceX, float distanceY);

    void scaleView(float scaleFactor);


    void translateMethod();

    void rotateMethod();

    void scaleMethod();

private:

    void ComputeMVPMatrix();

    float FOV;
    float nearPlaneDistance, farPlaneDistance;
    // six degrees-of-freedom of the model contained in a quaternion and x-y-z coordinates
    glm::quat modelQuaternion;
    float translateX = 0, translateY = 0, translateZ = 0;
    float degrees = 0.0;
    float scale = 0.5;
    float deltaX, deltaY, deltaZ;
    float viewX = 0., viewY = 0., viewZ = 0.;


    glm::mat4 translateMat, rotateMat, scaleMat;  // 平移、旋转、缩放矩阵
    glm::mat4 modelMat;   //  模型矩阵:平移*旋转相乘后的矩阵
    glm::mat4 viewMat;    // 相机视图矩阵
    glm::mat4 projectionMat;  // 投影矩阵
    glm::mat4 projectionViewMat;  // 投影矩阵*相机视图矩阵
    glm::mat4 mvpMat;     // ModelViewProjection: obtained by multiplying Projection, View, & Model


};


#endif //ANDROID_JNI_GLMMATE_H
