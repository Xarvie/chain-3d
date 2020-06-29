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

enum SHADER_LOGIC_TYPE
{
    SHADER_LOGIC_TYPE_ANIM_MODEL = 0,
    SHADER_LOGIC_TYPE_STATIC_MODEL = 1,
    END
};
class Shader;

class Model {
public:
    int load(std::string str);
    void draw(glm::mat4 M, glm::mat4 V, glm::mat4 P, glm::vec3 cameraPos, glm::vec3 lightPos, float currentFrame);

protected:
    std::vector<SkeletalMesh*> AniMeshes;
    std::vector<SkeletalMesh*> staticMeshes;
    static std::vector<Shader *> shader;
};


#endif //INC_3D_MODEL_H
