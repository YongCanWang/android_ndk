//
// Created by Tom灿 on 2023/12/6.
//

#ifndef ANDROID_JNI_MODELLOADER_H
#define ANDROID_JNI_MODELLOADER_H

#include "core/AssimpMate.h"
#include "core/GLMMate.h"
#include "gles/GLESMate.h"


class ModelLoader {
private:
    AssimpMate *assimpMate = nullptr;
    GLMMate *glmMate = nullptr;
    GLESMate *glesMate;
    std::vector<float> modelDefaultPosition;
    int screenWidth;
    int screenHeight;

public:
    ModelLoader();

    void init(std::string);

    void setModelPath(std::string);

    void ReadModel();

    void Viewport(int width, int height);

    void Render3DModel();

    void ScrollAction(float distanceX, float distanceY, float positionX, float positionY);

    void ScaleAction(float scaleFactor);

    void MoveAction(float distanceX, float distanceY);

    void DoubleTapAction();

};


#endif //ANDROID_JNI_MODELLOADER_H
