//
// Created by caspasex on 2020/6/29.
//

#include "Model.h"
#include "Shader.h"
#include "Camera.h"
#include "Data.h"


int Model::load(std::string str) {
    mesh = new SkeletalMesh;
    mesh->loadMesh(str);
    if (mesh->hasAnimations())
        return 1;
    else
        return 0;

}


void Model::draw(int isDepth, int bloom,  Shader *curShader, glm::mat4 M, glm::mat4 V, glm::mat4 P,
                 float currentFrame) {
    glm::mat4 MVP = P * V * M;
    curShader->setMat4("M", M);
    curShader->setMat4("lightSpaceMatrix", worldData->lightSpaceMatrix);
    if(isDepth!=1) {
        curShader->setVec3("light.direction", worldData->light1Pos.x,  worldData->light1Pos.y,  worldData->light1Pos.z);
        curShader->setVec3("light.ambient", 0.5f, 0.5f, 0.5f);
        curShader->setVec3("light.diffuse", 1.0f, 1.0f, 1.0f);
        curShader->setVec3("light.specular", 1.0f, 1.0f, 1.0f);

        curShader->setMat4("MVP", MVP);
        curShader->setMat4("lightSpaceMatrix", worldData->lightSpaceMatrix);
    }


    if(mesh->hasAnimations())
    {
        curShader->setInt("anim", 1);
        std::vector<glm::mat4> transforms;
        mesh->boneTransform(currentFrame, transforms);
        for (unsigned int i = 0; i < transforms.size(); i++) {
            curShader->setMat4("gBones[" + std::to_string(i) + "]", transforms[i]);
        }
    } else{
        curShader->setInt("anim", 0);
    }

    mesh->draw();
}

