//
// Created by caspase on 10/20/2020.
//

#ifndef EM_RENDER2D_H
#define EM_RENDER2D_H

#include <vector>
#include "glm/glm.hpp"
#include "OpenglHeader.h"
#if defined(USE_GUI)

#include "gui.h"
#endif
class Shader;
class TextureEx1;
class Texture2DEx;
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

struct RenderUnit
{
    glm::vec3* pPositions;
    glm::vec2* pTexcoords;
    int nPositionCount;

    ::Color color;

    GLuint* pIndices;
    int nIndexCount;
    TextureEx1* texture;

};



class quad
{
public:
    static quad* get();
    void init();
    void renderQuad();
    unsigned int quadVAO = 0;
    unsigned int quadVBO = 0;
};

class Render2D {
public:
    enum SHADER_TYPE{
        LOGIC_2D,
        SHADER_LOGIC_TYPE_DEBUG,

        END
    };
    int render2DInit();
    int init2d2();
    void drawTexture(float x, float y, TextureEx1* texture, glm::vec2* texcoords, ::Color& color, float curframe, int animW, int animH);
    int render2dDraw();

    std::vector<Shader*> shader;

    unsigned int VBO, VAO, EBO;

    std::vector<glm::vec3> vPositions;
    std::vector<glm::vec2> vTexcoords;
    std::vector<::Color> vColors;
    std::vector<GLuint>vIndices;

    GLuint positionBuffer;
    GLuint texcoordBuffer;
    GLuint colorBuffer;
    GLuint indexBuffer;
    GLuint VAO2;
    GLuint texrure;

    GLuint FBO2D[2];
    GLuint Buffer2D[2];


    GLint wfbo = 0;
    GLint wrbo = 0;

};

static std::vector<Texture2DEx*> resType;
#endif //EM_RENDER2D_H
