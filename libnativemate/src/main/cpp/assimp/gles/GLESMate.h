//
// Created by Tom灿 on 2023/12/6.
//

#ifndef ANDROID_JNI_GLESMATE_H
#define ANDROID_JNI_GLESMATE_H
#include <vector>

class GLESMate {

public:
    void init();

    void Viewport(int width, int height);

    void CheckGLError(std::string);
};


#endif //ANDROID_JNI_GLESMATE_H
