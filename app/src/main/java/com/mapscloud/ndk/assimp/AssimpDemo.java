package com.mapscloud.ndk.assimp;

import android.app.Activity;
import android.app.Application;
import android.content.Context;
import android.util.Log;

import com.mapscloud.libnativemate.assimp.AssimpMate;
import com.mapscloud.ndk.utils.Utils;

import java.io.File;

/**
 * @author Tom灿
 * @description:
 * @date :2023/11/21 16:56
 */
public class AssimpDemo {
    private static String TAG = "AssimpDemo";
    static {
        System.loadLibrary("AssimpMate");
    }

    public AssimpDemo(Activity context) {
        Utils.copyAssetAndWrite(context, "Man.JPG");
        Utils.copyAssetAndWrite(context, "Man.mtl");
        Utils.copyAssetAndWrite(context, "Man.obj");
        File file = new File(context.getCacheDir(), "Man.obj");
        Log.e(TAG, "文件路径: "+  file.getPath());
        AssimpMate.init(file.getPath());
    }
}
