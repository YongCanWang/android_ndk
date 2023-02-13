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
        Log.e("tomcan", "getNativeMethod:" + NativePort.getNativeMethod())
        Log.e("tomcan", "getNativeMethod:" + NativePort.getNativeMethod(456))
        Log.e("tomcan", "getNativeMethod:" + NativePort.getNativeMethod("tomcan"))

        Log.e("tomcan", "getNativeUtils:" + NativeUtils.getNativeUtils())
        Log.e("tomcan", "getNativeUtils:" + NativeUtils.getNativeUtils(2))
        Log.e("tomcan", "getNativeUtils:" + NativeUtils.getNativeUtils("tomcan"))
        Log.e("tomcan", "getNativeUtils:" + NativeUtils.getJavaUtils( this, 2))
        Toast.makeText(context, NativePort.getNativeMethod(456), Toast.LENGTH_LONG).show()
    }


    fun getJavaIndex(): Int {
        return 6666
    }


}