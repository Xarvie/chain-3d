//
// Created by CaspaseX on 10/04/2019.
//


#include "Data.h"
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

}