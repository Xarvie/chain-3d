//
// Created by caspasex on 2020/6/29.
//

#pragma once
#ifndef INC_3D_MODEL_H
#define INC_3D_MODEL_H
#include "Config.h"

#include "SkeletalMesh.h"
#include <string>
#include <vector>

class Shader;

class Model {
public:
    int load(std::string str);
    void draw(int isDepth, Shader * curShader, glm::mat4 M, glm::mat4 V, glm::mat4 P, glm::vec3 cameraPos, glm::vec3 lightPos, float currentFrame);
protected:
    SkeletalMesh* mesh = nullptr;
};


#endif //INC_3D_MODEL_H
