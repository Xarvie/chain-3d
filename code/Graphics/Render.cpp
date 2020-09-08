//
// Created by caspasex on 2020/6/29.
//

#include "Render.h"

#include <Graphics/Camera.h>
#include <Graphics/Shader.h>
#include <Queue.h>

#include "Config.h"
#include "Model.h"
#include "Data.h"
#include "Terrain.h"
#include "map.h"
bool GUIMode = false;
std::vector<Shader *> Render::shader = std::vector<Shader *>(SHADER_LOGIC_TYPE::END, nullptr);
unsigned int Render::depthMapFBO = 0;
unsigned int Render::depthMap = 0;


bool bloom = true;
bool bloomKeyPressed = false;
float exposure = 1.0f;


unsigned int quadVAO = 0;
unsigned int quadVBO = 0;

moodycamel::ConcurrentQueue<Render::Task> taskQueue;

int Render::render2DInit()
{
    auto & ourShader = *shader[SHADER_LOGIC_TYPE::SHADER_LOGIC_TYPE_2D];

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
            // positions          // colors           // texture coords
            0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
            0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    // load and create a texture
    // -------------------------
    for (auto& E: resType)
    {
        E.load();
    }







    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    ourShader.use(); // don't forget to activate/use the shader before setting uniforms!
    // either set it manually like so:
    glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);
    // or set it via the texture class
    //ourShader.setInt("texture2", 1);
    return 0;
}

void Render::drawTexture(float x, float y, Texture* texture, glm::vec2* texcoords, ::Color& color, float curframe, int animW, int animH)
{

    int w = texture->w;
    int h = texture->h;

    vPositions.resize(4);
    vIndices.resize(6);
    ////this->resizeVector(4, 6);
    ///
    ///


    vPositions[0] = glm::vec3(x + 0, y + 0, 0);
    vPositions[1] = glm::vec3(x + 0, y + h/animH, 0);
    vPositions[2] = glm::vec3(x + w/animW, y + h/animH, 0);
    vPositions[3] = glm::vec3(x + w/animW, y + 0, 0);



    glm::mat4 mat(1.0f);
    glm::mat4 ortho = glm::ortho(0.0f, (float)worldData->w, (float)worldData->h, 0.0f, -1.0f, 1.0f);

    glm::mat4 mTransformMatrix = ortho ;

    vPositions[0] = mTransformMatrix * glm::vec4(vPositions[0],1.0f);
    vPositions[1] = mTransformMatrix * glm::vec4(vPositions[1],1.0f);
    vPositions[2] = mTransformMatrix * glm::vec4(vPositions[2],1.0f);
    vPositions[3] = mTransformMatrix * glm::vec4(vPositions[3],1.0f);

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
    int xxxx = sizeof( glm::vec3);
    glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof( glm::vec3 ) * nPositionCount, &vPositions[0], GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof( ::Color ) * nPositionCount, &vColors[0], GL_DYNAMIC_DRAW);


    glBindBuffer(GL_ARRAY_BUFFER, texcoordBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof( glm::vec2 ) * nPositionCount, &texcoords[0], GL_DYNAMIC_DRAW);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture->m_textureID);
    shader[SHADER_LOGIC_TYPE_2D2]->setInt("defaultTexture", 0);
    //glUniform1i(glGetUniformLocation(shaderProgram, "defaulteTexture"), 0);
    //shader[SHADER_LOGIC_TYPE_2D2]->setInt("offset", 2);



    shader[SHADER_LOGIC_TYPE_2D2]->setInt("offset", int(curframe*10) % animW + animW*0);
    shader[SHADER_LOGIC_TYPE_2D2]->setInt("wcount", animW);
    shader[SHADER_LOGIC_TYPE_2D2]->setInt("hcount", animH);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    int nIndexCount = 6;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof( GLuint ) * nIndexCount, &vIndices[0], GL_DYNAMIC_DRAW);


    glBindVertexArray(VAO2);


    glDrawElements(GL_TRIANGLES, nIndexCount, GL_UNSIGNED_INT, 0);


    return ;
}

int Render::render2dDraw()
{
   // glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    //glClear(GL_COLOR_BUFFER_BIT);

//
//    std::map<float, UnitData*> sorted;
//    for (auto& E: map1Unit)
//    {
//        auto pos = glm::vec3(Real::ToFloat(E.pos.x), Real::ToFloat(E.pos.y), Real::ToFloat(E.pos.z));
//        float distance = glm::length(worldData->camera.Position - pos);
//        sorted[distance] = &E;
//    }
//
//
//    auto & ourShader = *shader[SHADER_LOGIC_TYPE::SHADER_LOGIC_TYPE_2D];
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
//
//
//
//    // render container
//    ourShader.use();
//
//    glm::mat4 projection = worldData->proj;
//    glm::mat4 view = worldData->camera.getViewMatrix();
//
//    for(std::map<float, UnitData*>::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); ++it)
//    {
//        auto & rest = resType[it->second->type];
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, textures[rest.modelTypeId]);
//        if(rest.animAll > 1){
//            glm::mat4 model = glm::mat4(1.0f);
//            model = translate(model, rest.ModelOffset + it->second->pos.glm());
//            model = glm::scale(model,glm::vec3(rest.pixelX*0.01f, rest.pixelX*0.01f, rest.pixelX*0.01f));
//            ourShader.setMat4("MVP", projection * view * model);
//            int w = rest.animW, h = rest.animH;
//            ourShader.setInt("offset", int(worldData->currentFrame*10) % w + w*3);
//            ourShader.setInt("wcount", w);
//            ourShader.setInt("hcount", h);
//            //ourShader.setInt("allcount", 30);
//
//            //glDisable(GL_DEPTH_TEST);
//            glBindVertexArray(VAO);
//            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//        }
//        else
//        {
//            glm::mat4 model = glm::mat4(1.0f);
//            model = translate(model, rest.ModelOffset + it->second->pos.glm());
//            model = glm::scale(model,glm::vec3(rest.pixelX*0.01f, rest.pixelX*0.01f, rest.pixelX*0.01f));
//            ourShader.setMat4("MVP", projection * view * model);
//            ourShader.setInt("offset", 0);
//            ourShader.setInt("wcount", 1);
//            ourShader.setInt("hcount", 1);
//            //ourShader.setInt("allcount", 30);
//
//            //glDisable(GL_DEPTH_TEST);
//            glBindVertexArray(VAO);
//            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//
//        }
//
//
//
//    }

    ::Color c(1.0,1.0,1.0,1.0);
    {
        shader[SHADER_LOGIC_TYPE_2D2]->use();
        {
            glBindFramebuffer(GL_FRAMEBUFFER, FBO2D[0]);
            glBindTexture(GL_TEXTURE_2D, Buffer2D[0]);
        }
        glClear(GL_COLOR_BUFFER_BIT);
    }
    if(!this->maps.empty())
    for(auto E:this->maps[this->curMapIndex].spiritSet){
        Texture2DEx &t = resType[E.modelObj.spiritModelId];
        drawTexture(Real::ToFloat(E.posObj.pos.x) + t.ModelOffset.x,Real::ToFloat(E.posObj.pos.y) + t.ModelOffset.y
                , t.texture, t.texcoords, c, worldData->currentFrame, t.animW, t.animH);

    }
    if(!this->maps.empty())
    for(auto E:this->maps[this->curMapIndex].unitSet){
        Texture2DEx &t = resType[E.modelObj.spiritModelId];
        drawTexture(Real::ToFloat(E.posObj.pos.x) + t.ModelOffset.x,Real::ToFloat(E.posObj.pos.y) + t.ModelOffset.y
                , t.texture, t.texcoords, c, worldData->currentFrame, t.animW, t.animH);

    }
//    for(auto E:map1tile)
//    {
//        Texture2DEx &t = resType[E.type];
//
//
//        drawTexture(Real::ToFloat(E.pos.x),Real::ToFloat(E.pos.y)
//                , t.texture, t.texcoords, c, worldData->currentFrame, t.animW, t.animH);
//
//
//    }

//    for(auto E:map1tile)
//    {
//        Texture2DEx &t = resType[E.type];
//
//
//        drawTexture(Real::ToFloat(E.pos.x) + t.ModelOffset.x,Real::ToFloat(E.pos.y) + t.ModelOffset.y
//                , t.texture, t.texcoords, c, worldData->currentFrame, t.animW, t.animH);
//
//
//    }

//    for(auto E:map1Unit)
//    {
//        Texture2DEx &t = resType[E.type];
//
//
//        drawTexture(Real::ToFloat(E.pos.x) + t.ModelOffset.x,Real::ToFloat(E.pos.y) + t.ModelOffset.y
//        , t.texture, t.texcoords, c, worldData->currentFrame, t.animW, t.animH);
//
//
//    }


    {
        glBindVertexArray(0);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);


        shader[SHADER_LOGIC_TYPE_DEBUG]->use();
        shader[SHADER_LOGIC_TYPE_DEBUG]->setInt("depthMap", 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, Buffer2D[0]);
        //if(int(curframe)%2 == 0)
        renderQuad();
    }
//    model = translate(model, glm::vec3(0.1, 0.0f, -1));
//    //model = glm::scale(model,glm::vec3(1.0, 2.0f, 1.0));
//    ourShader.setMat4("MVP", projection * view * model);
//    ourShader.setInt("offset", int(worldData->currentFrame*10) % maxCount + 4);
//    ourShader.setInt("wcount", 4);
//    ourShader.setInt("hcount", 4);
//    //ourShader.setInt("allcount", 30);
//
//    //glDisable(GL_DEPTH_TEST);
//    glBindVertexArray(VAO);
//    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//    //glEnable(GL_DEPTH_TEST);
    return 0;
}

void renderQuad() {
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
}

#include "BatchSpriteScene.h"
Render* Render::get()
{
    static Render r;
    return &r;
}

int Render::init() {

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    //glEnable(GL_CULL_FACE);

    glfwWindowHint(GLFW_SAMPLES, worldData->MSAA);
    glEnable(GL_BLEND);

    if (p == nullptr)
        p = new Particle;
    p->init();
    worldData->proj = glm::perspective(45.0f,
                                       float(worldData->w) / float(worldData->h),
                                       0.1f, 50.0f);

    //worldData->proj = glm::ortho(0.0f, 50.0f, 0.0f, 50.0f, -100.0f, 100.0f);

    if (shader[SHADER_LOGIC_TYPE::SHADER_LOGIC_TYPE_ANIM_MODEL_WITH_SHADOW] == nullptr) {
        shader[SHADER_LOGIC_TYPE::SHADER_LOGIC_TYPE_ANIM_MODEL_WITH_SHADOW] = new Shader(
                SHADER_DIR"SkeletalModelWithShadow.vert.glsl", SHADER_DIR"SkeletalModelWithShadow.frag.glsl");
    }
    if (shader[SHADER_LOGIC_TYPE::SHADER_LOGIC_TYPE_DEPTH_ANIM] == nullptr) {
        shader[SHADER_LOGIC_TYPE::SHADER_LOGIC_TYPE_DEPTH_ANIM] = new Shader(
                SHADER_DIR"ShadowMappingDepthSkeletal.vert.glsl", SHADER_DIR"ShadowMappingDepthSkeletal.frag.glsl");
    }
    if (shader[SHADER_LOGIC_TYPE::SHADER_LOGIC_TYPE_DEBUG] == nullptr) {
        shader[SHADER_LOGIC_TYPE::SHADER_LOGIC_TYPE_DEBUG] = new Shader(SHADER_DIR"DebugShadowMapping.vert.glsl",
                                                                        SHADER_DIR"DebugShadowMapping.frag.glsl");
    }
    if (shader[SHADER_LOGIC_TYPE::SHADER_LOGIC_TYPE_LIGHT] == nullptr) {
        shader[SHADER_LOGIC_TYPE::SHADER_LOGIC_TYPE_LIGHT] = new Shader(SHADER_DIR"SkeletalModelWithShadow.vert.glsl",
                                                                        SHADER_DIR"Light.frag.glsl");
    }
    if (shader[SHADER_LOGIC_TYPE::SHADER_LOGIC_TYPE_BLUR] == nullptr) {
        shader[SHADER_LOGIC_TYPE::SHADER_LOGIC_TYPE_BLUR] = new Shader(SHADER_DIR"blur.vert.glsl",
                                                                       SHADER_DIR"blur.frag.glsl");
    }
    if (shader[SHADER_LOGIC_TYPE::SHADER_LOGIC_TYPE_BLOOM_FINAL] == nullptr) {
        shader[SHADER_LOGIC_TYPE::SHADER_LOGIC_TYPE_BLOOM_FINAL] = new Shader(SHADER_DIR"bloomFinal.vert.glsl",SHADER_DIR"bloomFinal.frag.glsl");
    }
    if (shader[SHADER_LOGIC_TYPE::SHADER_LOGIC_TYPE_2D] == nullptr) {
        shader[SHADER_LOGIC_TYPE::SHADER_LOGIC_TYPE_2D] = new Shader(SHADER_DIR"2D.vert.glsl",SHADER_DIR"2D.frag.glsl");
    }
    if (shader[SHADER_LOGIC_TYPE::SHADER_LOGIC_TYPE_2D2] == nullptr) {
        shader[SHADER_LOGIC_TYPE::SHADER_LOGIC_TYPE_2D2] = new Shader(SHADER_DIR"shader.vert.glsl",SHADER_DIR"shader.frag.glsl");
    }
    glGenFramebuffers(1, &hdrFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);

    glGenTextures(2, colorBuffers);
    for (unsigned int i = 0; i < 2; i++) {
        glBindTexture(GL_TEXTURE_2D, colorBuffers[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, worldData->w, worldData->h, 0, GL_RGBA, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                        GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, colorBuffers[i], 0);
    }

    glGenRenderbuffers(1, &rboDepth);
    glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, worldData->w, worldData->h);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);

    glDrawBuffers(2, attachments);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "Framebuffer not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glGenFramebuffers(2, pingpongFBO);
    glGenTextures(2, pingpongColorbuffers);
    for (unsigned int i = 0; i < 2; i++) {

        glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[i]);
        glBindTexture(GL_TEXTURE_2D, pingpongColorbuffers[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, worldData->w, worldData->h, 0, GL_RGBA, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pingpongColorbuffers[i], 0);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::cout << "Framebuffer not complete!" << std::endl;
    }

    shader[SHADER_LOGIC_TYPE::SHADER_LOGIC_TYPE_BLUR]->use();
    shader[SHADER_LOGIC_TYPE::SHADER_LOGIC_TYPE_BLUR]->setInt("image", 0);
    shader[SHADER_LOGIC_TYPE::SHADER_LOGIC_TYPE_BLOOM_FINAL]->use();
    shader[SHADER_LOGIC_TYPE::SHADER_LOGIC_TYPE_BLOOM_FINAL]->setInt("scene", 0);
    shader[SHADER_LOGIC_TYPE::SHADER_LOGIC_TYPE_BLOOM_FINAL]->setInt("bloomBlur", 1);


    {
        glGenFramebuffers(1, &Render::depthMapFBO);

        glGenTextures(1, &Render::depthMap);
        glBindTexture(GL_TEXTURE_2D, Render::depthMap);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, worldData->SHADOW_WIDTH, worldData->SHADOW_HEIGHT, 0,
                     GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        float borderColor[] = {1.0, 1.0, 1.0, 1.0};
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
        glBindFramebuffer(GL_FRAMEBUFFER, Render::depthMapFBO);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, Render::depthMap, 0);
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

    }
    std::vector<std::string> resName(3+1);
    resName[0] = RES_DIR"";
    resName[1] = RES_DIR"gas.dae";
    resName[2] = RES_DIR"tree.dae";
    resName[3] = RES_DIR"girl.dae";
    staticModels.resize(3+1);
    animModels.resize(3+1);
    for(int i = 1; i < 3+1; i++)
    {
        auto x = new Model();
        //int anim = x->load(RES_DIR"untitled.gltf");
        int anim = x->load(resName[i]);
        if (anim)
            animModels[i] = x;
        else
            staticModels[i] = x;
    }
    t = new World;
    t->renderInit();


#ifdef USE_GUI

    g = new gui();
    g->init((GLFWwindow*)worldData->d->_window->_glfwPtr);
#endif


    this->maps.emplace_back(Map{.index = 0,});
    return 0;
}


int Render::drawTask(Task t){
    taskQueue.enqueue(t);
    return 0;
}


int addUnit(Map& Map, Unit& u)
{
    Map.unitSet.emplace_back(u);
    return 0;
}
int addSpirit(Map& Map, Unit& u)
{
    Map.spiritSet.emplace_back(u);
    return 0;
}

int Render::update(){
    static Task t;
    while(taskQueue.try_dequeue(t))
    {
        switch (t.type)
        {
            case Render::Task::TYPE::ADD_SPIRIT:
            {
                addSpirit(this->maps[0], t.u);
                break;
            }
            case Render::Task::TYPE::MOD_SPIRIT:
            {
                break;
            }
            case Render::Task::TYPE::DEL_SPIRIT:
            {
                break;
            }
            case Render::Task::TYPE::ADD_UNIT:
            {
                addUnit(this->maps[0], t.u);
                break;
            }
            case Render::Task::TYPE::MOD_UNIT:
            {
                break;
            }
            case Render::Task::TYPE::DEL_UNIT:
            {
                break;
            }
            default:
            {
                assert(NULL && "crash");
            }

        }
    }
    return 0;
}

int Render::draw() {
    float &currentFrame = worldData->currentFrame;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, worldData->w, worldData->h);

    glm::mat4 lightProjection, lightView;
    glm::mat4 &lightSpaceMatrix = worldData->lightSpaceMatrix;

    lightProjection = glm::ortho(worldData->orthoLeft, worldData->orthoRight, worldData->orthoBottom,
                                 worldData->orthoTop, worldData->near_plane, worldData->far_plane);
    lightView = glm::lookAt(glm::vec3(worldData->light1Pos.x, worldData->light1Pos.y, worldData->light1Pos.z),
                            worldData->lookCenterPos, worldData->lookUpPos);
    lightSpaceMatrix = lightProjection * lightView;

    if (worldData->shadowOn) {
        //glEnable(GL_POLYGON_OFFSET_FILL);
        //glPolygonOffset(worldData->offset1, worldData->offset2);
        getDepthMap();
        //glDisable(GL_POLYGON_OFFSET_FILL);

    }
    {
        glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glViewport(0, 0, worldData->w, worldData->h);


        Shader *curShader = shader[SHADER_LOGIC_TYPE::SHADER_LOGIC_TYPE_ANIM_MODEL_WITH_SHADOW];
        curShader->use();
        glm::mat4 projection = worldData->proj;
        glm::mat4 view = worldData->camera.getViewMatrix();
        glm::mat4 model = glm::mat4(1.0f);
        worldData->light2Pos = glm::vec3(6 * cos(currentFrame), 3, 6 * sin(currentFrame));

        {
            //curShader->setVec3("viewPos", worldData->camera.Position);
            curShader->setVec3("lightPos", worldData->light2Pos);
            curShader->setInt("shadowMap", 0);
            curShader->setInt("diffuseTexture", 1);
            if (worldData->shadowOn)
                curShader->setInt("shadowOn", 1);
            else
                curShader->setInt("shadowOn", 0);
        }


        auto &shadowOn = worldData->shadowOn;

        drawModelWithShadow();





        t->drawModels(0);


        if (worldData->particleOn) {
            p->draw();
        }
       this->render2dDraw();
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    if (worldData->bloomOn) {
        bool horizontal = true, first_iteration = true;
        unsigned int amount = 10;
        shader[SHADER_LOGIC_TYPE_BLUR]->use();
        shader[SHADER_LOGIC_TYPE_BLUR]->setInt("image", 0);
        for (unsigned int i = 0; i < amount; i++) {
            glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[horizontal]);
            shader[SHADER_LOGIC_TYPE_BLUR]->setInt("horizontal", horizontal);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, first_iteration ? colorBuffers[1]
                                                         : pingpongColorbuffers[!horizontal]);
            renderQuad();
            horizontal = !horizontal;
            if (first_iteration)
                first_iteration = false;
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader[SHADER_LOGIC_TYPE_BLOOM_FINAL]->use();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, colorBuffers[0]);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, pingpongColorbuffers[!horizontal]);
        shader[SHADER_LOGIC_TYPE_BLOOM_FINAL]->setInt("bloom", bloom);
        shader[SHADER_LOGIC_TYPE_BLOOM_FINAL]->setFloat("exposure", exposure);
        renderQuad();
    } else {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader[SHADER_LOGIC_TYPE_BLOOM_FINAL]->use();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, colorBuffers[0]);
        shader[SHADER_LOGIC_TYPE_BLOOM_FINAL]->setInt("bloom", worldData->bloomOn);
        shader[SHADER_LOGIC_TYPE_BLOOM_FINAL]->setFloat("exposure", exposure);
        renderQuad();
    }
//    //shadow debug
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    showDepthMap();

#ifdef USE_GUI
    g->render();
#endif


    return 0;
}


void Render::showDepthMap() {
    auto &debugDepthQuad = *shader[SHADER_LOGIC_TYPE::SHADER_LOGIC_TYPE_DEBUG];
    debugDepthQuad.use();
    debugDepthQuad.setInt("depthMap", 0);
    //debugDepthQuad.setFloat("near_plane", worldData->near_plane);
    //debugDepthQuad.setFloat("far_plane", worldData->far_plane);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, Render::depthMap);
    renderQuad();
}

int Render::shaderSetParam(Shader *curShader, DRAW_TYPE type) {
    float &currentFrame = worldData->currentFrame;

    worldData->light2Pos =  glm::vec3(6 * cos(currentFrame), 3, 6 * sin(currentFrame));

    if (type == DRAW_TYPE::DRAW_TYPE_ANIM_MODEL_WITH_SHADOW || type == DRAW_TYPE::DRAW_TYPE_ANIM_MODEL) {
        //curShader->setVec3("viewPos", worldData->camera.Position);
        curShader->setVec3("lightPos", worldData->light2Pos);
        curShader->setInt("shadowMap", 0);
        curShader->setInt("diffuseTexture", 1);
        if (type == DRAW_TYPE::DRAW_TYPE_ANIM_MODEL_WITH_SHADOW)
            curShader->setInt("shadowOn", 1);
        else
            curShader->setInt("shadowOn", 0);
    } else if (type == DRAW_TYPE::DRAW_TYPE_DEPTH) {

    }
    return 0;
}

int Render::drawModels(DRAW_TYPE type) {
    float &currentFrame = worldData->currentFrame;
    Shader *curShader = nullptr;

    if (type == DRAW_TYPE::DRAW_TYPE_ANIM_MODEL_WITH_SHADOW || type == DRAW_TYPE::DRAW_TYPE_ANIM_MODEL ||
        type == DRAW_TYPE::DRAW_TYPE_ANIM_MODEL_WITH_BLOOM) {
        curShader = Render::shader[SHADER_LOGIC_TYPE::SHADER_LOGIC_TYPE_ANIM_MODEL_WITH_SHADOW];
    } else if (type == DRAW_TYPE::DRAW_TYPE_DEPTH) {
        curShader = Render::shader[SHADER_LOGIC_TYPE::SHADER_LOGIC_TYPE_DEPTH_ANIM];
    }

    if (curShader == nullptr)
        return -1;
    curShader->use();
    glm::mat4 projection = worldData->proj;
    glm::mat4 view = worldData->camera.getViewMatrix();
    glm::mat4 model = glm::mat4(1.0f);
    glm::vec3 lightPos;
    shaderSetParam(curShader, type);



//    for(auto & E : worldData->map1.data)
//    {
//        model = glm::mat4(1.0f);
//
//        int modelID = E.second->modelID;
//        float x = Real::ToFloat(E.second->pos.x);
//        float y = Real::ToFloat(E.second->pos.y);
//        float z = Real::ToFloat(E.second->pos.z);
//
//        if(E.second->anim)
//        {
//            model = glm::mat4(1.0f);
//            //model = scale(model, glm::vec3(0.5f));
//            model = translate(model, glm::vec3(x, 1.0f, y));
//            //model = rotate(model, glm::radians(-90.0f), glm::vec3(1, 0, 0));
//            animModels[modelID]->draw(type, 1, curShader, model, view, projection, currentFrame);
//        }
//        else
//        {
//            model = translate(model, glm::vec3(x, 1.0f, y));
//            //model = rotate(model, glm::radians(-90.0f), glm::vec3(1, 0, 0));
//            model = scale(model, glm::vec3(0.8f));
//            staticModels[modelID]->draw(type, 1, curShader, model, view, projection, currentFrame);
//        }
//    }


    return 0;
}


void Render::getDepthMap() {
    float &currentFrame = worldData->currentFrame;
    glViewport(0, 0, worldData->SHADOW_WIDTH, worldData->SHADOW_HEIGHT);
    glBindFramebuffer(GL_FRAMEBUFFER, Render::depthMapFBO);

    glClear(GL_DEPTH_BUFFER_BIT);
    drawModels(DRAW_TYPE::DRAW_TYPE_DEPTH);
    t->drawModels(1);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glViewport(0, 0, worldData->w, worldData->h);
}

void Render::drawModelWithShadow() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, worldData->w, worldData->h);

    if (worldData->shadowOn == 1) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, Render::depthMap);
    }

    if (worldData->shadowOn) {
        drawModels(DRAW_TYPE::DRAW_TYPE_ANIM_MODEL_WITH_SHADOW);
    } else {
        drawModels(DRAW_TYPE::DRAW_TYPE_ANIM_MODEL);
    }

    if (worldData->shadowOn == 1) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}
