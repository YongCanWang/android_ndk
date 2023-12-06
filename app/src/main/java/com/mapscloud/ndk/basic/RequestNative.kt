package com.mapscloud.ndk.basic

import android.content.Context
import android.util.Log
import com.mapscloud.libnativemate.basic.NativeMate
import com.mapscloud.libnativemate.basic.NativePort

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
                + NativeMate.getNativeMate())
        Log.e("tomcan", "NativeMate-getNativeMate:"
                + NativeMate.getNativeMate(0))
        Log.e("tomcan", "NativeMate-getNativeMate:"
                + NativeMate.getNativeMate(""))

        Log.e("tomcan", "NativePort-getNativeMethod:"
                + NativePort.getNativeMethod())
        Log.e("tomcan", "NativePort-getNativeMethod:"
                + NativePort.getNativeMethod(456))
        Log.e("tomcan", "NativePort-getNativeMethod:"
                + NativePort.getNativeMethod("tomcan"))

        Log.e("tomcan", "getNativeUtils:"
                + com.mapscloud.libnativemate.basic.NativeUtils.getNativeUtils())
        Log.e("tomcan", "getNativeUtils:"
                + com.mapscloud.libnativemate.basic.NativeUtils.getNativeUtils(2))
        Log.e("tomcan", "getNativeUtils:"
                + com.mapscloud.libnativemate.basic.NativeUtils.getNativeUtils("tomcan"))
        Log.e("tomcan", "getNativeUtils:"
                + com.mapscloud.libnativemate.basic.NativeUtils.getJavaUtils( this, 2))
    }


    /**
     * 供C++调用的java方法
     */
    fun getJavaIndex(): Int {
        return 6666
    }


}