//
// Created by Tom灿 on 2023/12/2.
//

#ifndef ANDROID_JNI_ASSETHELPER_H
#define ANDROID_JNI_ASSETHELPER_H


#include <jni.h>
#include <android/asset_manager_jni.h>
#include "string"
extern "C" {
class AssetHelper {


private:
    std::string TAG = "AssetHelper";
    AAssetManager *aAssetManager;
    std::string apkInternalPath;
    mutable pthread_mutex_t threadMutex;



public:
    AssetHelper(_JNIEnv *env, _jobject *assetManager, _jstring *pathToInternalDir);

    ~AssetHelper();

    bool ExtractAssetReturnFilename(std::string assetName, std::string &filename,
                                    bool checkIfFileIsAvailable = false);

    std:: string StartExtract();
};

extern AssetHelper *assetHelper;

}



#endif //ANDROID_JNI_ASSETHELPER_H