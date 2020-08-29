//
// Created by caspasex on 2019/10/17.
//

#pragma once
#ifndef INC_3D_RENDER_H
#define INC_3D_RENDER_H

#include "Model.h"
#include "Particle.h"

#include "gui.h"
#include "Terrain.h"

#define USE_GUI
extern bool GUIMode;

class Color
{
public:
    GLfloat r, g, b, a;

public:
    Color() : r(0), g(0), b(0), a(0) {}
    Color(GLfloat nr, GLfloat ng, GLfloat nb, GLfloat na) : r(nr), g(ng), b(nb), a(na) {}

    void set(GLfloat nr, GLfloat ng, GLfloat nb, GLfloat na)
    {
        r = nr; g = ng; b = nb; a = na;
    }
};

void renderQuad();

struct RenderUnit
{
    glm::vec3* pPositions;
    glm::vec2* pTexcoords;
    int nPositionCount;

    Color color;

    GLuint* pIndices;
    int nIndexCount;
    Texture* texture;

};

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
        SHADER_LOGIC_TYPE_2D = 6,
        SHADER_LOGIC_TYPE_2D2 = 7,
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

    int render2DInit();
    int render2dDraw();
    std::vector<glm::vec3> vPositions;
    std::vector<glm::vec2> vTexcoords;
    std::vector<Color> vColors;
    std::vector<GLuint>vIndices;


    GLuint positionBuffer;
    GLuint texcoordBuffer;
    GLuint colorBuffer;
    GLuint indexBuffer;
    GLuint VAO2;
    GLuint texrure;

    GLuint FBO2D[2];
    GLuint Buffer2D[2];
    int init2d2(int w, int h)
    {


        glGenFramebuffers(1, FBO2D);
        glGenTextures(1, Buffer2D);
        for (GLuint i = 0; i < 1; i++)
        {
            glBindFramebuffer(GL_FRAMEBUFFER, FBO2D[i]);
            glBindTexture(GL_TEXTURE_2D, Buffer2D[i]);
            glTexImage2D(
                GL_TEXTURE_2D, 0, GL_RGB16F, w, h, 0, GL_RGB, GL_FLOAT, NULL
            );
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glFramebufferTexture2D(
                GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, Buffer2D[i], 0
            );
        }



        glGenBuffers(1, &positionBuffer);
        glGenBuffers(1, &texcoordBuffer);
        glGenBuffers(1, &colorBuffer);
        glGenBuffers(1, &indexBuffer);
        glGenVertexArrays(1, &VAO2);

        glBindVertexArray(VAO2);

        glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), ( GLvoid* ) 0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, texcoordBuffer);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), ( GLvoid* ) 0);
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
        glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(::Color), ( GLvoid* ) 0);
        glEnableVertexAttribArray(2);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        return 0;
    }

    void drawTexture(float x, float y, Texture* texture, glm::vec2* texcoords, Color& color, float curframe, int animW, int animH);


public:
    std::vector<Model *> staticModels;
    std::vector<Model *> animModels;

    static std::vector<Shader *> shader;


    static unsigned int depthMapFBO;
    static unsigned int depthMap;
protected:
    unsigned int hdrFBO = 0;
    unsigned int rboDepth = 0;

    unsigned int pingpongFBO[2];
    unsigned int pingpongColorbuffers[2];

    unsigned int attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
    unsigned int colorBuffers[2];
    Particle * p = nullptr;
    World * t = nullptr;
    gui *g = nullptr;

    std::vector<unsigned int >textures;
    unsigned int VBO, VAO, EBO;



};


#endif //INC_3D_RENDER_H
