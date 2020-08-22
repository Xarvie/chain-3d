//
// Created by caspasex on 2019/10/17.
//

#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION

#include <stb_image.h>

Texture::Texture(GLenum TextureTarget, const std::string &FileName, TextureEnum TextureType) {
    m_textureTarget = TextureTarget;
    m_fileName = FileName;
    m_textureType = TextureType;
    load();
}

Texture::~Texture() {
}

void Texture::load() {
    glGenTextures(1, &m_textureID);
    glBindTexture(m_textureTarget, m_textureID);
    int width, height, nrComponents;
    unsigned char *data = stbi_load(m_fileName.c_str(), &width, &height, &nrComponents, 0);
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

        this->texcoords[0] = glm::vec2(0, 0);
        this->texcoords[1] = glm::vec2(0, 1);
        this->texcoords[2] = glm::vec2(1, 1);
        this->texcoords[3] = glm::vec2(1, 0);


        stbi_image_free(data);

    } else {
        std::cout << "err: load texture: " << m_fileName << std::endl;
    }
}

void Texture::bind(GLenum TextureUnit) {
    glActiveTexture(TextureUnit);
    glBindTexture(m_textureTarget, m_textureID);
}
