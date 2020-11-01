//
// Created by caspasex on 2019/10/17.
//


#ifndef INC_3D_TEXTUREEX1_H
#define INC_3D_TEXTUREEX1_H

#include "Config.h"
#include "OpenglHeader.h"
#include <string>
#include <iostream>
#include <glm/glm.hpp>

enum TextureEnum {
    DIFFUSE,
    SPECULAR,
    NORMAL,
    IMAGE
};

class TextureEx1 {
public:

    TextureEx1(GLenum TextureTarget, const std::string &FileName, TextureEnum TextureType);

    ~TextureEx1();

    void load();

    void bind(GLenum TextureUnit);

    std::string getFilename() { return m_fileName; }

    TextureEnum getTextureType() { return m_textureType; }

public:

    std::string m_fileName;
    GLenum m_textureTarget;
    GLuint m_textureID;
    TextureEnum m_textureType;

    GLfloat x, y, w, h;

};
#endif
