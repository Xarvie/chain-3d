//
// Created by CaspaseX on 10/04/2019.
//

#pragma once
#ifndef INC_3D_DATA_H
#define INC_3D_DATA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GameLogic/Bomber.h>

#include "Graphics/Camera.h"

#include "Device.h"

#include "Collision.h"
#include "map.h"

class Data {

};
class Device;
class WorldData {
public:
    WorldData() {
        init();
    }

    void init();

    void updateTime(float curTime) {
        currentFrame = curTime;
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
    }

    int r = 0;
    int g = 0;
    int b = 0;

    glm::vec3 light2Pos;
    glm::vec3 light1Pos;
    glm::vec3 lookCenterPos;
    glm::vec3 lookUpPos;

    glm::vec3 light1Offset;


    float orthoLeft = 0.0;
    float orthoRight = 0.0;
    float orthoBottom = 0.0;
    float orthoTop = 0.0;
    float near_plane = 0.0;
    float far_plane = 0.0;
    float ro = 0.0;
    Camera camera;

    int ssao = 0;


    float lastX = 0;
    float lastY = 0;
    bool firstMouse = true;

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;


    float currentFrame = 0.0;

    Device * d = nullptr;
    int w = 0;
    int h = 0;

    int SHADOW_WIDTH = 8192;
    int SHADOW_HEIGHT = 8192;

    glm::mat4 lightSpaceMatrix;

    int shadowOn = 1;
    float offset1 = 0.4;
    float offset2 = 1.0;
    int bloomOn = 1;
    int particleOn = 1;
    glm::mat4 proj;

    bool vsync = true;
    int MSAA = 2;

    Collision worldCollision;


    Map map1;
    Unit *unit1 = nullptr;
    Bomber* bomber;
};

extern WorldData* worldData;

#endif //INC_3D_DATA_H
