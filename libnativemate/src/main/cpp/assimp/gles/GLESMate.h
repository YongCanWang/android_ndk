//
// Created by Tom灿 on 2023/12/6.
//

#ifndef ANDROID_JNI_GLESMATE_H
#define ANDROID_JNI_GLESMATE_H

#include <vector>
#include "fwd.hpp"
#include "../../assimp/core/AssimpMate.h"

class GLESMate {

private:
    GLint shaderProgramID;
    GLuint vertexAttribute, vertexUVAttribute;     // attributes for shader variables
    GLint mvpLocation, textureSamplerLocation;    // location of MVP in the shader

public:

    void init();

    void Viewport(int width, int height);

    void CheckGLError(std::string);

    void Render3DModel(std::vector<struct MeshInfo> modelMeshes, glm::mat4 *mvpMat);
};


#endif //ANDROID_JNI_GLESMATE_H
