//
// Created by caspasex on 2019/10/17.
//

#include "TextureEx1.h"

#define STB_IMAGE_IMPLEMENTATION1
#include "stb_image.h"
#include "ResourceMgr.h"

TextureEx1::TextureEx1(GLenum TextureTarget, const std::string &FileName, TextureEnum TextureType) {
    m_textureTarget = TextureTarget;
    m_fileName = FileName;
    m_textureType = TextureType;
    load();
}

TextureEx1::~TextureEx1() {
}

void TextureEx1::load() {
    glGenTextures(1, &m_textureID);
    glBindTexture(m_textureTarget, m_textureID);
    int width, height, nrComponents;
    stbi_set_flip_vertically_on_load(false);
    auto resData = res.Res(m_fileName);
    unsigned char *data = stbi_load_from_memory((stbi_uc*)resData.data(), resData.size(), &width, &height, &nrComponents, 0);
    if (data) {
        GLenum internalFormat;
        GLenum dataFormat = GL_RED;
        if (nrComponents == 1) {
            internalFormat = dataFormat = GL_RED;
        } else if (nrComponents == 3) {
            dataFormat = GL_RGB;
        } else if (nrComponents == 4) {
            dataFormat = GL_RGBA;
        }
        //dataFormat = GL_RGBA;
        glTexImage2D(m_textureTarget, 0, dataFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, dataFormat == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, dataFormat == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        //glGenerateMipmap(GL_TEXTURE_2D);

        this->x = 0;
        this->y = 0;
        this->w = width;
        this->h = height;




        stbi_image_free(data);

    } else {
        std::cout << "err: load texture: " << m_fileName << std::endl;
    }
}

void TextureEx1::bind(GLenum TextureUnit) {
    glActiveTexture(TextureUnit);
    glBindTexture(m_textureTarget, m_textureID);
}
