//
// Created by Tom灿 on 2023/11/24.
//


#include <GLES2/gl2.h>
#include "AssimpMate.h"
#include "strings.h"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "../JNIImpl.h"
#include "../../utils/LogUtil.h"
#include "../common/misc.h"
#include "opencv2/imgproc/types_c.h"
#include "opencv2/opencv.hpp"
#include "../gles/ShaderMate.h"


AssimpMate::AssimpMate() {
    importer = new Assimp::Importer;
    // shader related setup -- loading, attribute and uniform locations
    std::string vertexShader = "shaders/modelTextured.vsh";
    std::string fragmentShader = "shaders/modelTextured.fsh";
    shaderProgramID = LoadShaders(vertexShader, fragmentShader);
    vertexAttribute = GetAttributeLocation(shaderProgramID, "vertexPosition");
    vertexUVAttribute = GetAttributeLocation(shaderProgramID, "vertexUV");
    mvpLocation = GetUniformLocation(shaderProgramID, "mvpMat");
    textureSamplerLocation = GetUniformLocation(shaderProgramID, "textureSampler");
}


/**
 * Renders the 3D model by rendering every mesh in the object
 * 通过渲染对象中的每个网格来渲染3D模型
 */
void AssimpMate::Render3DModel(glm::mat4 *mvpMat) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shaderProgramID);
    glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, (const GLfloat *) mvpMat);

    glActiveTexture(GL_TEXTURE0);
    glUniform1i(textureSamplerLocation, 0);

    unsigned int numberOfLoadedMeshes = modelMeshes.size();
    LOGCATE("GL->Render: model meshes size:%u", numberOfLoadedMeshes);
    // render all meshesgit
    for (unsigned int n = 0; n < numberOfLoadedMeshes; ++n) {

        // Texture
        if (modelMeshes[n].textureIndex) {
            glBindTexture(GL_TEXTURE_2D, modelMeshes[n].textureIndex);
            LOGCATE("GL->Render: bind the %u-th mesh's texture:%u", n, modelMeshes[n].textureIndex);
        }

        // Faces
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, modelMeshes[n].faceBuffer);
        LOGCATE("GL->Render: bind the %u-th mesh's face：%u", n, modelMeshes[n].faceBuffer);

        // Vertices
        glBindBuffer(GL_ARRAY_BUFFER, modelMeshes[n].vertexBuffer);
        LOGCATE("GL->Render: bind the %u-th mesh's vertices：%u", n, modelMeshes[n].vertexBuffer);
        glEnableVertexAttribArray(vertexAttribute);
        glVertexAttribPointer(vertexAttribute, 3, GL_FLOAT, 0, 0, 0);

        // Texture coords
        glBindBuffer(GL_ARRAY_BUFFER, modelMeshes[n].textureCoordBuffer);
        LOGCATE("GL->Render: bind the %u-th mesh's texture coordinates：%u", n,
                modelMeshes[n].textureCoordBuffer);
        glEnableVertexAttribArray(vertexUVAttribute);
        glVertexAttribPointer(vertexUVAttribute, 2, GL_FLOAT, 0, 0, 0);

        glDrawElements(GL_TRIANGLES, modelMeshes[n].numberOfFaces * 3, GL_UNSIGNED_INT, 0);
        LOGCATE("GL->Render: draw the %u-th mesh：%u", n);
        // unbind buffers
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    }


}

/**
 * Generate buffers for vertex positions, texture coordinates, faces -- and load data into them
 *
 * 为顶点位置、纹理坐标、面生成缓冲区，并将数据加载到其中
 */
void AssimpMate::GenerateGLBuffers() {
    LOGCATE("Assimp->Buffers: start load vertex and texture coordinates");
    struct MeshInfo newMeshInfo; // this struct is updated for each mesh in the model
    GLuint buffer;

    // For every mesh -- load face indices, vertex positions, vertex texture coords
    // 对于每个网格-加载面索引，顶点位置，顶点纹理坐标
    // also copy texture index for mesh into newMeshInfo.textureIndex
    // 也复制纹理索引为网格到
    LOGCATE("Assimp->Buffers: meshes size:%u", scene->mNumMeshes);
    for (unsigned int n = 0; n < scene->mNumMeshes; ++n) {

        const aiMesh *mesh = scene->mMeshes[n]; // read the n-th mesh // 读取第n个网格
        LOGCATE("Assimp->Buffers: read the %u-th mesh", n);
        // create array with faces // 创建带有面的数组
        // convert from Assimp's format to array for GLES // 将Assimp的格式转换为用于GLES的数组
        unsigned int *faceArray = new unsigned int[mesh->mNumFaces * 3];
        unsigned int faceIndex = 0;
        LOGCATE("Assimp->Buffers:  the %u-th mesh's faces size: %u", n, mesh->mNumFaces);
        for (unsigned int t = 0; t < mesh->mNumFaces; ++t) {
            // read a face from assimp's mesh and copy it into faceArray
            // 从assimp的网格中读取一张面并将其复制到faceArray中
            const aiFace *face = &mesh->mFaces[t];
            memcpy(&faceArray[faceIndex], face->mIndices, 3 * sizeof(unsigned int));
            faceIndex += 3;
        }
        newMeshInfo.numberOfFaces = scene->mMeshes[n]->mNumFaces;

        // buffer for faces  // 面缓冲区
        if (newMeshInfo.numberOfFaces) {

            glGenBuffers(1, &buffer);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                         sizeof(unsigned int) * mesh->mNumFaces * 3, faceArray,
                         GL_STATIC_DRAW);
            newMeshInfo.faceBuffer = buffer;

        }
        delete[] faceArray;

        // buffer for vertex positions  // 顶点缓冲区
        if (mesh->HasPositions()) {

            glGenBuffers(1, &buffer);
            glBindBuffer(GL_ARRAY_BUFFER, buffer);
            glBufferData(GL_ARRAY_BUFFER,
                         sizeof(float) * 3 * mesh->mNumVertices, mesh->mVertices,
                         GL_STATIC_DRAW);
            newMeshInfo.vertexBuffer = buffer;

        }

        // buffer for vertex texture coordinates  // 顶点纹理坐标缓冲区
        // ***ASSUMPTION*** -- handle only one texture for each mesh // 每个网格只处理一个纹理
        if (mesh->HasTextureCoords(0)) {

            float *textureCoords = new float[2 * mesh->mNumVertices];
            for (unsigned int k = 0; k < mesh->mNumVertices; ++k) {
                textureCoords[k * 2] = mesh->mTextureCoords[0][k].x;
                textureCoords[k * 2 + 1] = mesh->mTextureCoords[0][k].y;
            }
            glGenBuffers(1, &buffer);
            glBindBuffer(GL_ARRAY_BUFFER, buffer);
            glBufferData(GL_ARRAY_BUFFER,
                         sizeof(float) * 2 * mesh->mNumVertices, textureCoords,
                         GL_STATIC_DRAW);
            newMeshInfo.textureCoordBuffer = buffer;
            delete[] textureCoords;

        }

        // unbind buffers 释放缓冲区
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        // copy texture index (= texture name in GL) for the mesh from textureNameMap
        // 从textureNameMap中复制纹理索引(= GL中的纹理名称)
        aiMaterial *mtl = scene->mMaterials[mesh->mMaterialIndex];
        aiString texturePath;    //contains filename of texture
        if (AI_SUCCESS == mtl->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath)) {
            unsigned int textureId = textureNameMap[texturePath.data];
            newMeshInfo.textureIndex = textureId;
        } else {
            newMeshInfo.textureIndex = 0;
        }

        modelMeshes.push_back(newMeshInfo);
    }
}


/**
 * Read textures associated with all materials and load images to GL
 *
 * 读取与所有材料相关的纹理，并将图像加载到GL
 */
bool AssimpMate::LoadTexturesToGL(std::string modelFilePath) {
    LOGCATE("Assimp->Textures: Materials =  %s", modelFilePath.c_str());
    // read names of textures associated with all materials
    textureNameMap.clear();


    if (scene->HasMaterials()) {
        LOGCATE("Assimp->Textures: Materials size：%u", scene->mNumMaterials);
        // 遍历materials数组（一个.mtl文件可以包含一个或多个材质定义.）
        for (unsigned int m = 0; m < scene->mNumMaterials; ++m) {
            int textureIndex = 0;
            aiString textureFilename;
            aiReturn isTexturePresent = scene->mMaterials[m]->GetTexture(aiTextureType_DIFFUSE,
                                                                         textureIndex,
                                                                         &textureFilename);
            while (isTexturePresent == AI_SUCCESS) {

                //fill map with textures, OpenGL image ids set to 0
                // 用纹理填充贴图，OpenGL图像id设置为0
                textureNameMap.insert(std::pair<std::string, GLuint>(textureFilename.data, 0));
                // more textures? more than one texture could be associated with a material
                // 更多的纹理?一个材质可以关联多个纹理
                textureIndex++;
                isTexturePresent = scene->mMaterials[m]->GetTexture(aiTextureType_DIFFUSE,
                                                                    textureIndex,
                                                                    &textureFilename);
            }
        }
    } else {
        LOGCATE("Assimp->Textures: Materials is null");
    }


    int numTextures = (int) textureNameMap.size();
    LOGCATE("Assimp->Textures: Textures size：%d", numTextures);

    GLuint *textureGLNames = new GLuint[numTextures];
    /**
     * Description:
     * 生成纹理名称
     * glGenTextures返回一个纹理名称。
     * 不能保证这些名称形成一个连续的整数集;但是，可以保证在调用glGenTextures之前没有任何返回的名称正在使用。
     * 生成的纹理没有维度;它们假定它们第一次绑定到的纹理目标的维度(参见glBindTexture）。
     * 调用glGenTextures返回的纹理名称不会被后续调用返回，除非它们首先被glDeleteTextures删除。
     *
     * 参数1-n:指定要生成的纹理名称的数量。
     * 参数2-textures:指定存储生成的纹理名称的数组。
     */
    // create and fill array with texture names in GL  // 在GL中创建和填充纹理名称数组
    glGenTextures(numTextures, textureGLNames); // 生成纹理名称

    // Extract the directory part from the file name // 从文件名中提取将用于读取纹理的目录部分
    // will be used to read the texture
    std::string modelTextureDirectory = GetDirectoryName(modelFilePath);
    LOGCATE("Assimp->Textures: Textures directory：%s", modelTextureDirectory.c_str());

    // iterate over the textures, read them using OpenCV, load into GL
    // 迭代纹理，使用OpenCV读取它们，加载到GL
    std::map<std::string, GLuint>::iterator textureIterator = textureNameMap.begin();
    int i = 0;
    for (; textureIterator != textureNameMap.end(); ++i, ++textureIterator) {

        std::string textureFilename = (*textureIterator).first;  // get filename
        LOGCATE("Assimp->Textures: the %d-th Textures fileName：%s", i, textureFilename.c_str());
        std::string textureFullPath = modelTextureDirectory + "/" + textureFilename;
        LOGCATE("Assimp->Textures: the %u-th Textures file full path：%s ", i,
                textureFullPath.c_str());
        (*textureIterator).second = textureGLNames[i];      // save texture id for filename in map // 保存贴图中文件名的纹理id

        // load the texture using OpenCV // 使用OpenCV加载这个纹理
        cv::Mat textureImage = cv::imread(textureFullPath);
        LOGCATE("OpenCV->Textures: imread");
        if (!textureImage.empty()) {
            LOGCATE("OpenCV->Textures: Mat non-null ");
            // opencv reads textures in BGR format, change to RGB for GL
            // opencv以BGR格式读取纹理，为GL更改为RGB
            cv::cvtColor(textureImage, textureImage, CV_BGR2RGB);
            // opencv reads image from top-left, while GL expects it from bottom-left
            // opencv从左上角读取图像，而GL期望从左下角读取图像
            // vertically flip the image // 垂直翻转图像
            cv::flip(textureImage, textureImage, 0);


            /**
             * Description:
             * 将命名纹理绑定到纹理目标
             * glBindTexture让你创建或使用命名纹理。在目标设置为GL_TExTURE_2D或GL_TExTURE_CUBE_MAP时调用glBindTexture，
             * 并将纹理设置为新纹理的名称，将纹理名称绑定到当前活动纹理单元的目标。当纹理绑定到目标时，该目标的先前绑定将自动中断。
             * 纹理名称是无符号整数。保留0值来表示每个纹理目标的默认纹理。纹理名称和对应的纹理内容是当前GL渲染上下文的共享对象空间的本地内容。
             * 你可以使用glGenTextures来生成一组新的纹理名称。
             * 当一个纹理第一次绑定时，它假定指定的目标:一个纹理首先绑定到GL, TExTuRE_ 2D成为一个二维纹理，
             * 一个纹理首先绑定到GL_TEXTURE_CUBE_MAP成为一个立方体映射纹理。
             * 二维纹理在第一次绑定后的状态与GL初始化时默认的CL_TEXTURE_2D的状态相同，对于立方体映射的纹理也是如此。
             * 当纹理被绑定时，GL对被绑定目标的操作会影响被绑定的纹理，而对被绑定目标的查询会返回被绑定纹理的状态。
             * 实际上，纹理目标成为当前绑定到它们的纹理的别名，纹理名称0指的是初始化时绑定到它们的默认纹理。
             * 使用glBindTexture创建的纹理绑定保持活动状态，直到不同的纹理被绑定到相同的目标，或者直到绑定的纹理被glDeleteTextures删除。
             * 一旦创建，命名纹理可以根据需要随时重新绑定到相同的原始目标。
             * 使用giBindTexturel将现有的命名纹理绑定到纹理目标之一通常比使用glTexlmage2D重新加载纹理图像要快得多。
             *
             * 参数1-target:指定纹理绑定到的活动纹理单元的目标。
             *              必须是GL_TExTuRE_2D
             *              或GL_TExTURE_CUBE_MAP。
             * 参数2-texture:指定纹理的名称。
             */
            // bind the texture // 绑定纹理
            glBindTexture(GL_TEXTURE_2D, textureGLNames[i]); // 将命名纹理绑定到纹理目标
            LOGCATE("OpenCV->Textures: Bind Textures--> name= %d ", textureGLNames[i]);

            // specify linear filtering  // 指定线性滤波
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

            /**
             * 指定二维纹理图像
             * Description:
             * 纹理将指定纹理图像的一部分映射到纹理处于活动状态的每个图形原语上。
             * 纹理是活动的当前的片段着色器或顶点着色器使用内置的纹理查找函数。
             * 要定义纹理图像，调用glTexImage2D
             * 。参数描述了纹理图像的参数，如高度、宽度、level-of- 1详细编号(参见glTexParameter)和格式。
             * 最后三个参数描述了图像如何在内存中表示。
             * 根据类型，从数据中以无符号字节或短序列的形式读取数据。当type为GL_UNSIGNED_BYTE时，每个字节被解释为一个颜色组件。
             * 当type为GL_UNSIGNED_SHoRT_5_6_5、GL_UNSIGNED_SHORT_4_4_4_4或GL_UNSIGNED_SHORT_5_5_5_1之一时，
             * 每个无符号短值被解释为包含单个texel的所有组件，颜色组件根据格式排列。
             * 颜色组件被视为一组、两组、三组或四组值，同样基于格式。组件组被称为texel。
             * 宽度x高度像素从内存中读取，从位置数据开始。默认情况下，这些文本从相邻的内存位置获取，
             * 除了在读取所有宽度文本之后，读取指针被推进到下一个四字节边界。
             * 四字节的行对齐由glPixelStorei用参数GL_UNPACK_ALIGNMENT指定，它可以设置为1、2、4或8个字节。
             * 第一个元素对应于纹理图像的左下角。后续元素从左到右依次遍历纹理图像中最低行的剩余纹理，
             * 然后依次遍历纹理图像中较高的行。最后一个元素对应于纹理图像的右上角。
             *
             * 参数1-target:指定活动纹理单元的目标纹理。必须是GL_TEXTURE_2D、GL_TEXTURE_CUBE_MAP_POSITIVE_X、
             *                                        GL_TEXTURE_CUBE MAP_NEGATIVE_X、
             *                                        GL_TEXTURE_CUBE_MAP_POSITIVE_Y、
             *                                        GL_TEXTURE_CUBE_MAP_NEGATIVE_Y、
             *                                        GL_TEXTURE_CUBE_MAP_POSITIVE_Z
             *                                        或GL_TEXTURE_CUBE_MAP_NEGATIVE_Z。
             * 参数2-level:突出的数字。O级是base image。n级是nth mipmap减减图像。
             * 参数3-internalformat:指定纹理的内部格式。必须是以下符号常量之一:GL_ALPHA,
             *                                      GL_LUMINANCE, GL_LUMINANCE_ALPHA，GL_RGB，GL_RGBA。
             * 参数4-width:指定纹理图像的宽度。所有实现都支持至少64个像素宽的2D纹理图像和至少16个像素宽的立方体贴图纹理图像。
             * 参数5-height:所有实现都支持至少64个像素高的2D纹理图像和至少16个像素高的立方体贴图纹理图像。
             * 参数6-border:指定边框的宽度。必须是0。
             * 参数7-format:指定文本数据的格式。必须匹配内部格式。可以接受以下符号值:GL_ALPHA、GL_RGB、GL_RGBA、
             *                                                          GL_LUMINANCE和GL_LUMINANCE_ALPHA。
             * 参数8-type:指定文本数据的数据类型。可以接受以下符号值:GL_UNSIGNED_BYTE、
             *                                             GL_UNSIGNED_SHORT_5_6_5、
             *                                             GL_UNSIGNED_SHORT_4_4_4_4
             *                                             和GL_UNSIGNED_SHORT_5_5_5_1。
             * 参数9-data:指定指向内存中图像数据的指针。
             */
            // load the OpenCV Mat into GLES // 加载OpenCV Mat到GLES
            LOGCATE("OpenCV->Textures: Textures target--> width= %d height= %d pixels= %d",
                    textureImage.cols,
                    textureImage.rows, textureImage.data);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureImage.cols,
                         textureImage.rows, 0, GL_RGB, GL_UNSIGNED_BYTE,
                         textureImage.data);  // 指定二维纹理图像
        } else {
            LOGCATE("OpenCV->Textures: Mat is null");
            //Cleanup and return  // 清理并返回
            delete[] textureGLNames;
            return false;
        }
    }

    //Cleanup and return
    delete[] textureGLNames;
    return true;
}

void AssimpMate::ReadModel() {
    scene = importer->ReadFile(source,
                               aiProcessPreset_TargetRealtime_Quality
//                                              | aiProcess_Triangulate
//                                              | aiProcess_FlipUVs
//                                              | aiProcess_GenSmoothNormals
//                                              | aiProcess_CalcTangentSpace
//                                              | aiProcess_JoinIdenticalVertices
//                                              | aiProcess_SortByPType
    );

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
    {
        LOGCATE("Assimp->ReadModel: path= %s, ReadModel Error= %s", source.c_str(),
                importer->GetErrorString());
        return;
    } else {
        LOGCATE("Assimp->ReadModel: ReadModel succeed path= %s", source.c_str());
    }

    if (!LoadTexturesToGL(source)) {
        LOGCATE("Assimp->ReadModel: Unable to load textures");
        return;
    }

    GenerateGLBuffers();

}

void AssimpMate::init(std::string modelPath) {
    source = modelPath;
    LOGCATE("Assimp->init: init source: %s", source.c_str());
}


