//
// Created by caspasex on 2019/10/17.
//

#pragma once
#ifndef INC_3D_RENDER_H
#define INC_3D_RENDER_H

#include "Model.h"

class Render {
public:
    enum SHADER_LOGIC_TYPE
    {
        SHADER_LOGIC_TYPE_ANIM_MODEL_WITH_SHADOW = 0,
        SHADER_LOGIC_TYPE_DEPTH_ANIM  = 1,
        SHADER_LOGIC_TYPE_DEBUG = 2,
        END
    };
    enum DRAW_TYPE
    {
        DRAW_TYPE_ANIM_MODEL,
        DRAW_TYPE_DEPTH,
        DRAW_TYPE_ANIM_MODEL_WITH_SHADOW,
    };
public:
    int init();

    int draw();

    int drawModels(DRAW_TYPE type);

    void showDepthMap();

    void getDepthMap();
    void drawModelWithShadow(bool shadowOn);

public:
    std::vector<Model *> staticModels;
    std::vector<Model *> animModels;

    static std::vector<Shader *> shader;
protected:

    static unsigned int depthMapFBO;
    static unsigned int depthMap;
};


#endif //INC_3D_RENDER_H
