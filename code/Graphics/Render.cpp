//
// Created by caspasex on 2020/6/29.
//

#include "Render.h"

#include <Graphics/Camera.h>
#include <Graphics/Shader.h>

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
unsigned int quadVBO;

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

    // texture 1
    // ---------
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char *data = stbi_load(RES_DIR"boom.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
//    // texture 2
//    // ---------
//    glGenTextures(1, &texture2);
//    glBindTexture(GL_TEXTURE_2D, texture2);
//    // set the texture wrapping parameters
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    // set texture filtering parameters
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    // load image, create texture and generate mipmaps
//    data = stbi_load(RES_DIR"texture_t1.png", &width, &height, &nrChannels, 0);
//    if (data)
//    {
//        // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
//        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
//        glGenerateMipmap(GL_TEXTURE_2D);
//    }
//    else
//    {
//        std::cout << "Failed to load texture" << std::endl;
//    }
//    stbi_image_free(data);

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    ourShader.use(); // don't forget to activate/use the shader before setting uniforms!
    // either set it manually like so:
    glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);
    // or set it via the texture class
    //ourShader.setInt("texture2", 1);
    return 0;
}

int Render::render2dDraw()
{
   // glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    //glClear(GL_COLOR_BUFFER_BIT);

    auto & ourShader = *shader[SHADER_LOGIC_TYPE::SHADER_LOGIC_TYPE_2D];

    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
//    glActiveTexture(GL_TEXTURE1);
//    glBindTexture(GL_TEXTURE_2D, texture2);

    // render container
    ourShader.use();
    int maxCount = 4;

    ourShader.setInt("offset", int(worldData->currentFrame*10) % maxCount + 4);
    ourShader.setInt("wcount", 4);
    ourShader.setInt("hcount", 4);
    //ourShader.setInt("allcount", 30);


    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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


int Render::init() {

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    //glEnable(GL_CULL_FACE);

    glfwWindowHint(GLFW_SAMPLES, worldData->MSAA);
    glEnable(GL_BLEND);

    if (p == nullptr)
        p = new Particle;
    p->init();
    worldData->proj = glm::perspective(worldData->camera.Zoom,
                                       float(worldData->w) / float(worldData->h),
                                       0.1f, 50.0f);

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

    return 0;
}


int Render::draw() {
    float &currentFrame = worldData->currentFrame;

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
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

        this->render2dDraw();
        if (worldData->particleOn) {
            p->draw();
        }
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



    for(auto & E : worldData->map1.data)
    {
        model = glm::mat4(1.0f);

        int modelID = E.second->modelID;
        float x = Real::ToFloat(E.second->pos.x);
        float y = Real::ToFloat(E.second->pos.y);
        float z = Real::ToFloat(E.second->pos.z);




        if(modelID == 3){
            model = glm::mat4(1.0f);
            //model = scale(model, glm::vec3(0.5f));
            model = translate(model, glm::vec3(x, 1.0f, y));
            //model = rotate(model, glm::radians(-90.0f), glm::vec3(1, 0, 0));
            animModels[modelID]->draw(type, 1, curShader, model, view, projection, currentFrame);
        }
        else{
            model = translate(model, glm::vec3(x, 1.0f, y));
            //model = rotate(model, glm::radians(-90.0f), glm::vec3(1, 0, 0));
            model = scale(model, glm::vec3(0.8f));
            staticModels[modelID]->draw(type, 1, curShader, model, view, projection, currentFrame);
        }
    }
//    for(int x = 0; x < 15; x++)
//        for(int y = 0; y < 15; y++)
//        {
//            if(map1[x][y] == 2)
//            {
//
//            }
//        }





//    auto srcModel = model;
//
//    int halfDist = 2;
//
//    for (int x = -halfDist; x < halfDist; x++) {
//        for (int y = -halfDist; y < halfDist; y++) {
//            model = translate(srcModel, glm::vec3(x * 8, y * 8, 0));
//            animModels[0]->draw(type, 1, curShader, model, view, projection, currentFrame);
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

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
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