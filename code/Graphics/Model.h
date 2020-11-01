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
class SkeletalMesh;

class Model {
public:
    int load(std::string str);
    void draw(int isDepth, int bloom, Shader * curShader, glm::mat4 M, glm::mat4 V, glm::mat4 P, float currentFrame);
protected:
    SkeletalMesh* mesh = nullptr;
};


#endif //INC_3D_MODEL_H
