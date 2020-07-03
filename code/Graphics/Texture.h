//
// Created by caspasex on 2019/10/17.
//


#pragma once
#ifndef INC_3D_TEXTURE_H
#define INC_3D_TEXTURE_H

#include "Config.h"
#include <glad/glad.h>
#include <string>
#include <iostream>

enum TextureEnum {
    DIFFUSE,
    SPECULAR,
    NORMAL,
    IMAGE
};

class Texture {
public:

    Texture(GLenum TextureTarget, const std::string &FileName, TextureEnum TextureType);

    ~Texture();

    void load();

    void bind(GLenum TextureUnit);

    std::string getFilename() { return m_fileName; }

    TextureEnum getTextureType() { return m_textureType; }

public:

    std::string m_fileName;
    GLenum m_textureTarget;
    GLuint m_textureID;
    TextureEnum m_textureType;

};

#endif