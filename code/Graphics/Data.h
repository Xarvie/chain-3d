//
// Created by CaspaseX on 10/04/2019.
//

#pragma once
#ifndef INC_3D_DATA_H
#define INC_3D_DATA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Graphics/Camera.h"

#include "Device.h"

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

    int SHADOW_WIDTH = 2048;
    int SHADOW_HEIGHT = 2048;

    glm::mat4 lightSpaceMatrix;

    int shadowOn = 1;
};

extern WorldData* worldData;

#endif //INC_3D_DATA_H
