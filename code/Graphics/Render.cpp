//
// Created by caspasex on 2020/6/29.
//

#include "Render.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <Graphics/Camera.h>
#include <Graphics/Shader.h>

#include <iostream>
#include <unordered_map>
#include "Config.h"

#include "Model.h"
#include "Data.h"


int Render::init() {
    characters.emplace_back(new Model());
    characters.emplace_back(new Model());
    characters[0]->load(RES_DIR"untitled.gltf");
    characters[1]->load(RES_DIR"bee.dae");
    return 0;
}

int Render::draw() {
    float &currentFrame = worldData->currentFrame;

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, worldData->d->_window->_bw, worldData->d->_window->_bh);

    glm::mat4 projection = glm::perspective(worldData->camera.Zoom,
                                            float(worldData->w) / float(worldData->h),
                                            0.1f, 100.0f);
    glm::mat4 view = worldData->camera.GetViewMatrix();
    glm::mat4 model = glm::mat4(1.0f);
    glm::vec3 lightPos = glm::vec3(3 * cos(currentFrame), 3, 3 * sin(currentFrame));


    model = glm::mat4(1.0f);
    model = scale(model, glm::vec3(0.1f));
    model = translate(model, glm::vec3(0, -2.0, 0));
    model = rotate(model, glm::radians(-90.0f), glm::vec3(0, 1, 0));
    characters[0]->draw(model, view, projection, worldData->camera.Position, lightPos, currentFrame);

    model = glm::mat4(1.0f);
    model = scale(model, glm::vec3(0.05f));
    model = translate(model, glm::vec3(0, -2.0, 0));
    model = rotate(model, glm::radians(-90.0f), glm::vec3(1, 0, 0));
    characters[1]->draw(model, view, projection, worldData->camera.Position, lightPos, currentFrame);

    model = translate(model, glm::vec3(-10, 0.0, 0));
    characters[1]->draw(model, view, projection, worldData->camera.Position, lightPos, currentFrame);
    return 0;
}