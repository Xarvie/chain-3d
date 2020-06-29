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

class Data {

};

class WorldData {
public:
    WorldData() {
        init();
    }

    void init() {

        camera = glm::vec3(0.0f, 0.0f, 5.0f);
        glm::vec3 light1Offset = glm::vec3(1, 1, 1);

        light1Pos = glm::vec3(0, 16, 0);
        lookCenterPos = glm::vec3(0, 0.0f, 5.0f);
        lookUpPos = glm::vec3(0, 1, 0);

        orthoLeft = -32;
        orthoRight = 32;
        orthoBottom = -32;
        orthoTop = 32;
        near_plane = 0.1;
        far_plane = 32;
        ro = -1.5f;
    }

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


    int SCR_WIDTH = 1024;
    int SCR_HEIGHT = 768;

    float lastX = (float) SCR_WIDTH / 2.0;
    float lastY = (float) SCR_HEIGHT / 2.0;
    bool firstMouse = true;

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;


    float currentFrame = 0.0f;
};

extern WorldData worldData;

#endif //INC_3D_DATA_H
