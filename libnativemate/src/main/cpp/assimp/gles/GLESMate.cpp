//
// Created by Tom灿 on 2023/12/6.
//

#include "GLESMate.h"
#include "ShaderMate.h"
#include <GLES2/gl2.h>
#include <sstream>
#include "../../utils/LogUtil.h"
#include "fwd.hpp"
#include "../../assimp/core/AssimpMate.h"
//#include "gl3stub.h"

void GLESMate::init() {
    // White background
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LEQUAL);
    LOGCATE("OpenGL %s, GLSL %s", glGetString(GL_VERSION),
            glGetString(GL_SHADING_LANGUAGE_VERSION));

    // check if the device supports GLES 3 or GLES 2
    const char *versionStr = (const char *) glGetString(GL_VERSION);
    if (strstr(versionStr, "OpenGL ES 3.")
//    && gl3stubInit()
            ) {
        LOGCATE("Device supports GLES 3");
    } else {
        LOGCATE("Device supports GLES 2");
    }

    std::string vertexShader = "shaders/modelTextured.vsh";
    std::string fragmentShader = "shaders/modelTextured.fsh";
    shaderProgramID = LoadShaders(vertexShader, fragmentShader);

    vertexAttribute = GetAttributeLocation(shaderProgramID, "vertexPosition");
    vertexUVAttribute = GetAttributeLocation(shaderProgramID, "vertexUV");
    mvpLocation = GetUniformLocation(shaderProgramID, "mvpMat");
    textureSamplerLocation = GetUniformLocation(shaderProgramID, "textureSampler");

    CheckGLError("GLES Initiate");
}

/**
 * set the viewport, function is also called when user changes device orientation
 */
void GLESMate::Viewport(int width, int height) {
    glViewport(0, 0, width, height);
}


/**
 * Renders the 3D model by rendering every mesh in the object
 * 通过渲染对象中的每个网格来渲染3D模型
 */
void GLESMate::Render3DModel(std::vector<struct MeshInfo> modelMeshes, glm::mat4 *mvpMat) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shaderProgramID);
    glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, (const GLfloat *) mvpMat);

    glActiveTexture(GL_TEXTURE0);
    glUniform1i(textureSamplerLocation, 0);

    unsigned int numberOfLoadedMeshes = modelMeshes.size();
    LOGCATE("GL->Render: model meshes size:%u", numberOfLoadedMeshes);
    // render all meshesgit
    for (unsigned int n = 0; n < numberOfLoadedMeshes; ++n) {
        // Texture
        if (modelMeshes[n].textureIndex) {
            glBindTexture(GL_TEXTURE_2D, modelMeshes[n].textureIndex);
            LOGCATE("GL->Render: bind the %u-th mesh's texture:%u", n, modelMeshes[n].textureIndex);
        }

        // Faces
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, modelMeshes[n].faceBuffer);
        LOGCATE("GL->Render: bind the %u-th mesh's face：%u", n, modelMeshes[n].faceBuffer);

        // Vertices
        glBindBuffer(GL_ARRAY_BUFFER, modelMeshes[n].vertexBuffer);
        LOGCATE("GL->Render: bind the %u-th mesh's vertices：%u", n, modelMeshes[n].vertexBuffer);
        glEnableVertexAttribArray(vertexAttribute);
        glVertexAttribPointer(vertexAttribute, 3, GL_FLOAT, 0, 0, 0);

        // Texture coords
        glBindBuffer(GL_ARRAY_BUFFER, modelMeshes[n].textureCoordBuffer);
        LOGCATE("GL->Render: bind the %u-th mesh's texture coordinates：%u", n,
                modelMeshes[n].textureCoordBuffer);
        glEnableVertexAttribArray(vertexUVAttribute);
        glVertexAttribPointer(vertexUVAttribute, 2, GL_FLOAT, 0, 0, 0);

        glDrawElements(GL_TRIANGLES, modelMeshes[n].numberOfFaces * 3, GL_UNSIGNED_INT, 0);
        LOGCATE("GL->Render: draw the %u-th mesh：%u", n);
        // unbind buffers
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    }
}


/**
 * Checks for OpenGL errors.
 */
void GLESMate::CheckGLError(std::string funcName) {

    GLenum err = glGetError();
    if (err == GL_NO_ERROR) {
        return;
    } else {
        LOGCATE("[FAIL GL] %s", funcName.c_str());
    }

    switch (err) {

        case GL_INVALID_ENUM:
            LOGCATE("GL_INVALID_ENUM: GLenum argument out of range");
            break;

        case GL_INVALID_VALUE:
            LOGCATE("GL_INVALID_VALUE: numeric argument out of range");
            break;

        case GL_INVALID_OPERATION:
            LOGCATE("GL_INVALID_OPERATION: operation illegal in current state");
            break;

        case GL_INVALID_FRAMEBUFFER_OPERATION:
            LOGCATE("GL_INVALID_FRAMEBUFFER_OPERATION: framebuffer object is not complete");
            break;

        case GL_OUT_OF_MEMORY:
            LOGCATE("GL_OUT_OF_MEMORY: not enough memory left to execute command");
            break;

        default:
            LOGCATE("unlisted error");
            break;
    }
}