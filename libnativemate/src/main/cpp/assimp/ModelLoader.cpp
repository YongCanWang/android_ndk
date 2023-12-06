//
// Created by Tom灿 on 2023/12/6.
//

#include "ModelLoader.h"
#include "core/AssimpMate.h"
#include "core/GLMMate.h"
#include "gles/GLESMate.h"
#include "jni.h"
#include "../utils/LogUtil.h"


ModelLoader::ModelLoader() {
    assimpMate = new AssimpMate();
    glmMate = new GLMMate();
    glesMate = new GLESMate();
}

void ModelLoader::init(std::string modelPath) {
//    float pos[] = {0., 0., 0., 0.2, 0.5, 0.};
    float pos[] = {0., 0., 0., 0.2, 1, 1};
    std::copy(&pos[0], &pos[5], std::back_inserter(modelDefaultPosition));
    glesMate->init();
    glmMate->SetModelPosition(modelDefaultPosition);
    if (assimpMate != nullptr) {
        assimpMate->init(modelPath);
    }
}

void ModelLoader::setModelPath(std::string modelPath) {
    assimpMate->init(modelPath);
}


void ModelLoader::ReadModel() {
    assimpMate->ReadModel();
}


void ModelLoader::Viewport(int width, int height) {
    screenWidth = width;
    screenHeight = height;
    glesMate->Viewport(width, height);
    glmMate->SetAspectRatio((float) width / height);
}

void ModelLoader::Render3DModel() {
    glm::mat4 mvpMat = glmMate->GetMVP();
    assimpMate->Render3DModel(&mvpMat);
}


/**
 * rotate the model if user scrolls with one finger
 * 如果用户用一个手指滚动，则旋转模型
 */
void ModelLoader::ScrollAction(float distanceX, float distanceY, float positionX, float positionY) {
    // normalize movements on the screen wrt GL surface dimensions
    // invert dY to be consistent with GLES conventions
    float dX = (float) distanceX / screenWidth;
    float dY = -(float) distanceY / screenHeight;
    float posX = 2 * positionX / screenWidth - 1.;
    float posY = -2 * positionY / screenHeight + 1.;
    posX = fmax(-1., fmin(1., posX));
    posY = fmax(-1., fmin(1., posY));
    glmMate->RotateModel(dX, dY, posX, posY);
}

/**
 * pinch-zoom: move the model closer or farther away
 * 缩放:将模型移近或移远
 */
void ModelLoader::ScaleAction(float scaleFactor) {
    glmMate->ScaleModel(scaleFactor);
}


/**
 * two-finger drag: displace the model by changing its x-y coordinates
 * 两指拖动:通过改变模型的x-y坐标来移动模型
 */
void ModelLoader::MoveAction(float distanceX, float distanceY) {
    // normalize movements on the screen wrt GL surface dimensions
    // invert dY to be consistent with GLES conventions
    float dX = distanceX / screenWidth;
    float dY = -distanceY / screenHeight;
    glmMate->TranslateModel(dX, dY);
}


/**
 * reset model's position in double-tap
 * 双击重置模型位置
 */
void ModelLoader::DoubleTapAction() {
    glmMate->SetModelPosition(modelDefaultPosition);
}