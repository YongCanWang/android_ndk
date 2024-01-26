//
// Created by Tom灿 on 2023/11/21.
//
#include "jni.h"
#include "strings.h"
#include "../utils/LogUtil.h"
#include "JNIImpl.h"
#include "core/AssimpMate.h"
#include"string"
#include "utils/AssetHelper.h"
#include "core/GLMMate.h"
#include "gles/GLESMate.h"
#include "ModelLoader.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wformat"
#define JNIREG_CLASS "com/mapscloud/libnativemate/assimp/AssimpMate"// TODO 指定要注册的类
const std::string TAG_JNImpl = "JNImpl-->";
std::string assetsObjPath;
AssetHelper *assetHelper;
ModelLoader *modelLoader = nullptr;

JNIEXPORT void JNICALL native_draw(JNIEnv *env, jclass clazz) {
    modelLoader->Render3DModel();
}

JNIEXPORT void JNICALL native_viewport(JNIEnv *env, jclass clazz, int width, int height) {
    modelLoader->Viewport(width, height);
}

JNIEXPORT void JNICALL native_scrollAction(JNIEnv *env, jclass clazz,
                                           float distanceX, float distanceY,
                                           float positionX, float positionY) {
    modelLoader->ScrollAction(distanceX, distanceY, positionX, positionY);
}

JNIEXPORT void JNICALL native_scaleAction(JNIEnv *env, jclass clazz, float scaleFactor) {
    modelLoader->ScaleAction(scaleFactor);
}

JNIEXPORT void JNICALL
native_moveAction(JNIEnv *env, jclass clazz, float distanceX, float distanceY) {
    modelLoader->MoveAction(distanceX, distanceY);
}

JNIEXPORT void JNICALL
native_doubleTapAction(JNIEnv *env, jclass clazz) {
    modelLoader->DoubleTapAction();
}

JNIEXPORT void JNICALL native_init(JNIEnv *env, jclass clazz, jstring modelPath) {
//    modelPath =  "/storage/emulated/0/trans/navi3/model-merge/Man.obj";
    LOGCATE("%s native_init-> init assimp", TAG_JNImpl.c_str());
    const char *modelPathChar = env->GetStringUTFChars(modelPath, NULL);
    LOGCATE("%s native_init-> modelPath:%s", TAG_JNImpl.c_str(), modelPathChar);
    modelLoader = new ModelLoader();
//    modelLoader->init(assetsObjPath);
    modelLoader->init(modelPathChar);
    modelLoader->ReadModel();
}

JNIEXPORT void JNICALL native_getAssetsFilePath(JNIEnv *env, jclass clazz,
                                                jobject assetManager,
                                                jstring pathToInternalDir) {
    assetHelper = new AssetHelper(env, assetManager, pathToInternalDir);
    assetsObjPath = assetHelper->StartExtract();
}


//1.建立 函数映射表(本质为JNINativeMethod结构体数组)
JNINativeMethod methods[] = {
        {"init",              "(Ljava/lang/String;)V", (void *) native_init}, // java与native绑定
        {"draw",              "()V",                   (void *) native_draw}, // java与native绑定
        {"viewport",          "(II)V",                 (void *) native_viewport}, // java与native绑定
        {"scrollAction",      "(FFFF)V",               (void *) native_scrollAction}, // java与native绑定
        {"scaleAction",       "(F)V",                  (void *) native_scaleAction}, // java与native绑定
        {"moveAction",        "(FF)V",                 (void *) native_moveAction}, // java与native绑定
        {"doubleTapAction",   "()V",                   (void *) native_doubleTapAction}, // java与native绑定
        {"getAssetsFilePath", "(Landroid/content/res/AssetManager;Ljava/lang/String;)V",
                                                       (void *) native_getAssetsFilePath}, // java与native绑定
};

//2.实现JNI_OnLoad方法，在加载动态库后，自动执行动态注册
jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env = NULL;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }
    //3.调用FindClass方法，获取目标java对象
    jclass clazz = env->FindClass(JNIREG_CLASS);
    if (clazz == NULL) {
        return JNI_ERR;
    }
    //4.调用RegisterNatives方法，传入java对象、JNINativeMethod数组、注册数目，执行动态注册
    jint result = env->RegisterNatives(clazz, methods, 8);
    if (result < 0) {    // 注册失败会返回一个负值
        return JNI_ERR;
    }
    return JNI_VERSION_1_6;
}


#pragma clang diagnostic pop