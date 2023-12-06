//
// Created by Tom灿 on 2023/12/6.
//

#include "GLESMate.h"
#include "ShaderMate.h"
#include <GLES2/gl2.h>
#include <sstream>
#include "../../utils/LogUtil.h"
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

    CheckGLError("GLES Initiate");
}

/**
 * set the viewport, function is also called when user changes device orientation
 */
void GLESMate::Viewport(int width, int height) {
    glViewport(0, 0, width, height);
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