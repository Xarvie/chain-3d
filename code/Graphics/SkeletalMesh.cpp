//
// Created by caspasex on 2019/10/17.
//


#include "SkeletalMesh.h"

enum {
    POSITION_LOCATION,
    TEX_COORD_LOCATION,
    NORMAL_LOCATION,
    BONE_ID_LOCATION,
    BONE_WEIGHT_LOCATION
};

void SkeletalMesh::VertexBoneData::addBoneData(unsigned int BoneID, float Weight) {
    for (unsigned int i = 0; i < NUM_BONES_PER_VERTEX; i++) {
        if (_weights[i] == 0.0) {
            _ids[i] = BoneID;
            _weights[i] = Weight;
            return;
        }
    }
    assert(0);
}

SkeletalMesh::SkeletalMesh() {
    _meshVAO = 0;
    for (auto &i:_buffers)
        i = 0;
    _numBones = 0;
    _pScene = nullptr;
}


SkeletalMesh::~SkeletalMesh() {
    clear();
}

void SkeletalMesh::clear() {
    if (_buffers[0] != 0) {
        glDeleteBuffers(NUM_VBs, _buffers);
    }

    if (_meshVAO != 0) {
        glDeleteVertexArrays(1, &_meshVAO);
        _meshVAO = 0;
    }
}


bool SkeletalMesh::loadMesh(const std::string &filename) {
    clear();
    std::string::size_type SlashIndex = filename.find_last_of('/');

    if (SlashIndex == std::string::npos) {
        _dir = ".";
    } else if (SlashIndex == 0) {
        _dir = "/";
    } else {
        _dir = filename.substr(0, SlashIndex);
    }

    glGenVertexArrays(1, &_meshVAO);
    glBindVertexArray(_meshVAO);
    glGenBuffers(NUM_VBs, _buffers);

    bool Ret = false;
    _pScene = _importer.ReadFile(filename.c_str(),
                                 aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs |
                                 aiProcess_JoinIdenticalVertices);

    if (_pScene) {
        _globalInverseTransform = toGlmMat4(_pScene->mRootNode->mTransformation);
        _globalInverseTransform = glm::inverse(_globalInverseTransform);
        processNode(_pScene->mRootNode, _pScene);
        Ret = initFromScene(_pScene, filename);
    } else {
        std::cout << "Error parsing " << filename.c_str() << " " << _importer.GetErrorString() << std::endl;
    }
    glBindVertexArray(0);
    return Ret;
}

void SkeletalMesh::processNode(aiNode *node, const aiScene *scene) {
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        for (unsigned int j = 0; j < mesh->mNumVertices; j++) {
            mesh->mVertices[j] = node->mTransformation * mesh->mVertices[j];
        }
    }
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene);
    }

}

bool SkeletalMesh::initFromScene(const aiScene *pScene, const std::string &filename) {
    _meshData.resize(pScene->mNumMeshes);

    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> texCoords;
    std::vector<VertexBoneData> bones;
    std::vector<unsigned int> indices;
    unsigned int NumVertices = 0;
    unsigned int NumIndices = 0;


    for (unsigned int i = 0; i < _meshData.size(); i++) {

        _meshData[i].numIndices = pScene->mMeshes[i]->mNumFaces * 3;
        _meshData[i].baseVertex = NumVertices;
        _meshData[i].baseIndex = NumIndices;

        NumVertices += pScene->mMeshes[i]->mNumVertices;
        NumIndices += _meshData[i].numIndices;

        int MaterialIndex = (int)pScene->mMeshes[i]->mMaterialIndex;
        initMeshMaterial(pScene->mMaterials[MaterialIndex], _meshData[i]._textures);
    }

    positions.reserve(NumVertices);
    normals.reserve(NumVertices);
    texCoords.reserve(NumVertices);
    bones.resize(NumVertices);
    indices.reserve(NumIndices);

    for (unsigned int i = 0; i < _meshData.size(); i++) {
        const aiMesh *paiMesh = pScene->mMeshes[i];
        initMesh(i, paiMesh, positions, normals, texCoords, bones, indices);
    }

    glBindBuffer(GL_ARRAY_BUFFER, _buffers[POS_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions[0]) * positions.size(), &positions[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(POSITION_LOCATION);
    glVertexAttribPointer(POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, _buffers[TEXCOORD_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords[0]) * texCoords.size(), &texCoords[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(TEX_COORD_LOCATION);
    glVertexAttribPointer(TEX_COORD_LOCATION, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, _buffers[NORMAL_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(normals[0]) * normals.size(), &normals[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(NORMAL_LOCATION);
    glVertexAttribPointer(NORMAL_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, _buffers[BONE_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(bones[0]) * bones.size(), &bones[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(BONE_ID_LOCATION);
    glVertexAttribIPointer(BONE_ID_LOCATION, 4, GL_INT, sizeof(VertexBoneData), (const GLvoid *) nullptr);
    glEnableVertexAttribArray(BONE_WEIGHT_LOCATION);
    glVertexAttribPointer(BONE_WEIGHT_LOCATION, 4, GL_FLOAT, GL_FALSE, sizeof(VertexBoneData), (const GLvoid *) 16);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffers[INDEX_BUFFER]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return true;
}

void SkeletalMesh::initMesh(unsigned int Index, const aiMesh *paiMesh, std::vector<glm::vec3> &positions,
                            std::vector<glm::vec3> &normals,
                            std::vector<glm::vec2> &texCoords, std::vector<VertexBoneData> &bones,
                            std::vector<unsigned int> &indices) {

    const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

    for (unsigned int i = 0; i < paiMesh->mNumVertices; i++) {

        paiMesh->mVertices[i] = paiMesh->mVertices[i];
        const aiVector3D *pPos = &(paiMesh->mVertices[i]);
        const aiVector3D *pNormal = paiMesh->HasNormals() ? &(paiMesh->mNormals[i]) : &Zero3D;
        const aiVector3D *pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &Zero3D;

        positions.emplace_back(pPos->x, pPos->y, pPos->z);
        normals.emplace_back(glm::vec3(pNormal->x, pNormal->y, pNormal->z));
        texCoords.emplace_back(glm::vec2(pTexCoord->x, pTexCoord->y));
    }

    loadBones(Index, paiMesh, bones);

    for (unsigned int i = 0; i < paiMesh->mNumFaces; i++) {
        const aiFace &Face = paiMesh->mFaces[i];
        assert(Face.mNumIndices == 3);
        indices.push_back(Face.mIndices[0]);
        indices.push_back(Face.mIndices[1]);
        indices.push_back(Face.mIndices[2]);
    }

}

void SkeletalMesh::initMeshMaterial(const aiMaterial *pMaterial, std::vector<Texture> &mesh_textures) {

    if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
        mesh_textures.push_back(loadMaterialFile(pMaterial, aiTextureType_DIFFUSE, DIFFUSE));
    }
    if (pMaterial->GetTextureCount(aiTextureType_SPECULAR) > 0) {
        mesh_textures.push_back(loadMaterialFile(pMaterial, aiTextureType_SPECULAR, SPECULAR));
    }
    if (pMaterial->GetTextureCount(aiTextureType_HEIGHT) > 0) {
        mesh_textures.push_back(loadMaterialFile(pMaterial, aiTextureType_HEIGHT, NORMAL));
    }
}

Texture SkeletalMesh::loadMaterialFile(const aiMaterial *pMaterial, aiTextureType aiType, TextureEnum texEnum) {
    aiString Path;
    pMaterial->GetTexture(aiType, 0, &Path);
    std::string p(Path.data);

    if (p.substr(0, 2) == ".\\") {
        p = p.substr(2, p.size() - 2);
    }
    std::string FullPath = _dir + "/" + p;

    for (auto i: _textures_Loaded) {
        if (i.getFilename() == FullPath) {
            return i;
        }
    }

    Texture tex(GL_TEXTURE_2D, FullPath, texEnum);
    _textures_Loaded.push_back(tex);
    return tex;

}

void SkeletalMesh::loadBones(unsigned int MeshIndex, const aiMesh *pMesh, std::vector<VertexBoneData> &bones) {
    for (unsigned int i = 0; i < pMesh->mNumBones; i++) {
        unsigned int BoneIndex;
        std::string BoneName(pMesh->mBones[i]->mName.data);

        if (_boneMapping.find(BoneName) == _boneMapping.end()) {
            BoneIndex = _numBones;
            _numBones++;
            BoneInfo bi;
            _boneInfo.push_back(bi);
            _boneInfo[BoneIndex]._boneOffset = toGlmMat4(pMesh->mBones[i]->mOffsetMatrix);
            _boneMapping[BoneName] = BoneIndex;
        } else {
            BoneIndex = _boneMapping[BoneName];
        }

        for (unsigned int j = 0; j < pMesh->mBones[i]->mNumWeights; j++) {
            unsigned int VertexID = _meshData[MeshIndex].baseVertex + pMesh->mBones[i]->mWeights[j].mVertexId;
            float Weight = pMesh->mBones[i]->mWeights[j].mWeight;
            bones[VertexID].addBoneData(BoneIndex, Weight);
        }
    }
}


void SkeletalMesh::draw() {
    glBindVertexArray(_meshVAO);
    const int SHADOW_INDEX = 1;
    for (auto & meshData : _meshData) {
        for (auto & _texture : meshData._textures) {
            std::string n;
            switch (_texture.getTextureType()) {
                case DIFFUSE:
                    n = "diffuseTexture";
                    _texture.bind(GL_TEXTURE0+SHADOW_INDEX);
                    break;
                case SPECULAR:
                    n = "specularTexture";
                    _texture.bind(GL_TEXTURE1+SHADOW_INDEX);
                    break;
                case NORMAL:
                    n = "normalTexture";
                    _texture.bind(GL_TEXTURE2+SHADOW_INDEX);
                    break;
                default:
                    break;
            }
        }

        glDrawElementsBaseVertex(GL_TRIANGLES, meshData.numIndices, GL_UNSIGNED_INT,
                                 (void *) (sizeof(unsigned int) * meshData.baseIndex),
                                 meshData.baseVertex);

    }

    glBindVertexArray(0);
}


void SkeletalMesh::boneTransform(float timeInSeconds, std::vector<glm::mat4> &transforms) {
    glm::mat4 identity(1.0);
    if (_pScene->mAnimations == nullptr)
        return;
    auto TicksPerSecond = (float) (_pScene->mAnimations[0]->mTicksPerSecond != 0
                                    ? _pScene->mAnimations[0]->mTicksPerSecond : 25.0f);
    float TimeInTicks = timeInSeconds * TicksPerSecond;
    float AnimationTime = fmod(TimeInTicks, (float) _pScene->mAnimations[0]->mDuration);

    readNodeHierarchy(AnimationTime, _pScene->mRootNode, identity);

    transforms.resize(_numBones);

    for (unsigned int i = 0; i < _numBones; i++) {
        transforms[i] = _boneInfo[i]._finalTransformation;
    }
}


void SkeletalMesh::readNodeHierarchy(float animationTime, const aiNode *pNode, const glm::mat4 &parentTransform) {
    std::string nodeName(pNode->mName.data);

    const aiAnimation *pAnim = _pScene->mAnimations[0];

    glm::mat4 nodeTransformation = toGlmMat4(pNode->mTransformation);

    const aiNodeAnim *pNodeAnim = findNodeAnim(pAnim, nodeName);

    if (pNodeAnim) {
        aiVector3D s;
        calcInterpolatedScaling(s, animationTime, pNodeAnim);
        glm::mat4 sMat4 = glm::mat4(1.0);
        sMat4 = glm::scale(sMat4, glm::vec3(s.x, s.y, s.z));

        aiQuaternion r;
        calcInterpolatedRotation(r, animationTime, pNodeAnim);
        glm::mat4 rMat4 = toGlmMat4(r.GetMatrix());

        aiVector3D t;
        calcInterpolatedPosition(t, animationTime, pNodeAnim);
        glm::mat4 tMat4 = glm::mat4(1.0);
        tMat4 = glm::translate(tMat4, glm::vec3(t.x, t.y, t.z));

        nodeTransformation = tMat4 * rMat4 * sMat4;
    }

    glm::mat4 globalTransformation = parentTransform * nodeTransformation;

    if (_boneMapping.find(nodeName) != _boneMapping.end()) {
        unsigned int boneID = _boneMapping[nodeName];
        _boneInfo[boneID]._finalTransformation =
                _globalInverseTransform * globalTransformation * _boneInfo[boneID]._boneOffset;
    }

    for (unsigned int i = 0; i < pNode->mNumChildren; i++) {
        readNodeHierarchy(animationTime, pNode->mChildren[i], globalTransformation);
    }
}

const aiNodeAnim *SkeletalMesh::findNodeAnim(const aiAnimation *pAnim, const std::string& nodeName) {
    for (unsigned int i = 0; i < pAnim->mNumChannels; i++) {
        const aiNodeAnim *pNodeAnim = pAnim->mChannels[i];

        if (std::string(pNodeAnim->mNodeName.data) == nodeName) {
            return pNodeAnim;
        }
    }

    return nullptr;
}


void SkeletalMesh::calcInterpolatedPosition(aiVector3D &out, float animationTime, const aiNodeAnim *pNodeAnim) {
    if (pNodeAnim->mNumPositionKeys == 1) {
        out = pNodeAnim->mPositionKeys[0].mValue;
        return;
    }

    unsigned int PositionIndex = findPosition(animationTime, pNodeAnim);
    unsigned int NextPositionIndex = (PositionIndex + 1);
    assert(NextPositionIndex < pNodeAnim->mNumPositionKeys);
    auto deltaTime = (float) (pNodeAnim->mPositionKeys[NextPositionIndex].mTime -
                               pNodeAnim->mPositionKeys[PositionIndex].mTime);
    float factor = (animationTime - (float) pNodeAnim->mPositionKeys[PositionIndex].mTime) / deltaTime;
    assert(factor >= 0.0f && factor <= 1.0f);
    const aiVector3D &start = pNodeAnim->mPositionKeys[PositionIndex].mValue;
    const aiVector3D &end = pNodeAnim->mPositionKeys[NextPositionIndex].mValue;
    aiVector3D Delta = end - start;
    out = start + factor * Delta;
}


void SkeletalMesh::calcInterpolatedRotation(aiQuaternion &out, float animationTime, const aiNodeAnim *pNodeAnim) {
    if (pNodeAnim->mNumRotationKeys == 1) {
        out = pNodeAnim->mRotationKeys[0].mValue;
        return;
    }

    unsigned int RotationIndex = findRotation(animationTime, pNodeAnim);
    unsigned int NextRotationIndex = (RotationIndex + 1);
    assert(NextRotationIndex < pNodeAnim->mNumRotationKeys);
    auto DeltaTime = (float) (pNodeAnim->mRotationKeys[NextRotationIndex].mTime - // gltf 416.66 dae 0.66
                               pNodeAnim->mRotationKeys[RotationIndex].mTime);      // gltf 41.666 dae 0.625
    float Factor = (animationTime - (float) pNodeAnim->mRotationKeys[RotationIndex].mTime) / DeltaTime;
    assert(Factor >= 0.0f && Factor <= 1.0f);
    const aiQuaternion &StartRotationQ = pNodeAnim->mRotationKeys[RotationIndex].mValue;
    const aiQuaternion &EndRotationQ = pNodeAnim->mRotationKeys[NextRotationIndex].mValue;
    aiQuaternion::Interpolate(out, StartRotationQ, EndRotationQ, Factor);
    out = out.Normalize();
}


void SkeletalMesh::calcInterpolatedScaling(aiVector3D &out, float animationTime, const aiNodeAnim *pNodeAnim) {
    if (pNodeAnim->mNumScalingKeys == 1) {
        out = pNodeAnim->mScalingKeys[0].mValue;
        return;
    }

    unsigned int scalingIndex = findScaling(animationTime, pNodeAnim);
    unsigned int nextScalingIndex = (scalingIndex + 1);
    assert(nextScalingIndex < pNodeAnim->mNumScalingKeys);
    auto DeltaTime = (float) (pNodeAnim->mScalingKeys[nextScalingIndex].mTime -
                               pNodeAnim->mScalingKeys[scalingIndex].mTime);
    float Factor = (animationTime - (float) pNodeAnim->mScalingKeys[scalingIndex].mTime) / DeltaTime;
    assert(Factor >= 0.0f && Factor <= 1.0f);
    const aiVector3D &Start = pNodeAnim->mScalingKeys[scalingIndex].mValue;
    const aiVector3D &End = pNodeAnim->mScalingKeys[nextScalingIndex].mValue;
    aiVector3D Delta = End - Start;
    out = Start + Factor * Delta;
}


unsigned int SkeletalMesh::findPosition(float animationTime, const aiNodeAnim *pNodeAnim) {
    for (unsigned int i = 0; i < pNodeAnim->mNumPositionKeys - 1; i++) {
        if (animationTime < (float) pNodeAnim->mPositionKeys[i + 1].mTime) {
            return i;
        }
    }
    assert(0);
    return 0;
}

unsigned int SkeletalMesh::findRotation(float animationTime, const aiNodeAnim *pNodeAnim) {
    assert(pNodeAnim->mNumRotationKeys > 0);

    for (unsigned int i = 0; i < pNodeAnim->mNumRotationKeys - 1; i++) {
        if (animationTime < (float) pNodeAnim->mRotationKeys[i + 1].mTime) {
            return i;
        }
    }
    assert(0);
    return 0;
}


unsigned int SkeletalMesh::findScaling(float animationTime, const aiNodeAnim *pNodeAnim) {
    assert(pNodeAnim->mNumScalingKeys > 0);

    for (unsigned int i = 0; i < pNodeAnim->mNumScalingKeys - 1; i++) {
        if (animationTime < (float) pNodeAnim->mScalingKeys[i + 1].mTime) {
            return i;
        }
    }
    assert(0);
    return 0;
}

glm::mat4 SkeletalMesh::toGlmMat4(const aiMatrix4x4 &m) {
    glm::mat4 matrix = glm::make_mat4(&m[0][0]);
    return glm::transpose(matrix);
}

glm::mat4 SkeletalMesh::toGlmMat4(const aiMatrix3x3 &m) {
    glm::mat3 matrix = glm::make_mat3(&m[0][0]);
    return glm::transpose(glm::mat4(matrix));
}
