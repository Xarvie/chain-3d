//
// Created by caspasex on 2019/10/19.
//


#pragma once
#ifndef INC_3D_SKELETALMESH_H
#define INC_3D_SKELETALMESH_H

#include "Config.h"

#include "OpenglHeader.h"
#if defined(USE_ASSIMP)
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#endif
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <TextureEx1.h>
#include <map>
#include <vector>
#include <string>

class SkeletalMesh {
public:
#if !defined(USE_ASSIMP)
    SkeletalMesh(){

    }

    ~SkeletalMesh(){

    }

    bool loadMesh(const std::string &filename){
        return false;
    }

    void draw(){

    }

    [[nodiscard]] unsigned int numBones() const {
        return 0;
    }

    bool hasAnimations() {
        return 0;
    }

    void boneTransform(float timeInSeconds, std::vector<glm::mat4> &transforms){};
#else

    SkeletalMesh();

    ~SkeletalMesh();
    bool loadMesh(const std::string &filename);

    void draw();

    [[nodiscard]] unsigned int numBones() const {
        return _numBones;
    }

    bool hasAnimations() {
        return _pScene->HasAnimations();
    }

    void boneTransform(float timeInSeconds, std::vector<glm::mat4> &transforms);

private:
    static const unsigned int NUM_BONES_PER_VERTEX = 4;

    struct BoneInfo {
        glm::mat4 _boneOffset{};
        glm::mat4 _finalTransformation{};

        BoneInfo() {
            _boneOffset = glm::mat4(0);
            _finalTransformation = glm::mat4(0);
        }
    };

    struct VertexBoneData {
        unsigned int _ids[NUM_BONES_PER_VERTEX]{};
        float _weights[NUM_BONES_PER_VERTEX]{};

        VertexBoneData() {
            reset();
        };

        void reset() {
            for (auto &i:_ids)
                i = 0;
            for (auto &i:_weights)
                i = 0;
        }

        void addBoneData(unsigned int BoneID, float Weight);
    };

    static const unsigned int INVALID_MATERIAL = 0xFFFFFFFF;
    enum VB_TYPES {
        INDEX_BUFFER,
        POS_VB,
        NORMAL_VB,
        TEXCOORD_VB,
        BONE_VB,
        NUM_VBs
    };
    GLuint _meshVAO = 0;
    GLuint _buffers[NUM_VBs]{};

    struct MeshData {
        MeshData() {
            numIndices = 0;
            baseVertex = 0;
            baseIndex = 0;
        }

        unsigned int numIndices;
        unsigned int baseVertex;
        unsigned int baseIndex;
        std::vector<TextureEx1> _textures;
    };

    void processNode(aiNode *node, const aiScene *scene);

    bool initFromScene(const aiScene *pScene, const std::string &filename);

    void initMesh(unsigned int index, const aiMesh *paiMesh, std::vector<glm::vec3> &positions,
                  std::vector<glm::vec3> &normals,
                  std::vector<glm::vec2> &texCoords, std::vector<VertexBoneData> &bones,
                  std::vector<unsigned int> &indices);

    void initMeshMaterial(const aiMaterial *pMaterial, std::vector<TextureEx1> &mesh_textures);

    TextureEx1 loadMaterialFile(const aiMaterial *pMaterial, aiTextureType aiType, TextureEnum texEnum);


    void loadBones(unsigned int meshIndex, const aiMesh *pMesh, std::vector<VertexBoneData> &bones);

    void readNodeHierarchy(float animationTime, const aiNode *pNode, const glm::mat4 &parentTransform);

    static const aiNodeAnim *findNodeAnim(const aiAnimation *pAnim, const std::string& nodeName);

    static void calcInterpolatedScaling(aiVector3D &out, float animationTime, const aiNodeAnim *pNodeAnim);

    static void calcInterpolatedRotation(aiQuaternion &out, float animationTime, const aiNodeAnim *pNodeAnim);

    static void calcInterpolatedPosition(aiVector3D &Out, float animationTime, const aiNodeAnim *pNodeAnim);

    static unsigned int findScaling(float animationTime, const aiNodeAnim *pNodeAnim);

    static unsigned int findRotation(float animationTime, const aiNodeAnim *pNodeAnim);

    static unsigned int findPosition(float animationTime, const aiNodeAnim *pNodeAnim);

    static glm::mat4 toGlmMat4(const aiMatrix4x4 &m);

    static glm::mat4 toGlmMat4(const aiMatrix3x3 &m);

    void clear();

    std::string _dir;
    std::vector<MeshData> _meshData;
    std::vector<TextureEx1> _textures_Loaded;

    std::map<std::string, unsigned int> _boneMapping;
    unsigned int _numBones;
    std::vector<BoneInfo> _boneInfo;
    glm::mat4 _globalInverseTransform{};

    const aiScene *_pScene;
    Assimp::Importer _importer;
#endif
};

#endif
