//
// Created by Tom灿 on 2023/12/5.
//

#ifndef ANDROID_JNI_SHADERMATE_H
#define ANDROID_JNI_SHADERMATE_H


#include <GLES2/gl2.h>
#include "jni.h"
#include "string"
#include "../utils/AssetHelper.h"


GLuint LoadShaders(std::string vertexShaderCode, std::string fragmentShaderCode);

GLuint GetAttributeLocation(GLuint programID, std::string variableName);

GLint GetUniformLocation(GLuint programID, std::string uniformName);

const std::string TAG_SHADER = "Shader-->";

class ShaderMate {


};


#endif //ANDROID_JNI_SHADERMATE_H
