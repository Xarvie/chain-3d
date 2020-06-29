//
// Created by caspasex on 2020/6/29.
//

#include "Model.h"
#include "Shader.h"
#include "Camera.h"

std::vector<Shader *> Model::shader = std::vector<Shader *>(SHADER_LOGIC_TYPE::END, nullptr);

int Model::load(std::string str) {
    SkeletalMesh *mesh = new SkeletalMesh;
    mesh->loadMesh(str);
    if (mesh->hasAnimations())
        this->AniMeshes.push_back(mesh);
    else
        this->staticMeshes.push_back(mesh);
    return 0;
}


void Model::draw(glm::mat4 M, glm::mat4 V, glm::mat4 P, glm::vec3 cameraPos, glm::vec3 lightPos, float currentFrame) {

    if (shader[SHADER_LOGIC_TYPE::SHADER_LOGIC_TYPE_ANIM_MODEL] == nullptr) {
        shader[SHADER_LOGIC_TYPE::SHADER_LOGIC_TYPE_ANIM_MODEL] = new Shader(SHADER_DIR"SkeletalModel.vert.glsl", SHADER_DIR"SkeletalModel.frag.glsl");
    }
    if (shader[SHADER_LOGIC_TYPE::SHADER_LOGIC_TYPE_STATIC_MODEL] == nullptr) {
        shader[SHADER_LOGIC_TYPE::SHADER_LOGIC_TYPE_STATIC_MODEL] = new Shader(SHADER_DIR"StaticModel.vert.glsl", SHADER_DIR"SkeletalModel.frag.glsl");
    }

    using namespace glm;
    //bob render
    {
        Shader *curShader = shader[SHADER_LOGIC_TYPE::SHADER_LOGIC_TYPE_ANIM_MODEL];
        curShader->use();

        mat4 MVP = P * V * M;
        curShader->setMat4("MVP", MVP);
        curShader->setMat4("M", M);
        curShader->setVec3("lightPos", lightPos);
        curShader->setVec3("viewPos", cameraPos);


        for (int i = 0; i < AniMeshes.size(); i++) {
            auto &aniMesh = AniMeshes[i];
            std::vector<mat4> transforms;
            aniMesh->boneTransform(currentFrame, transforms);
            for (unsigned int i = 0; i < transforms.size(); i++) {
                curShader->setMat4("gBones[" + std::to_string(i) + "]", transforms[i]);
            }
            curShader->setInt("diffuseTexture", 0);
            aniMesh->draw();

        }
    }
    {
        Shader *curShader = shader[SHADER_LOGIC_TYPE::SHADER_LOGIC_TYPE_STATIC_MODEL];
        curShader->use();

        mat4 MVP = P * V * M;
        curShader->setMat4("MVP", MVP);
        curShader->setMat4("M", M);
        curShader->setVec3("lightPos", lightPos);
        curShader->setVec3("viewPos", cameraPos);

        for (int i = 0; i < staticMeshes.size(); i++) {
            auto &mesh = staticMeshes[i];
            curShader->setInt("diffuseTexture", 0);
            mesh->draw();
        }
    }


}