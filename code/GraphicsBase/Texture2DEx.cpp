//
// Created by caspasex on 2019/10/17.
//

#include "Texture2DEx.h"
#include "TextureEx1.h"

int Texture2DEx::load()    {
    texture = new TextureEx1(GL_TEXTURE_2D, modelName, TextureEnum::IMAGE);
    this->texcoords[0] = glm::vec2(0, 0);
    this->texcoords[1] = glm::vec2(0, 1);
    this->texcoords[2] = glm::vec2(1, 1);
    this->texcoords[3] = glm::vec2(1, 0);
    return 0;
}