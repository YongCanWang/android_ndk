//
// Created by Tom on 2023/2/8.
//

#include "NativeMate.h"
#include <jni.h>
#include "com_mapscloud_libnativemate_NativeMate.h"



extern "C" jstring
Java_com_mapscloud_libnativemate_NativeMate_getNativeMate__(JNIEnv *env, jclass clazz) {
    return env->NewStringUTF("NativeMate!");
}


extern "C"
jstring
Java_com_mapscloud_libnativemate_NativeMate_getNativeMate__I(JNIEnv *env, jclass clazz, jint age) {
    return env->NewStringUTF("NativeMate!!");
}

extern "C"
JNIEXPORT jint
Java_com_mapscloud_libnativemate_NativeMate_getNativeMate__Ljava_lang_String_2(JNIEnv
*env,
jclass clazz,
        jstring
name) {
return 456;
}
