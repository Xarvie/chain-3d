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


bool bloom = true;
bool bloomKeyPressed = false;
float exposure = 1.0f;


unsigned int quadVAO = 0;
unsigned int quadVBO;

void renderQuad() {
    if (quadVAO == 0) {
        float quadVertices[] = {
                // positions        // texture Coords
                -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
                -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
                1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
                1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        };
        // setup plane VAO
        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
    }
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}


int Render::init() {

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_CULL_FACE);

    glfwWindowHint(GLFW_SAMPLES, worldData->MSAA);
    glEnable(GL_BLEND);

    if (p == nullptr)
        p = new Particle;
    p->init();
    worldData->proj = glm::perspective(worldData->camera.Zoom,
                                       float(worldData->w) / float(worldData->h),
                                       0.1f, 50.0f);

    if (shader[SHADER_LOGIC_TYPE::SHADER_LOGIC_TYPE_ANIM_MODEL_WITH_SHADOW] == nullptr) {
        shader[SHADER_LOGIC_TYPE::SHADER_LOGIC_TYPE_ANIM_MODEL_WITH_SHADOW] = new Shader(
                SHADER_DIR"SkeletalModelWithShadow.vert.glsl", SHADER_DIR"SkeletalModelWithShadow.frag.glsl");
    }
    if (shader[SHADER_LOGIC_TYPE::SHADER_LOGIC_TYPE_DEPTH_ANIM] == nullptr) {
        shader[SHADER_LOGIC_TYPE::SHADER_LOGIC_TYPE_DEPTH_ANIM] = new Shader(
                SHADER_DIR"ShadowMappingDepthSkeletal.vert.glsl", SHADER_DIR"ShadowMappingDepthSkeletal.frag.glsl");
    }
    if (shader[SHADER_LOGIC_TYPE::SHADER_LOGIC_TYPE_DEBUG] == nullptr) {
        shader[SHADER_LOGIC_TYPE::SHADER_LOGIC_TYPE_DEBUG] = new Shader(SHADER_DIR"DebugShadowMapping.vert.glsl",
                                                                        SHADER_DIR"DebugShadowMapping.frag.glsl");
    }
    if (shader[SHADER_LOGIC_TYPE::SHADER_LOGIC_TYPE_LIGHT] == nullptr) {
        shader[SHADER_LOGIC_TYPE::SHADER_LOGIC_TYPE_LIGHT] = new Shader(SHADER_DIR"SkeletalModelWithShadow.vert.glsl",
                                                                        SHADER_DIR"Light.frag.glsl");
    }
    if (shader[SHADER_LOGIC_TYPE::SHADER_LOGIC_TYPE_BLUR] == nullptr) {
        shader[SHADER_LOGIC_TYPE::SHADER_LOGIC_TYPE_BLUR] = new Shader(SHADER_DIR"blur.vert.glsl",
                                                                       SHADER_DIR"blur.frag.glsl");
    }
    if (shader[SHADER_LOGIC_TYPE::SHADER_LOGIC_TYPE_BLOOM_FINAL] == nullptr) {
        shader[SHADER_LOGIC_TYPE::SHADER_LOGIC_TYPE_BLOOM_FINAL] = new Shader(SHADER_DIR"bloomFinal.vert.glsl",
                                                                              SHADER_DIR"bloomFinal.frag.glsl");
    }

    glGenFramebuffers(1, &hdrFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);

    glGenTextures(2, colorBuffers);
    for (unsigned int i = 0; i < 2; i++) {
        glBindTexture(GL_TEXTURE_2D, colorBuffers[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, worldData->w, worldData->h, 0, GL_RGBA, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                        GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, colorBuffers[i], 0);
    }

    glGenRenderbuffers(1, &rboDepth);
    glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, worldData->w, worldData->h);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);

    glDrawBuffers(2, attachments);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "Framebuffer not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glGenFramebuffers(2, pingpongFBO);
    glGenTextures(2, pingpongColorbuffers);
    for (unsigned int i = 0; i < 2; i++) {

        glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[i]);
        glBindTexture(GL_TEXTURE_2D, pingpongColorbuffers[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, worldData->w, worldData->h, 0, GL_RGBA, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pingpongColorbuffers[i], 0);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::cout << "Framebuffer not complete!" << std::endl;
    }

    shader[SHADER_LOGIC_TYPE::SHADER_LOGIC_TYPE_BLUR]->use();
    shader[SHADER_LOGIC_TYPE::SHADER_LOGIC_TYPE_BLUR]->setInt("image", 0);
    shader[SHADER_LOGIC_TYPE::SHADER_LOGIC_TYPE_BLOOM_FINAL]->use();
    shader[SHADER_LOGIC_TYPE::SHADER_LOGIC_TYPE_BLOOM_FINAL]->setInt("scene", 0);
    shader[SHADER_LOGIC_TYPE::SHADER_LOGIC_TYPE_BLOOM_FINAL]->setInt("bloomBlur", 1);


    {
        glGenFramebuffers(1, &Render::depthMapFBO);

        glGenTextures(1, &Render::depthMap);
        glBindTexture(GL_TEXTURE_2D, Render::depthMap);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, worldData->SHADOW_WIDTH, worldData->SHADOW_HEIGHT, 0,
                     GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        float borderColor[] = {1.0, 1.0, 1.0, 1.0};
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
        glBindFramebuffer(GL_FRAMEBUFFER, Render::depthMapFBO);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, Render::depthMap, 0);
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

    }
    {
        auto x = new Model();
        //int anim = x->load(RES_DIR"untitled.gltf");
        int anim = x->load(RES_DIR"plane.dae");
        if (anim)
            animModels.emplace_back(x);
        else
            staticModels.emplace_back(x);
    }

    {
        auto x = new Model();
        int anim = x->load(RES_DIR"bee.dae");
        if (anim)
            animModels.emplace_back(x);
        else
            staticModels.emplace_back(x);
    }



#ifdef USE_GUI

    g = new gui();
    g->init((GLFWwindow*)worldData->d->_window->_glfwPtr);
#endif

    return 0;
}


int Render::draw() {
    float &currentFrame = worldData->currentFrame;

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, worldData->w, worldData->h);

    glm::mat4 lightProjection, lightView;
    glm::mat4 &lightSpaceMatrix = worldData->lightSpaceMatrix;

    lightProjection = glm::ortho(worldData->orthoLeft, worldData->orthoRight, worldData->orthoBottom,
                                 worldData->orthoTop, worldData->near_plane, worldData->far_plane);
    lightView = glm::lookAt(glm::vec3(worldData->light1Pos.x, worldData->light1Pos.y, worldData->light1Pos.z),
                            worldData->lookCenterPos, worldData->lookUpPos);
    lightSpaceMatrix = lightProjection * lightView;

    if (worldData->shadowOn) {
        getDepthMap();
    }
    {
        glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glViewport(0, 0, worldData->w, worldData->h);


        Shader *curShader = shader[SHADER_LOGIC_TYPE::SHADER_LOGIC_TYPE_ANIM_MODEL_WITH_SHADOW];
        curShader->use();
        glm::mat4 projection = worldData->proj;
        glm::mat4 view = worldData->camera.getViewMatrix();
        glm::mat4 model = glm::mat4(1.0f);
        glm::vec3 lightPos = glm::vec3(3 * cos(currentFrame), 3, 3 * sin(currentFrame));


        {
            curShader->setVec3("viewPos", worldData->camera.Position);
            curShader->setVec3("lightPos", lightPos);
            curShader->setInt("shadowMap", 0);
            curShader->setInt("diffuseTexture", 1);
            if (worldData->shadowOn)
                curShader->setInt("shadowOn", 1);
            else
                curShader->setInt("shadowOn", 0);
        }


        auto &shadowOn = worldData->shadowOn;

        drawModelWithShadow();

        if (worldData->particleOn) {
            p->draw();
        }


    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    if (worldData->bloomOn) {
        bool horizontal = true, first_iteration = true;
        unsigned int amount = 10;
        shader[SHADER_LOGIC_TYPE_BLUR]->use();
        shader[SHADER_LOGIC_TYPE_BLUR]->setInt("image", 0);
        for (unsigned int i = 0; i < amount; i++) {
            glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[horizontal]);
            shader[SHADER_LOGIC_TYPE_BLUR]->setInt("horizontal", horizontal);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, first_iteration ? colorBuffers[1]
                                                         : pingpongColorbuffers[!horizontal]);
            renderQuad();
            horizontal = !horizontal;
            if (first_iteration)
                first_iteration = false;
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader[SHADER_LOGIC_TYPE_BLOOM_FINAL]->use();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, colorBuffers[0]);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, pingpongColorbuffers[!horizontal]);
        shader[SHADER_LOGIC_TYPE_BLOOM_FINAL]->setInt("bloom", bloom);
        shader[SHADER_LOGIC_TYPE_BLOOM_FINAL]->setFloat("exposure", exposure);
        renderQuad();
    } else {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader[SHADER_LOGIC_TYPE_BLOOM_FINAL]->use();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, colorBuffers[0]);
        shader[SHADER_LOGIC_TYPE_BLOOM_FINAL]->setInt("bloom", worldData->bloomOn);
        shader[SHADER_LOGIC_TYPE_BLOOM_FINAL]->setFloat("exposure", exposure);
        renderQuad();
    }


#ifdef USE_GUI
    g->render();
#endif
    //showDepthMap();

    return 0;
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

int Render::shaderSetParam(Shader *curShader, DRAW_TYPE type) {
    float &currentFrame = worldData->currentFrame;
    glm::vec3 lightPos = glm::vec3(3 * cos(currentFrame), 3, 3 * sin(currentFrame));
    if (type == DRAW_TYPE::DRAW_TYPE_ANIM_MODEL_WITH_SHADOW || type == DRAW_TYPE::DRAW_TYPE_ANIM_MODEL) {
        curShader->setVec3("viewPos", worldData->camera.Position);
        curShader->setVec3("lightPos", lightPos);
        curShader->setInt("shadowMap", 0);
        curShader->setInt("diffuseTexture", 1);
        if (type == DRAW_TYPE::DRAW_TYPE_ANIM_MODEL_WITH_SHADOW)
            curShader->setInt("shadowOn", 1);
        else
            curShader->setInt("shadowOn", 0);
    } else if (type == DRAW_TYPE::DRAW_TYPE_DEPTH) {

    }
    return 0;
}


int Render::drawModels(DRAW_TYPE type) {
    float &currentFrame = worldData->currentFrame;
    Shader *curShader = nullptr;

    if (type == DRAW_TYPE::DRAW_TYPE_ANIM_MODEL_WITH_SHADOW || type == DRAW_TYPE::DRAW_TYPE_ANIM_MODEL ||
        type == DRAW_TYPE::DRAW_TYPE_ANIM_MODEL_WITH_BLOOM) {
        curShader = Render::shader[SHADER_LOGIC_TYPE::SHADER_LOGIC_TYPE_ANIM_MODEL_WITH_SHADOW];
    } else if (type == DRAW_TYPE::DRAW_TYPE_DEPTH) {
        curShader = Render::shader[SHADER_LOGIC_TYPE::SHADER_LOGIC_TYPE_DEPTH_ANIM];
    }

    if (curShader == nullptr)
        return -1;
    curShader->use();
    glm::mat4 projection = worldData->proj;
    glm::mat4 view = worldData->camera.getViewMatrix();
    glm::mat4 model = glm::mat4(1.0f);
    glm::vec3 lightPos;
    shaderSetParam(curShader, type);


    model = glm::mat4(1.0f);
    model = scale(model, glm::vec3(10.0f));
    model = translate(model, glm::vec3(0, 0.0, 0));
    model = rotate(model, glm::radians(-90.0f), glm::vec3(1, 0, 0));

    staticModels[0]->draw(type, 1, curShader, model, view, projection, currentFrame);

    model = glm::mat4(1.0f);
    model = scale(model, glm::vec3(0.3f));
    model = translate(model, glm::vec3(0, -1 * 0.6666, 0));
    model = rotate(model, glm::radians(-90.0f), glm::vec3(1, 0, 0));
    animModels[0]->draw(type, 1, curShader, model, view, projection, currentFrame);
    auto srcModel = model;

    int halfDist = 10;

    for (int x = -halfDist; x < halfDist; x++) {
        for (int y = -halfDist; y < halfDist; y++) {
            model = translate(srcModel, glm::vec3(x * 8, y * 8, 0));
            animModels[0]->draw(type, 1, curShader, model, view, projection, currentFrame);
        }
    }


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

void Render::drawModelWithShadow() {

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, worldData->w, worldData->h);

    if (worldData->shadowOn == 1) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, Render::depthMap);
    }

    if (worldData->shadowOn) {
        drawModels(DRAW_TYPE::DRAW_TYPE_ANIM_MODEL_WITH_SHADOW);
    } else {
        drawModels(DRAW_TYPE::DRAW_TYPE_ANIM_MODEL);
    }

    if (worldData->shadowOn == 1) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}