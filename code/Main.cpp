#include "Render.h"
#include "Data.h"
#include <iostream>
#include "Particle.h"

int main() {
    worldData = new WorldData();
    auto& d = *worldData->d;
    d.init();
    d.createWindow("ChainProject", 1024, 768, 0, 1);

    d.VSYNC(true);
    Render r;
    r.init();

    Particle p;
    p.init();


    while (d.shouldClose()) {
        d.processInput();

        worldData->updateTime(d.getTime());

        r.draw();

        p.draw();

        d.swapBuffers();
        d.pollEvents();

    }
    d.shutDown();
    return 0;
}