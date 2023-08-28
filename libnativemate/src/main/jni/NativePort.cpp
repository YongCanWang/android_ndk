//
// Created by Tom on 2023/2/7.
//
#include "jni.h"
#include "utils/LogUtil.h"
#include "NativePort.h"
#include "com_mapscloud_libnativemate_NativePort.h"
#include "com_mapscloud_libnativemate_NativeMate.h"

// TODO 手写+VC 无法使用
//格式为：Java_包名_类名_函数名(方法名)(调用jni的类的包名)
//extern "C" JNIEXPORT jstring JNICALL Java_com_mapscloud_libnativemate_NativePort_getNativeMethod__
//        (JNIEnv *env, jclass) {
//    return env->NewStringUTF("hello, jni!");
//}
//
//
//extern "C" JNIEXPORT jstring JNICALL Java_com_mapscloud_libnativemate_NativePort_getNativeMethod__I
//        (JNIEnv *, jclass, jint i1) {
//    return (jstring) i1;
//}
//
//
//extern "C" JNIEXPORT jint JNICALL
//Java_com_mapscloud_libnativemate_NativePort_getNativeMethod__Ljava_lang_String_2
//        (JNIEnv *, jclass, jstring si) {
//    return 123456;
//}
//
//
//extern "C" JNIEXPORT jstring JNICALL getNativeMethod
//        (JNIEnv *env, jclass) {
//    return env->NewStringUTF("hello, jni!");
//}


// TODO 指向包名com.mapscloud.jni
extern "C"
JNIEXPORT jstring JNICALL
Java_com_mapscloud_jni_NativePort_getNativeMethod__(JNIEnv *env, jclass clazz) {
    return env->NewStringUTF("NativePort!");
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_mapscloud_jni_NativePort_getNativeMethod__I(JNIEnv *env, jclass clazz, jint age) {
    return env->NewStringUTF("NativePort!!");
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_mapscloud_jni_NativePort_getNativeMethod__Ljava_lang_String_2(JNIEnv *env, jclass clazz,
                                                                       jstring name) {
    return 123;
}




// TODO 指向包名com.mapscloud.libnativemate
extern "C"
JNIEXPORT jstring JNICALL
Java_com_mapscloud_libnativemate_NativePort_getNativeMethod__(JNIEnv *env, jclass clazz) {
    return env->NewStringUTF("NativePort!");
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_mapscloud_libnativemate_NativePort_getNativeMethod__I(JNIEnv *env, jclass clazz,
                                                               jint age) {
    return env->NewStringUTF("NativePort!!");
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_mapscloud_libnativemate_NativePort_getNativeMethod__Ljava_lang_String_2(JNIEnv *env,
                                                                                 jclass clazz,
                                                                                 jstring name) {
    return 123;
}

