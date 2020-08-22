//
// Created by caspase on 7/24/2020.
//

#ifndef INC_3D_UNIT_H
#define INC_3D_UNIT_H

#include "Collision.h"
#include "Render.h"
#include "real.h"
#include "vec3r.h"
class AABB;

struct MoveObj
{
    int move(real degree);
    real moveSpeed = Real::Div(Real::FromInt(8), Real::FromInt(100));
    vec3r* pos = nullptr;
    AABB* aabb = nullptr;
};

class Unit {
public:
    MoveObj moveObj;

    bool anim = 0;
    int modelID = 0;

    float transx = 0;
    float transy = 0;
    float transz = 0;

    vec3r pos;
    int mapID;
};


#endif //INC_3D_UNIT_H
