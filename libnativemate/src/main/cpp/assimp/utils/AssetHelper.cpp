//
// Created by Tom灿 on 2023/12/2.
//

#include "AssetHelper.h"
#include "jni.h"
#include <android/asset_manager_jni.h>
#include "string"
#include "../../utils/LogUtil.h"
#include "../common/misc.h"

AssetHelper::AssetHelper(JNIEnv *env, jobject assetManager,
                         jstring pathToInternalDir) {
    // get a native instance of the asset manager // 获取资产管理器的本地实例
    // assetManager is passed from Java and should not be garbage collected!
    // assetManager是从Java传入的，不应该被垃圾收集!
    aAssetManager = AAssetManager_fromJava(env, assetManager);

    //Save app internal data storage path -- we will extract assets and save here
    // 保存应用内部数据存储路径——我们将提取资源并保存在这里
    const char *cPathToInternalDir;
    cPathToInternalDir = env->GetStringUTFChars(pathToInternalDir, NULL);
    apkInternalPath = std::string(cPathToInternalDir);
    env->ReleaseStringUTFChars(pathToInternalDir, cPathToInternalDir);

    //mutex for thread safety // 用于线程安全的互斥锁
    pthread_mutex_init(&threadMutex, NULL);

}

AssetHelper::~AssetHelper() {
    pthread_mutex_destroy(&threadMutex);
}


std::string AssetHelper::StartExtract() {
    // extract the OBJ and companion files from assets // 从资产中提取OBJ和配套文件
    std::string objFilename, mtlFilename, texFilename;
    bool isFilesPresent =
            ExtractAssetReturnFilename("amenemhat/amenemhat.obj", objFilename) &&
            ExtractAssetReturnFilename("amenemhat/amenemhat.mtl", mtlFilename) &&
            ExtractAssetReturnFilename("amenemhat/amenemhat.jpg", texFilename);

//            ExtractAssetReturnFilename("obj/Man.obj", objFilename) &&
//            ExtractAssetReturnFilename("obj/Man.mtl", mtlFilename) &&
//            ExtractAssetReturnFilename("obj/Man.JPG", texFilename);

    if (isFilesPresent) {
        LOGCATE("Assets: Model exist!", objFilename.c_str());
    } else {
        LOGCATE("Assets: Model %s does not exist!", objFilename.c_str());
    }
    return objFilename;
}

/**
 * Search for a file in assets, extract it, save it in internal storage, and return the new path
 * 在assets中搜索文件，提取文件，将其保存在内部存储器中，并返回新路径
 */
bool AssetHelper::ExtractAssetReturnFilename(std::string assetName, std::string &filename,
                                             bool checkIfFileIsAvailable) {

    // construct the filename in internal storage by concatenating with path to internal storage
    // 通过连接到内部存储器的路径来在内部存储器中构造文件名
    filename = apkInternalPath + "/" + GetFileName(assetName);

    // check if the file was previously extracted and is available in app's internal dir
    // 检查该文件是否已被提取，并且在应用程序的内部目录中可用
    FILE *file = fopen(filename.c_str(), "rb");
    if (file && checkIfFileIsAvailable) {
        LOGCATE("Assets: Found extracted file in assets: %s", filename.c_str());
        fclose(file);
        pthread_mutex_unlock(&threadMutex);
        return true;
    }

    // let us look for the file in assets
    // 让我们在assets中查找文件
    bool result = false;

    // AAsset objects are not thread safe and need to be protected with mutex
    // AAsset对象不是线程安全的，需要用互斥锁来保护
    pthread_mutex_lock(&threadMutex);

    // Open file
    AAsset *asset = AAssetManager_open(aAssetManager, assetName.c_str(),
                                       AASSET_MODE_STREAMING);

    char buf[BUFSIZ];
    int nb_read = 0;
    if (asset != NULL) {
        FILE *out = fopen(filename.c_str(), "w");
        while ((nb_read = AAsset_read(asset, buf, BUFSIZ)) > 0) {
            fwrite(buf, nb_read, 1, out);
        }
        fclose(out);
        AAsset_close(asset);
        result = true;

        LOGCATE("Assets: Asset extracted: %s", filename.c_str());
    } else {
        LOGCATE("Assets: Asset not found: %s", assetName.c_str());
    }

    pthread_mutex_unlock(&threadMutex);
    return result;

}