package com.mapscloud.jni

import android.content.Context
import android.util.Log
import android.widget.Toast
import com.mapscloud.jni.utils.NativeUtils

/**
 * @author TomCan
 * @description:
 * @date:2023/2/13 15:40
 */
class RequestNative {
    val javaIndex = "987654321"

    constructor(context: Context) {
        NDKMate()

        Log.e("tomcan", "NativeMate-getNativeMate:"
                + com.mapscloud.libnativemate.NativeMate.getNativeMate())
        Log.e("tomcan", "NativeMate-getNativeMate:"
                + com.mapscloud.libnativemate.NativeMate.getNativeMate(0))
        Log.e("tomcan", "NativeMate-getNativeMate:"
                + com.mapscloud.libnativemate.NativeMate.getNativeMate(""))

        Log.e("tomcan", "NativePort-getNativeMethod:"
                + com.mapscloud.libnativemate.NativePort.getNativeMethod())
        Log.e("tomcan", "NativePort-getNativeMethod:"
                + com.mapscloud.libnativemate.NativePort.getNativeMethod(456))
        Log.e("tomcan", "NativePort-getNativeMethod:"
                + com.mapscloud.libnativemate.NativePort.getNativeMethod("tomcan"))

        Log.e("tomcan", "getNativeUtils:"
                + com.mapscloud.libnativemate.NativeUtils.getNativeUtils())
        Log.e("tomcan", "getNativeUtils:"
                + com.mapscloud.libnativemate.NativeUtils.getNativeUtils(2))
        Log.e("tomcan", "getNativeUtils:"
                + com.mapscloud.libnativemate.NativeUtils.getNativeUtils("tomcan"))
        Log.e("tomcan", "getNativeUtils:"
                + com.mapscloud.libnativemate.NativeUtils.getJavaUtils( this, 2))
    }


    /**
     * 供C++调用的java方法
     */
    fun getJavaIndex(): Int {
        return 6666
    }


}