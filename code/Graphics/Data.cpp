//
// Created by CaspaseX on 10/04/2019.
//


#include "Data.h"
#include "Component.h"
#include "Device.h"
WorldData* worldData;


void WorldData::init() {

    camera = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 light1Offset = glm::vec3(1, 1, 1);

    light1Pos = glm::vec3(0, 16, 1);
    lookCenterPos = glm::vec3(0, 0.0f, 0.0f);
    lookUpPos = glm::vec3(0, 1, 0);

    orthoLeft = -32;
    orthoRight = 32;
    orthoBottom = -32;
    orthoTop = 32;
    near_plane = 0.1;
    far_plane = 32;
    ro = -1.5f;

    d = new Device();
    bomber = new Bomber();

    std::vector<char> data {
            0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0,
            0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 2, 0, 3, 2, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0,
    };

    //map1.init(15,15,1);
    worldCollision.init(15,15,1);

//    for(int x = 0; x < 15; x++)
//        for(int y = 0; y < 15; y++)
//        {
//            int type = data[x+y*15];
//
//            if(type == 0)
//                continue;
//
//            Unit * u = new Unit();
//            if(type == 3)
//                this->unit1 = u;
//            int z = 0;
//            u->pos.x = Real::FromInt(x);
//            u->pos.y = Real::FromInt(y);
//            u->pos.z = Real::FromInt(z);
//            u->modelID = type;
//            if(type == 3)
//            {
//                u->anim = 1;
//            }
//            u->moveObj.pos = &u->pos;
//            map1.add(u);
//            real half = Real::Div(Real::FromInt(40), Real::FromInt(100));
//            auto * aabb = new AABB(vec3r(Real::Sub(Real::FromInt(x),half), Real::Sub(Real::FromInt(y),half), Real::Sub(Real::FromInt(z), half)), vec3r(Real::Add(Real::FromInt(x),half), Real::Add(Real::FromInt(y), half), Real::Add(Real::FromInt(z),half)));
//            std::cout << "ox,oy:" << Real::ToFloat(Real::Sub(Real::FromInt(x),half)) << "," << Real::ToFloat(Real::FromInt(y)) << std::endl;
//            u->moveObj.aabb = aabb;
//            worldCollision.add(aabb);
//        }



}