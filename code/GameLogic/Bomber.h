//
// Created by caspasex on 2020/7/8.
//

#ifndef INC_3D_BOMBER_H
#define INC_3D_BOMBER_H
#include "Unit.h"


class Bomber {
public:

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

    Unit* unit1;
};


#endif //INC_3D_BOMBER_H
