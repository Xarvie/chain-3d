#include "Render.h"
#include "Data.h"
#include <iostream>
#include <chrono>
#include <thread>
#include "Collision.h"

int main() {
    worldData = new WorldData();
    auto& d = *worldData->d;
    d.init();
    d.createWindow("ChainProject", 800, 600, 0, 1);

    d.VSYNC(worldData->vsync);
    Render r;
    r.init();
    r.render2DInit();
    r.init2d2(worldData->w, worldData->h);

    auto & ourShader = *r.shader[Render::SHADER_LOGIC_TYPE::SHADER_LOGIC_TYPE_2D2];
    glEnable(GL_BLEND);
    glBlendEquation(GL_FUNC_ADD);
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
    ourShader.use();

//    worldData->pGraphicsContext = new GraphicsContext(800, 600);
//    worldData->pRenderer = new Renderer();
//    worldData->pGraphicsContext->SetRenderer(worldData->pRenderer);
//    worldData->pRenderer->SetGraphicsContext(worldData->pGraphicsContext);

//    worldData->pPainter = new Painter(worldData->pGraphicsContext);

//    worldData->pCurrentTestScene = new BatchSpriteScene;



    worldData->lastFrame = d.getTime();

    Texture* t1 = new Texture(GL_TEXTURE_2D, RES_DIR"2d/boom.png", IMAGE);
    Texture* t2 = new Texture(GL_TEXTURE_2D, RES_DIR"2d/bb.png", IMAGE);

    while (d.shouldClose()) {
        d.processInput();
//        worldData->pGraphicsContext->BeginRender();
//        worldData->pGraphicsContext->ResetDrawcall();
        worldData->updateTime(d.getTime());
//        worldData->pCurrentTestScene->Update(worldData->deltaTime);
        glDisable(GL_DEPTH_TEST);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glViewport(0, 0, worldData->w, worldData->h);
        ourShader.use();
        ::Color c(1, 1, 1, 1.0f);


        r.drawTexture(0, 0, t1, c, worldData->currentFrame);
        //r.drawTexture(t1->w/2, t1->h/2, t2, c, worldData->currentFrame);
        //r.drawTexture(t1->w/2/2, t1->h/2/2, t2, c);
        //r.draw();

//        worldData->pCurrentTestScene->Draw(worldData->pPainter);
//        worldData->pGraphicsContext->EndRender();


        d.swapBuffers();
        d.pollEvents();


    }
    d.shutDown();
    return 0;
}
