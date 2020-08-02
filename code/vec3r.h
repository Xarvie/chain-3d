//
// Created by caspase on 7/24/2020.
//

#ifndef INC_3D_VEC3R_H
#define INC_3D_VEC3R_H
#include "real.h"

class vec3r
{
public:
    vec3r()
    {

    }
    vec3r(real xyz){
        this->x = xyz;
        this->y = xyz;
        this->z = xyz;
    }
    vec3r(real x, real y, real z){
        this->x = x;
        this->y = y;
        this->z = z;
    }

//    vec3r(float x, float y, float z){
//        this->x = Real::FromFloat(x);
//        this->y = Real::FromFloat(y);
//        this->z = Real::FromFloat(z);
//    }

    real x;
    real y;
    real z;
};

#endif //INC_3D_VEC3R_H
