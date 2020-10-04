//
// Created by caspase on 9/6/2020.
//

#ifndef INC_3D_COMPONENT_H
#define INC_3D_COMPONENT_H

#include "vec3r.h"
#include <vector>
#include <map>

struct AABBData {
    vec3r _min;
    vec3r _max;
};

struct MoveComponent
{
    Real moveSpeed = 8_r/100_r;

};

struct PosComponent
{
    vec3r pos;
};

struct CollisionComponent
{
    AABBData aabb;
};

struct ModelComponent
{
    int spiritModelId;
    bool anim = false;
    int modelID = 0;
    float transx = 0;
    float transy = 0;
    float transz = 0;
};

struct Unit {
    MoveComponent moveObj;
    PosComponent posObj;
    CollisionComponent collisionObj;
    ModelComponent modelObj;
    int mapID = 0;
    int uid = 0;
};

struct Map
{
    int index;
    std::vector<Unit> spiritSet;
    std::vector<Unit> unitSet;
    std::map<int64_t, Unit> data;
};

struct GameData{
    std::vector<Map> maps;
};

#endif //INC_3D_COMPONENT_H
