//
// Created by 53590 on 2023/12/7.
//

#ifndef ANDROID_NDK_MESHINFO_H
#define ANDROID_NDK_MESHINFO_H

#include <GLES2/gl2.h>

class MeshInfo {

};


struct Mesh {
    GLuint textureIndex;
    int numberOfFaces;
    GLuint faceBuffer;
    GLuint vertexBuffer;
    GLuint textureCoordBuffer;
};

#endif //ANDROID_NDK_MESHINFO_H
