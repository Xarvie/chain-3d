//
// Created by caspase on 7/24/2020.
//

#ifndef INC_3D_VEC3R_H
#define INC_3D_VEC3R_H
#include "real.h"
#include "glm/glm.hpp"

class vec3r
{
public:
    vec3r()
    {

    }
    vec3r(Real xyz){
        this->x = xyz;
        this->y = xyz;
        this->z = xyz;
    }
    vec3r(Real x, Real y, Real z){
        this->x = x;
        this->y = y;
        this->z = z;
    }
    vec3r operator-(const vec3r & v){
        return vec3r(this->x - v.x, this->y - v.y, this->z - v.z);
    }

    glm::vec3 glm(){
        return glm::vec3((double)(this->x), (double)(this->y), (double)(this->z));
    }


//    vec3r(float x, float y, float z){
//        this->x = Real::FromFloat(x);
//        this->y = Real::FromFloat(y);
//        this->z = Real::FromFloat(z);
//    }

    Real x;
    Real y;
    Real z;
};

#endif //INC_3D_VEC3R_H
