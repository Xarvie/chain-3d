//
// Created by caspasex on 2020/7/8.
//

#ifndef INC_3D_BOMBER_H
#define INC_3D_BOMBER_H


#include "Component.h"
#include "MapMgr.h"

class Bomber {
public:
    int init();
    int initMap();
    int initUnit();

    int upEvent(bool press);
    int downEvent(bool press);
    int leftEvent(bool press);
    int rightEvent(bool press);
    int aEvent(bool press);
    int bEvent(bool press);
    int xEvent(bool press);
    int yEvent(bool press);

    int startEvent(bool press);
    int backEvent(bool press);


    GameData gd;
};
extern Bomber* game;

#endif //INC_3D_BOMBER_H
