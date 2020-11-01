//
// Created by caspasex on 2019/10/17.
//

#ifndef INC_3D_TEXTURE2DEX_H
#define INC_3D_TEXTURE2DEX_H

#include "Config.h"
#include "OpenglHeader.h"
#include <string>
#include <iostream>
#include <glm/glm.hpp>

class TextureEx1;
class Texture2DEx{
public:
    TextureEx1 * texture;
    int modelTypeId;
    const char* modelName;
    glm::vec3 ModelOffset;

    int animW;
    int animH;
    int animAll;
    glm::vec2 texcoords[4];

    int load();

};
#endif