#include "Render.h"
#include "Data.h"
#include <iostream>
#include <chrono>
#include <thread>

int main() {
    worldData = new WorldData();
    auto& d = *worldData->d;
    d.init();
    d.createWindow("ChainProject", 1024, 768, 0, 1);

    d.VSYNC(worldData->vsync);
    Render r;
    r.init();



    worldData->lastFrame = d.getTime();

    while (d.shouldClose()) {
        d.processInput();

        worldData->updateTime(d.getTime());

        r.draw();



        d.swapBuffers();
        d.pollEvents();


    }
    d.shutDown();
    return 0;
}