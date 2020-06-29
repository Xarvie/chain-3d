//
// Created by caspasex on 2019/10/17.
//

#pragma once
#ifndef INC_3D_RENDER_H
#define INC_3D_RENDER_H

#include "Model.h"

class Render {
public:
    int init();

    int draw();

public:
    std::vector<Model *> characters;
};


#endif //INC_3D_RENDER_H
