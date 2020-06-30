#include "Render.h"
#include "Data.h"
#include <iostream>

int main() {
    worldData = new WorldData();
    auto& d = *worldData->d;
    d.init();
    d.createWindow("ChainProject", 1024, 768, 0, 1);

    d.VSYNC(true);
    Render r;
    r.init();


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