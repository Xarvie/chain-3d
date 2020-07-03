//
// Created by caspasex on 2020/6/29.
//

#include "Render.h"

#include <Graphics/Camera.h>
#include <Graphics/Shader.h>

#include "Config.h"
#include "Model.h"
#include "Data.h"

std::vector<Shader *> Render::shader = std::vector<Shader *>(SHADER_LOGIC_TYPE::END, nullptr);
unsigned int Render::depthMapFBO = 0;
unsigned int Render::depthMap = 0;

int Render::init() {
    worldData->proj = glm::perspective(worldData->camera.Zoom,
                                       float(worldData->w) / float(worldData->h),
                                       0.1f, 50.0f);

    if (shader[SHADER_LOGIC_TYPE::SHADER_LOGIC_TYPE_ANIM_MODEL_WITH_SHADOW] == nullptr) {
        shader[SHADER_LOGIC_TYPE::SHADER_LOGIC_TYPE_ANIM_MODEL_WITH_SHADOW] = new Shader(SHADER_DIR"SkeletalModelWithShadow.vert.glsl", SHADER_DIR"SkeletalModelWithShadow.frag.glsl");
    }
    if (shader[SHADER_LOGIC_TYPE::SHADER_LOGIC_TYPE_DEPTH_ANIM] == nullptr) {
        shader[SHADER_LOGIC_TYPE::SHADER_LOGIC_TYPE_DEPTH_ANIM] = new Shader(SHADER_DIR"ShadowMappingDepthSkeletal.vert.glsl", SHADER_DIR"ShadowMappingDepthSkeletal.frag.glsl");
    }
    if (shader[SHADER_LOGIC_TYPE::SHADER_LOGIC_TYPE_DEBUG] == nullptr) {
        shader[SHADER_LOGIC_TYPE::SHADER_LOGIC_TYPE_DEBUG] = new Shader(SHADER_DIR"DebugShadowMapping.vert.glsl", SHADER_DIR"DebugShadowMapping.frag.glsl");
    }


    {
        glGenFramebuffers(1, &Render::depthMapFBO);
        // create depth texture
        glGenTextures(1, &Render::depthMap);
        glBindTexture(GL_TEXTURE_2D, Render::depthMap);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, worldData->SHADOW_WIDTH, worldData->SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
        glBindFramebuffer(GL_FRAMEBUFFER, Render::depthMapFBO);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, Render::depthMap, 0);
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

    }
    {
        auto x = new Model();
        int anim = x->load(RES_DIR"untitled.gltf");
        if(anim)
            animModels.emplace_back(x);
        else
            staticModels.emplace_back(x);
    }

    {
        auto x = new Model();
        int anim = x->load(RES_DIR"bee.dae");
        if(anim)
            animModels.emplace_back(x);
        else
            staticModels.emplace_back(x);
    }


    return 0;
}

int Render::draw() {
    float &currentFrame = worldData->currentFrame;

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, worldData->w, worldData->h);

    glm::mat4 lightProjection, lightView;
    glm::mat4& lightSpaceMatrix = worldData->lightSpaceMatrix;

    lightProjection = glm::ortho(worldData->orthoLeft,worldData->orthoRight, worldData->orthoBottom, worldData->orthoTop, worldData->near_plane, worldData->far_plane);
    lightView = glm::lookAt(glm::vec3(worldData->light1Pos.x, worldData->light1Pos.y, worldData->light1Pos.z), worldData->lookCenterPos, worldData->lookUpPos);
    lightSpaceMatrix = lightProjection * lightView;


    auto & shadowOn = worldData->shadowOn;
    if(shadowOn)
    {
        getDepthMap();
        drawModelWithShadow(true);
    } else{
        drawModelWithShadow(false);
    }



    //showDepthMap();

    return 0;
}

unsigned int quadVAO = 0;
unsigned int quadVBO;
void renderQuad()
{
    if (quadVAO == 0)
    {
        float quadVertices[] = {
                // positions        // texture Coords
                -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
                -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
                1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
                1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        };
        // setup plane VAO
        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    }
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}

void Render::showDepthMap() {
    auto &debugDepthQuad = *shader[SHADER_LOGIC_TYPE::SHADER_LOGIC_TYPE_DEBUG];
    debugDepthQuad.use();
    debugDepthQuad.setInt("depthMap", 0);
    //debugDepthQuad.setFloat("near_plane", worldData->near_plane);
    //debugDepthQuad.setFloat("far_plane", worldData->far_plane);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, Render::depthMap);
    renderQuad();
}

int Render::drawModels(DRAW_TYPE type) {
    float &currentFrame = worldData->currentFrame;
    Shader * curShader = nullptr;

    if(type == DRAW_TYPE::DRAW_TYPE_ANIM_MODEL_WITH_SHADOW || type == DRAW_TYPE::DRAW_TYPE_ANIM_MODEL)
    {
        curShader = Render::shader[SHADER_LOGIC_TYPE::SHADER_LOGIC_TYPE_ANIM_MODEL_WITH_SHADOW];
    }
    else if(type == DRAW_TYPE::DRAW_TYPE_DEPTH)
    {
        curShader = Render::shader[SHADER_LOGIC_TYPE::SHADER_LOGIC_TYPE_DEPTH_ANIM];
    }

    if(curShader == nullptr)
        return -1;
    curShader->use();
    glm::mat4 projection = worldData->proj;
    glm::mat4 view = worldData->camera.getViewMatrix();
    glm::mat4 model = glm::mat4(1.0f);
    glm::vec3 lightPos = glm::vec3(3 * cos(currentFrame), 3, 3 * sin(currentFrame));

    if(type == DRAW_TYPE::DRAW_TYPE_ANIM_MODEL_WITH_SHADOW || type == DRAW_TYPE::DRAW_TYPE_ANIM_MODEL)
    {
        curShader->setVec3("viewPos", worldData->camera.Position);
        curShader->setVec3("lightPos", lightPos);
        curShader->setInt("shadowMap", 0);
        curShader->setInt("diffuseTexture", 1);
        if(type == DRAW_TYPE::DRAW_TYPE_ANIM_MODEL_WITH_SHADOW)
            curShader->setInt("shadowOn", 1);
        else
            curShader->setInt("shadowOn", 0);
    }
    else if(type == DRAW_TYPE::DRAW_TYPE_DEPTH)
    {

    }

    model = glm::mat4(1.0f);
    model = scale(model, glm::vec3(1.0f));
    model = translate(model, glm::vec3(0, -2.0, 0));
    model = rotate(model, glm::radians(-90.0f), glm::vec3(0, 1, 0));

    staticModels[0]->draw(type, curShader, model, view, projection, worldData->camera.Position, lightPos, currentFrame);

    model = glm::mat4(1.0f);
    model = scale(model, glm::vec3(1.0f));
    model = translate(model, glm::vec3(0, 2.0, 0));
    model = rotate(model, glm::radians(-90.0f), glm::vec3(1, 0, 0));
    animModels[0]->draw(type, curShader, model, view, projection, worldData->camera.Position, lightPos, currentFrame);

    model = translate(model, glm::vec3(-10, 0.0, 0));
    animModels[0]->draw(type, curShader, model, view, projection, worldData->camera.Position, lightPos, currentFrame);
    return 0;
}


void Render::getDepthMap() {
    float &currentFrame = worldData->currentFrame;
    glViewport(0, 0, worldData->SHADOW_WIDTH, worldData->SHADOW_HEIGHT);
    glBindFramebuffer(GL_FRAMEBUFFER, Render::depthMapFBO);

    glClear(GL_DEPTH_BUFFER_BIT);
    drawModels(DRAW_TYPE::DRAW_TYPE_DEPTH);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glViewport(0, 0, worldData->w, worldData->h);
}

void Render::drawModelWithShadow(bool shadowOn) {

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, worldData->w, worldData->h);

    if(shadowOn == 1)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, Render::depthMap);
    }

    if(shadowOn)
    {
        drawModels(DRAW_TYPE::DRAW_TYPE_ANIM_MODEL_WITH_SHADOW);
    } else{
        drawModels(DRAW_TYPE::DRAW_TYPE_ANIM_MODEL);
    }

    if(shadowOn == 1) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}