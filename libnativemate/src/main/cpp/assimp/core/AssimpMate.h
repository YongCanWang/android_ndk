//
// Created by Tom灿 on 2023/11/24.
//

#ifndef ANDROID_JNI_ASSIMPMATE_H
#define ANDROID_JNI_ASSIMPMATE_H

#include <GLES2/gl2.h>
#include <map>
#include <vector>
#include "assimp/Importer.hpp"
#include "string"
#include "fwd.hpp"

class AssimpMate {
public:
    AssimpMate();

    void init(std::string source);

    void ReadModel();

    void Render3DModel(glm::mat4 *mvpMat);

    std::vector<struct MeshInfo> modelMeshes;       // contains one struct for every mesh in model

private:
    Assimp::Importer *importer;
    std::string source;
    const aiScene *scene;  // assimp's output data structure
    std::map<std::string, GLuint> textureNameMap;   // (texture filename, texture name in GL)

    GLuint vertexAttribute, vertexUVAttribute;     // attributes for shader variables
    GLuint shaderProgramID;
    GLint mvpLocation, textureSamplerLocation;    // location of MVP in the shader

    void GenerateGLBuffers();

    bool LoadTexturesToGL(std::string source);

};

// info used to render a mesh
struct MeshInfo {
    GLuint textureIndex;
    int numberOfFaces;
    GLuint faceBuffer;
    GLuint vertexBuffer;
    GLuint textureCoordBuffer;
};


#endif //ANDROID_JNI_ASSIMPMATE_H
