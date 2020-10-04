#include "Render.h"
#include "Data.h"
#include <iostream>
#include <chrono>
#include <thread>
#include "Collision.h"
#include <Queue.h>
#include <atomic>

std::atomic<char> waiting = 2;




class MYint{
public:
     MYint operator+(int a){

        return *this;
    }
    int data;
};




int main(int argc, char **argv){

    std::thread rt2 = std::thread([&] {
        waiting--;
        while (waiting);
        game = new Bomber();
        game->init();
        while (worldData->d->running()) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    });

    worldData = new WorldData();
    auto &d = *worldData->d;
    d.init();

    d.createWindow("ChainProject", 1366, 1080, 0, 1);

    d.VSYNC(worldData->vsync);

    worldData->lastFrame = d.getTime();

    Render *r = Render::get();
    r->init();
    r->render2DInit();
    r->init2d2(worldData->w, worldData->h);

    auto &ourShader = *r->shader[Render::SHADER_LOGIC_TYPE::SHADER_LOGIC_TYPE_2D2];
    glEnable(GL_BLEND);
    glBlendEquation(GL_FUNC_ADD);
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    ourShader.use();
    waiting--;

    while (d.running()) {
        d.pollEvents();
        worldData->updateTime(d.getTime());
        glDisable(GL_DEPTH_TEST);

        glClear(GL_COLOR_BUFFER_BIT);
        glViewport(0, 0, worldData->w, worldData->h);
        ourShader.use();

        r->update();
        r->render2dDraw();
        d.processInput();
        d.swapBuffers();
    }
    worldData->d->shutDown();

//    std::thread rt1 = std::thread([&] {
//
//
//    });




    //rt2.join();
//    rt1.join();
//
    return 0;
}
