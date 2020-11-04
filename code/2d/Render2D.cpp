//
// Created by caspase on 10/20/2020.
//

#include "Render2D.h"
#include "Shader.h"
#include "TextureEx1.h"
#include "Texture2DEx.h"
#include "Device.h"
#include "RenderBase.h"

quad* quad::get(){
    static quad self = quad();
    return &self;
}

void quad::init() {
    float quadVertices[] = {
            // positions        // texture Coords
            -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
            1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
            1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
    };
    // setup plane VAO
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
}

void quad::renderQuad() {
    if (quadVAO == 0) {
        float quadVertices[] = {
                // positions        // texture Coords
                -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
                -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
                1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
                1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        };
// setup plane VAO
        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
    }
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
};

int Render2D::render2DInit() {
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &wfbo);
    glGetIntegerv(GL_RENDERBUFFER_BINDING, &wrbo);

    shader.resize(SHADER_TYPE::END, nullptr);
    auto &shader2D = shader[SHADER_TYPE::LOGIC_2D];
    std::vector<char> shaderVertFile;
    std::vector<char> shaderFragFile;
    shaderVertFile.insert(shaderVertFile.end(), shader_vert_glsl, shader_vert_glsl + strlen(shader_vert_glsl));
    shaderFragFile.insert(shaderFragFile.end(), shader_frag_glsl, shader_frag_glsl + strlen(shader_frag_glsl));

//    auto&& shaderVertFile = res.Res("Shader/shader.vert.glsl");
//    auto&& shaderFragFile = res.Res("Shader/shader.frag.glsl");
    if (shader[SHADER_TYPE::LOGIC_2D] == nullptr) {
        shader[SHADER_TYPE::LOGIC_2D] = new Shader(shaderVertFile, shaderFragFile);
    }

    std::vector<char>DebugShadowMappingVertFile;
    std::vector<char>DebugShadowMappingFragFile;
    DebugShadowMappingVertFile.insert(DebugShadowMappingVertFile.end(), DebugShadowMapping_vert_glsl, DebugShadowMapping_vert_glsl + strlen(DebugShadowMapping_vert_glsl));
    DebugShadowMappingFragFile.insert(DebugShadowMappingFragFile.end(), DebugShadowMapping_frag_glsl, DebugShadowMapping_frag_glsl + strlen(DebugShadowMapping_frag_glsl));

//    auto&& DebugShadowMappingVertFile = res.Res("Shader/DebugShadowMapping.vert.glsl");
//    auto&& DebugShadowMappingFragFile = res.Res("Shader/DebugShadowMapping.frag.glsl");
    if (shader[SHADER_TYPE::SHADER_LOGIC_TYPE_DEBUG] == nullptr) {
        shader[SHADER_TYPE::SHADER_LOGIC_TYPE_DEBUG] = new Shader(DebugShadowMappingVertFile,
                                                                        DebugShadowMappingFragFile);
    }


    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
            // positions          // colors           // texture coords
            0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
            -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
    };
    unsigned int indices[] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    // load and create a texture
    // -------------------------
     resType = {
            new Texture2DEx{nullptr, 0,  "2d/bb.png",    glm::vec3(3, 6, 0),     5, 1, 5},
            new Texture2DEx{nullptr, 1,  "2d/boom.png",  glm::vec3(-29, -58, 0), 4, 4, 16},
            new Texture2DEx{nullptr, 2,  "2d/ter1.png",  glm::vec3(0, 0, 0),     1, 1, 1},
            new Texture2DEx{nullptr, 3,  "2d/ter2.png",  glm::vec3(-10, -1, 0),  1, 1, 1},
            new Texture2DEx{nullptr, 4,  "2d/ter3.png",  glm::vec3(-19, -10, 0), 1, 1, 1},
            new Texture2DEx{nullptr, 5,  "2d/ter4.png",  glm::vec3(0, 15, 0),    1, 1, 1},
            new Texture2DEx{nullptr, 6,  "2d/ter5.png",  glm::vec3(0, 0, 0),     1, 1, 1},
            new Texture2DEx{nullptr, 7,  "2d/ter6.png",  glm::vec3(-23, -25, 0), 1, 1, 1},
            new Texture2DEx{nullptr, 8,  "2d/ter7.png",  glm::vec3(-23, -49, 0), 1, 1, 1},
            new Texture2DEx{nullptr, 9,  "2d/ter8.png",  glm::vec3(-35, -40, 0), 1, 1, 1},
            new Texture2DEx{nullptr, 10, "2d/ter9.png",  glm::vec3(-26, -26, 0), 1, 1, 1},
            new Texture2DEx{nullptr, 11, "2d/ter10.png", glm::vec3(-24, -40, 0), 1, 1, 1},
    };
    for (auto &E: resType) {
        E->load();
    }



    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    shader2D->use(); // don't forget to activate/use the shader before setting uniforms!
    // either set it manually like so:
    //glUniform1i(glGetUniformLocation(shader2D->ID, "texture1"), 0);
    // or set it via the texture class
    //ourShader.setInt("texture2", 1);


    this->init2d2();

    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    return 0;

}

int Render2D::init2d2()
{

    int w = Device::get()->_window->_w;
    int h = Device::get()->_window->_h;

    bool fbo0 = false;
    if(fbo0)
    {
    glGenFramebuffers(1, FBO2D);
    glGenTextures(1, Buffer2D);


    for (GLuint i = 0; i < 1; i++)
    {
        std::cout << FBO2D << std::endl;

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

void Render2D::drawTexture(float x, float y, TextureEx1 *texture, glm::vec2 *texcoords, ::Color &color, float curframe,
                           int animW, int animH) {
    auto &shader2D = shader[SHADER_TYPE::LOGIC_2D];
    shader2D->use();
    int w = texture->w;
    int h = texture->h;

    vPositions.resize(4);
    vIndices.resize(6);
    ////this->resizeVector(4, 6);
    ///
    ///


    vPositions[0] = glm::vec3(x + 0, y + 0, 0);
    vPositions[1] = glm::vec3(x + 0, y + h / animH, 0);
    vPositions[2] = glm::vec3(x + w / animW, y + h / animH, 0);
    vPositions[3] = glm::vec3(x + w / animW, y + 0, 0);


    glm::mat4 mat(1.0f);
    glm::mat4 ortho = glm::ortho(0.0f, (float) Device::_window->_w, (float) Device::_window->_h, 0.0f, -1.0f, 1.0f);

    glm::mat4 mTransformMatrix = ortho;

    vPositions[0] = mTransformMatrix * glm::vec4(vPositions[0], 1.0f);
    vPositions[1] = mTransformMatrix * glm::vec4(vPositions[1], 1.0f);
    vPositions[2] = mTransformMatrix * glm::vec4(vPositions[2], 1.0f);
    vPositions[3] = mTransformMatrix * glm::vec4(vPositions[3], 1.0f);

    vIndices[0] = 0;
    vIndices[1] = 2;
    vIndices[2] = 1;
    vIndices[3] = 0;
    vIndices[4] = 3;
    vIndices[5] = 2;


    vColors.resize(4, color);


    static RenderUnit unit;
    unit.pPositions = &vPositions[0];
    unit.nPositionCount = 4;
    unit.pTexcoords = texcoords;
    unit.pIndices = vIndices.data();
    unit.nIndexCount = 6;
    unit.color = color;
    unit.texture = texture;
    //unit.renderType = RENDER_TYPE_TEXTURE;

    //pRenderer->pushRenderUnit(unit);
    int nPositionCount = 4;
    int xxxx = sizeof(glm::vec3);
    glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * nPositionCount, &vPositions[0], GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(::Color) * nPositionCount, &vColors[0], GL_DYNAMIC_DRAW);


    glBindBuffer(GL_ARRAY_BUFFER, texcoordBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * nPositionCount, &texcoords[0], GL_DYNAMIC_DRAW);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture->m_textureID);
    shader2D->setInt("defaultTexture", 0);
    //glUniform1i(glGetUniformLocation(shaderProgram, "defaulteTexture"), 0);
    //shader[SHADER_LOGIC_TYPE_2D2]->setInt("offset", 2);



    shader2D->setInt("offset", int(curframe * 10) % animW + animW * 0);
    shader2D->setInt("wcount", animW);
    shader2D->setInt("hcount", animH);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    int nIndexCount = 6;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * nIndexCount, &vIndices[0], GL_DYNAMIC_DRAW);


    glBindVertexArray(VAO2);


    glDrawElements(GL_TRIANGLES, nIndexCount, GL_UNSIGNED_INT, 0);


    return;
}

int Render2D::render2dDraw() {

    auto &shader2D = shader[SHADER_TYPE::LOGIC_2D];
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    ::Color c(1.0, 1.0, 1.0, 1.0);
//    {
//        shader2D->use();
//        {
//            glBindFramebuffer(GL_FRAMEBUFFER, FBO2D[0]);
//            glBindTexture(GL_TEXTURE_2D, Buffer2D[0]);
//        }
//        glClear(GL_COLOR_BUFFER_BIT);
//    }


for(int k = 0 ; k < 3; k++)
for(int j = 0; j < 3; j++)
{
    int abc = 0;
    for(int i = 0; i < 3; i++)
    {
        int spiritModelId = 0;
        Texture2DEx &t = *resType[spiritModelId];
        int posX = j*50+i*cos(RenderBase::get()->currentFrame)*50+500;
        int posY = k*50+i*sin(RenderBase::get()->currentFrame)*50+500;
        drawTexture((double) posX + t.ModelOffset.x, (double) (posY) + t.ModelOffset.y,
                    t.texture, t.texcoords, c, RenderBase::get()->currentFrame, t.animW, t.animH);

    }
}
    for(int k =0 ; k < 3; k++)
        for(int j = 0; j < 3; j++)
        {
            int abc = 0;
            for(int i = 0; i < 3; i++)
            {
                int spiritModelId = 1;
                Texture2DEx &t = *resType[spiritModelId];
                int posX = j*50+i*cos(RenderBase::get()->currentFrame)*50+200;
                int posY = k*50+i*sin(RenderBase::get()->currentFrame)*50+200;
                drawTexture((double) posX + t.ModelOffset.x, (double) (posY) + t.ModelOffset.y,
                            t.texture, t.texcoords, c, RenderBase::get()->currentFrame, t.animW, t.animH);

            }
        }
#ifdef USE_GUI
//    g->render();
#endif

    {
        glBindVertexArray(0);

//        glBindFramebuffer(GL_FRAMEBUFFER, wfbo);
//
//        auto &shaderQuad = shader[SHADER_TYPE::SHADER_LOGIC_TYPE_DEBUG];
//        shaderQuad->use();
//        shaderQuad->setInt("depthMap", 0);
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, Buffer2D[0]);
//        //if(int(curframe)%2 == 0)
//        quad::get()->renderQuad();
    }

    return 0;
}
