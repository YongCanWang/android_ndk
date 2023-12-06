package com.mapscloud.libnativemate.basic;

/**
 * @author TomCan
 * @description:
 * @date:2023/2/13 10:04
 */
public class NativeConnector {
    public int javaInt = 1008;

    public static int getJavaStaticInt() {
        return 1000;
    }

    public int getJavaInt() {
        return 1001;
    }

    public String getJavaStr(int index) {
        if (index == 0) {
            return "100x0";
        } else if (index == 1) {
            return "100x1";
        } else {
            return "100xx";
        }
    }
}

