//
// Created by Tom灿 on 2023/11/24.
//

#include "../../../../../distribution/assimp/include/assimp/Importer.hpp"
#include "core/AssimpMate.h"
#include"../../../../../../../../../../../../ApplicationManage/dev/android/Android SDK/ndk/22.1.7171670/toolchains/llvm/prebuilt/windows-x86_64/sysroot/usr/include/c++/v1/string"
#include "core/GLMMate.h"
#include "utils/AssetHelper.h"


#ifndef ANDROID_JNI_ASSIMPMATE_H
#define ANDROID_JNI_ASSIMPMATE_H

class JNIImpl {

public:
    JNIImpl();

    AssimpMate *assimpLoader;
    GLMMate *glmMate;
};




#endif //ANDROID_JNI_ASSIMPMATE_H
