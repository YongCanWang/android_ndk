//
// Created by Tom灿 on 2023/12/5.
//

#include "ShaderMate.h"
#include "strings.h"
#include <iostream>
#include <fstream>
#include "../../utils/LogUtil.h"
#include <vector>
#include "fwd.hpp"
#include <GLES2/gl2.h>
#include "../JNIImpl.h"


/**
 * Read the shader code from assets
 */
bool ReadShaderCode(std::string &shaderCode, std::string &shaderFileName) {

    LOGCATE("%s ReadShaderCode->shaderFileName: %s", TAG_SHADER.c_str(), shaderFileName.c_str());

    // android shaders are stored in assets
    // read them using MyJNIHelper
    bool isFilePresent = assetHelper->ExtractAssetReturnFilename(shaderFileName,
                                                                 shaderFileName);
    if (!isFilePresent) {
        return false;
    }

    std::ifstream shaderStream(shaderFileName.c_str(), std::ios::in);
    if (shaderStream.is_open()) {
        std::string Line = "";
        while (getline(shaderStream, Line)) {
            shaderCode += "\n" + Line;
        }
        shaderStream.close();
    } else {
        LOGCATE("%s ReadShaderCode->cannot open shader file: %s", TAG_SHADER.c_str(),
                shaderFileName.c_str());
        return false;
    }

    LOGCATE("%s ReadShaderCode->read shader code successfully", TAG_SHADER.c_str());
    return true;
}

//**
//* Compile the shader and log any error messages
//*/
bool CompileShader(GLuint &shaderID, const GLenum shaderType, std::string shaderCode) {

    // Create the shader
    shaderID = glCreateShader(shaderType);

    // Compile Shader
    LOGCATE("%s CompileShader->compiling shader ID:%u", TAG_SHADER.c_str(), shaderID);
    char const *sourcePointer = shaderCode.c_str();
    glShaderSource(shaderID, 1, &sourcePointer, NULL);
    glCompileShader(shaderID);

    // Check Shader
    GLint result = GL_FALSE;
    int infoLogLength;

    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (result == 0) {

        std::vector<char> shaderErrorMessage(infoLogLength + 1);
        glGetShaderInfoLog(shaderID, infoLogLength, NULL, &shaderErrorMessage[0]);
        LOGCATE("%s CompileShader->failed to compile shader:%s", TAG_SHADER.c_str(),
                &shaderErrorMessage[0]);
        return false;
    } else {
        LOGCATE("%s CompileShader->compiled shader successfully", TAG_SHADER.c_str());
    }

    return true;
}

/**
 * Link the vertex and fragment shaders together
 */
bool LinkProgram(GLuint programID, GLuint vertexShaderID,
                 GLuint fragmentShaderID) {
    GLint result = GL_FALSE;
    int infoLogLength;


    LOGCATE("%s LinkProgram->linking program:programID=%u,vertexShaderID=%u,fragmentShaderID=%u",
            TAG_SHADER.c_str(), programID, vertexShaderID, fragmentShaderID);

    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
    glLinkProgram(programID);

    // Check the program
    glGetProgramiv(programID, GL_LINK_STATUS, &result);
    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);

    // common deletes
    if (vertexShaderID) {
        glDeleteShader(vertexShaderID);
    }
    if (fragmentShaderID) {
        glDeleteShader(fragmentShaderID);
    }

    if (result == 0) {
        std::vector<char> programErrorMessage(infoLogLength + 1);
        glGetProgramInfoLog(programID, infoLogLength, NULL,
                            &programErrorMessage[0]);
        LOGCATE("%s LinkProgram->failed to link program:%s", TAG_SHADER.c_str(),
                &programErrorMessage[0]);
        if (programID) {
            glDeleteProgram(programID);
        }
        return false;
    }
    LOGCATE("%s LinkProgram->linked successfully", TAG_SHADER.c_str());
    return true;
}

/**
 * Read the vertex & fragment shaders, compile and link them, return the program ID
 */
GLuint LoadShaders(std::string vertexShaderFilename,
                   std::string fragmentShaderFilename) {

    GLuint vertexShaderID, fragmentShaderID, programID;
    programID = glCreateProgram();

    // read and compile the vertex shader
    std::string vertexShaderCode;
    if (!ReadShaderCode(vertexShaderCode, vertexShaderFilename)) {
        LOGCATE("%s LoadShaders->error in reading vertex shader", TAG_SHADER.c_str());
        return 0;
    }
    if (!CompileShader(vertexShaderID, GL_VERTEX_SHADER, vertexShaderCode)) {
        LOGCATE("%s LoadShaders->error in compiling vertex shader", TAG_SHADER.c_str());
        return 0;
    }

    // read and compile the fragment shader
    std::string fragmentShaderCode;
    if (!ReadShaderCode(fragmentShaderCode, fragmentShaderFilename)) {
        LOGCATE("%s LoadShaders->error in reading fragment shader", TAG_SHADER.c_str());
        return 0;
    }
    if (!CompileShader(fragmentShaderID, GL_FRAGMENT_SHADER, fragmentShaderCode)) {
        LOGCATE("%s LoadShaders->error in compiling fragment shader", TAG_SHADER.c_str());
        return 0;
    }

    // Link both the shaders together
    if (!LinkProgram(programID, vertexShaderID, fragmentShaderID)) {
        LOGCATE("%s LoadShaders->error in linking shaders", TAG_SHADER.c_str());
        return 0;
    }

    return programID;
}

/*
 * get the attribute location of an input variable in a shader
 */
GLuint GetAttributeLocation(GLuint programID, std::string variableName) {

    GLint loc = glGetAttribLocation(programID, variableName.c_str());
    if (loc == -1) {
        LOGCATE("%s GetAttributeLocation->error in getting attribute:", TAG_SHADER.c_str(),
                variableName.c_str());
        return (0);
    } else {
        return ((GLuint) loc);
    }
}

/*
 * get the location of a uniform variable in a shader
 */
GLint GetUniformLocation(GLuint programID, std::string uniformName) {

    GLint loc = glGetUniformLocation(programID, uniformName.c_str());
    if (loc == -1) {
        LOGCATE("%s GetUniformLocation->error in uniform: %s", TAG_SHADER.c_str(),
                uniformName.c_str());
    } else {
        return loc;
    }
}
