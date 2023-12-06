#ifndef GIS_LOGUTIL_H
#define GIS_LOGUTIL_H

#include<android/log.h>
#include <string>

#define  LOG_TAG "tomcan-android-jni-native-C"

#define  LOGCATE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define  LOGCATV(...)  __android_log_print(ANDROID_LOG_VERBOSE,LOG_TAG,__VA_ARGS__)
#define  LOGCATD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGCATI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)

#define LOG_RESULT(FUN) {LOGCATD("%s func start", FUN);  std::string str= PrintResult(double *pdValues,int len) }


static std::string PrintResult(double *pdValues, int len, int dimension) {
    std::string results = "\t length-->" + std::to_string(len) + "\n";
    for (int i = 0; i < len; ++i) {
        if (dimension == 2) {
            results = results + "\t pdValues[" + std::to_string(i / 2) + "] (" +
                      std::to_string(pdValues[(i / 2)]) + "," +
                      std::to_string(pdValues[(i / 2 + 1)]) + ")\n";
        } else {
            results = results + "\t pdValues[" + std::to_string(i / 3) + "] (" +
                      std::to_string(pdValues[(i / 3)]) + "," +
                      std::to_string(pdValues[(i / 3 + 1)]) +
                      std::to_string(pdValues[(i / 3 + 2)])
                      + ")\n";
        }
    }


    return results;
}

#endif //GIS_LOGUTIL_H