//
// Created by Tom on 2023/2/8.
//

#include <string>
#include "jni.h"
#include "string.h"
#include "strings.h"
#include "../utils/LogUtil.h"

//extern "C" {
//#define JNIREG_CLASS "com/mapscloud/ndk/utils/NativeUtils"//指定要注册的类
#define JNIREG_CLASS "com/mapscloud/libnativemate/basic/NativeUtils"// TODO 指定要注册的类

JNIEXPORT  jstring JNICALL native_getNativeUtils(JNIEnv *env, jclass clazz) {
    return env->NewStringUTF("33000");
}


JNIEXPORT jstring JNICALL native2_getNativeUtils(JNIEnv *env, jclass clazz, jint i) {
    if (i == 0) {
        return env->NewStringUTF("33111+0");
    } else if (i == 1) {
        return env->NewStringUTF("33111+1");
    } else if (i == 2) {
        return env->NewStringUTF("33111+2");
    }
    return env->NewStringUTF("33111");
}

JNIEXPORT int JNICALL native3_getNativeUtils(JNIEnv *env, jclass clazz, jstring s) {
    return 33222;
}

/**
 *  native与java的互相调用： 找到类->找到方法->找到返回值
 * @param env
 * @param clazz
 * @param obj
 * @param jint1
 * @return
 */
JNIEXPORT jint JNICALL getJavaUtils(JNIEnv *env, jclass clazz, jobject obj, jint jint1) {
//JNIEXPORT jint JNICALL getJavaUtils(JNIEnv *env, jclass claz, jint jint1) {
    LOGCATE("NativeUtils-getJavaUtils: getJavaIndex()---------------------1");
    jclass jc = env->GetObjectClass(obj); // 获取NativeConnector 映射类
//    jclass jc = env->FindClass("com/mapscloud/jni/RequestNative");
    LOGCATE("NativeUtils-getJavaUtils: getJavaIndex()---------------------2");
    jmethodID jmethodID1 = env->GetMethodID(jc, "getJavaIndex", "()I"); // 返回java方法的方法ID,参2为java的方法名
    LOGCATE("NativeUtils-getJavaUtils: getJavaIndex()---------------------3");
//    jmethodID jmethodID2 = env->GetMethodID(jc, "getNativeUtils", "(I)C"); // 方法ID
//    jmethodID jmethodID3 = env->GetMethodID(jc, "getNativeUtils", "(C)I"); // 方法ID
//    jmethodID jmethodID4 = env->GetMethodID(jc, "getJavaUtils", "(I)I"); // 方法ID
//    jfieldID jfieldId = env->GetFieldID(jc, "javaInt", "I");  // 参数ID
    jint i = env->CallIntMethod(obj, jmethodID1); // 获取getJavaInt()方法返回值
    LOGCATE("NativeUtils-getJavaUtils: getJavaIndex()---------------------4");
//    char c = env->CallCharMethod(jc, jmethodID2, 2); // 获取getJavaStr()方法返回值
//    jint si = env->CallStaticIntMethod(jc, jmethodID3);// 获取static静态 getJavaStaticInt()方法返回值
//    jint k = env->GetIntField(clazz, jfieldId); // 获取参数值

//    LOGCATE("NativeUtils-getUtilsBool: getJavaStr()", c);
//    LOGCATE("NativeUtils-getUtilsBool: getJavaStaticInt()", si);
//    LOGCATE("NativeUtils-getUtilsBool: javaInt", k);
    LOGCATE("NativeUtils-getJavaUtils: getJavaIndex()---------------------4", i);
    return i;
}


//1.建立 函数映射表(本质为JNINativeMethod结构体数组)
JNINativeMethod methods[] = {
        {"getNativeUtils", "()Ljava/lang/String;",   (void *) native_getNativeUtils}, // java与native绑定
        {"getNativeUtils", "(I)Ljava/lang/String;",  (void *) native2_getNativeUtils},// java与native绑定
        {"getNativeUtils", "(Ljava/lang/String;)I",  (void *) native3_getNativeUtils},// java与native绑定
        {"getJavaUtils",   "(Ljava/lang/Object;I)I", (void *) getJavaUtils}// java与native绑定
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
    jint result = env->RegisterNatives(clazz, methods, 4);
    if (result < 0) {    // 注册失败会返回一个负值
        return JNI_ERR;
    }
    return JNI_VERSION_1_6;
}


//}


















