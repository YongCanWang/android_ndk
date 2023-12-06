package com.mapscloud.libnativemate.assimp;

import android.content.res.AssetManager;

/**
 * @author Tom灿
 * @description:
 * @date :2023/11/21 16:29
 */
public class AssimpMate {

    public static native void init(String modelPath);

    public static native void viewport(int width, int height);

    public static native void draw();

    public static native void scrollAction(float distanceX, float distanceY, float positionX, float positionY);

    public static native void scaleAction(float scaleFactor);

    public static native void moveAction(float distanceX, float distanceY);

    public static native void doubleTapAction();

    public static native void getAssetsFilePath(AssetManager assetManager, String path);


}
