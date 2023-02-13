package com.mapscloud.jni;

/**
 * @author TomCan
 * @description:
 * @date:2023/2/7 16:53
 */
public class NDKMate {

    static {
        System.loadLibrary("libNativePort_JNI");
    }
}
