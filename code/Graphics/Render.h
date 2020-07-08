//
// Created by caspasex on 2019/10/17.
//

#pragma once
#ifndef INC_3D_RENDER_H
#define INC_3D_RENDER_H

#include "Model.h"
#include "Particle.h"

#include "gui.h"
#define USE_GUI
static bool GUIMode = false;

class Render {
public:
    enum SHADER_LOGIC_TYPE
    {
        SHADER_LOGIC_TYPE_ANIM_MODEL_WITH_SHADOW = 0,
        SHADER_LOGIC_TYPE_DEPTH_ANIM  = 1,
        SHADER_LOGIC_TYPE_DEBUG = 2,
        SHADER_LOGIC_TYPE_LIGHT = 3,
        SHADER_LOGIC_TYPE_BLUR = 4,
        SHADER_LOGIC_TYPE_BLOOM_FINAL = 5,
        END
    };
    enum DRAW_TYPE
    {
        DRAW_TYPE_ANIM_MODEL,
        DRAW_TYPE_DEPTH,
        DRAW_TYPE_ANIM_MODEL_WITH_SHADOW,
        DRAW_TYPE_ANIM_MODEL_WITH_BLOOM,
    };
public:
    int init();

    int draw();

    int drawModels(DRAW_TYPE type);
    int shaderSetParam(Shader* shader, DRAW_TYPE type);
    void showDepthMap();

    void getDepthMap();
    void drawModelWithShadow();

public:
    std::vector<Model *> staticModels;
    std::vector<Model *> animModels;

    static std::vector<Shader *> shader;
protected:

    static unsigned int depthMapFBO;
    static unsigned int depthMap;

    unsigned int hdrFBO = 0;
    unsigned int rboDepth = 0;

    unsigned int pingpongFBO[2];
    unsigned int pingpongColorbuffers[2];

    unsigned int attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
    unsigned int colorBuffers[2];
    Particle * p = nullptr;

    gui *g = nullptr;
};


#endif //INC_3D_RENDER_H
