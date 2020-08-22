//
// Created by caspase on 7/22/2020.
//

#ifndef INC_3D_MAP_H
#define INC_3D_MAP_H

#include <vector>
#include <map>

#include "Unit.h"

class Map
{
public:

    int init(int x, int y, int z)
    {
        return 0;
    }
    int add(Unit* unit){
        glm::int64_t id = (int64_t)unit;
        data[id] = unit;
        return 0;
    }

    int x;
    int y;
    int z;
    std::map<int64_t, Unit*> data;
};

static char map1[15][15] =
        {
                {2, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2,},
                {2, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2,},
                {2, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2,},
                {2, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2,},
                {2, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2,},
                {2, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2,},
                {2, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2,},
                {2, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2,},
                {2, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2,},
                {2, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 2,},
                {2, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2,},
                {2, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2,},
                {2, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2,},
                {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2,},
                {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2,},
        };

struct UnitData{
    vec3r pos;
    int type;

};

struct ResType{
    int modelTypeId;
    const char* modelName;
    glm::vec3 ModelOffset;

    int animW;
    int animH;
    int animAll;
    int pixelX;
    int pixelY;

};

static std::vector<ResType> resType = {
        {0,RES_DIR"2d/bb.png", glm::vec3(0,0,0),5,1,5},
        {1,RES_DIR"2d/boom.png", glm::vec3(0,0,0), 4, 4, 16},
        {2,RES_DIR"2d/ter1.png", glm::vec3(0,0,0),1,1,1},
        {3,RES_DIR"2d/ter2.png", glm::vec3(0,0,0),1,1,1},
        {4,RES_DIR"2d/ter3.png", glm::vec3(0,0,0),1,1,1},
        {5,RES_DIR"2d/ter4.png", glm::vec3(0,0,0),1,1,1},
        {6,RES_DIR"2d/ter5.png", glm::vec3(0,0,0),1,1,1},
        {7,RES_DIR"2d/ter6.png", glm::vec3(0,0,0),1,1,1},
        {8,RES_DIR"2d/ter7.png", glm::vec3(0,0,0),1,1,1},
        {9,RES_DIR"2d/ter8.png", glm::vec3(0,0,0),1,1,1},
        {10,RES_DIR"2d/ter9.png", glm::vec3(0,0,0),1,1,1},
        {11,RES_DIR"2d/ter10.png", glm::vec3(0,0,0),1,1,1},
        };



static std::vector<UnitData> map1Unit = {
        { vec3r(Real::FromInt(2),Real::FromInt(0),Real::FromInt(1)),0},
        { vec3r(Real::FromInt(2),Real::FromInt(1*2),Real::FromInt(0)),1},
        { vec3r(Real::FromInt(2),Real::FromInt(2*2),Real::FromInt(1)),2},
        { vec3r(Real::FromInt(2),Real::FromInt(3*2),Real::FromInt(0)),3},
        { vec3r(Real::FromInt(2),Real::FromInt(4*2),Real::FromInt(1)),4},
        { vec3r(Real::FromInt(2),Real::FromInt(5*2),Real::FromInt(0)),5},
        { vec3r(Real::FromInt(2),Real::FromInt(6*2),Real::FromInt(1)),6},
        { vec3r(Real::FromInt(2),Real::FromInt(7*2),Real::FromInt(0)),7},
        { vec3r(Real::FromInt(2),Real::FromInt(8*2),Real::FromInt(1)),8},
        { vec3r(Real::FromInt(2),Real::FromInt(9*2),Real::FromInt(0)),9},
        { vec3r(Real::FromInt(2),Real::FromInt(10*2),Real::FromInt(1)),10},
        { vec3r(Real::FromInt(2),Real::FromInt(11*2),Real::FromInt(0)),11},
        { vec3r(Real::FromInt(2),Real::FromInt(12*2),Real::FromInt(1)),0},
        { vec3r(Real::FromInt(2),Real::FromInt(13*2),Real::FromInt(0)),0},
        { vec3r(Real::FromInt(2),Real::FromInt(14*2),Real::FromInt(1)),0},
};

#endif //INC_3D_MAP_H
