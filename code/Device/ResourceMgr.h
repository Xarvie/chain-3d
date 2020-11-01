//
// Created by xarvie on 2020/10/8.
//

#ifndef INC_3D4_RESOURCEMGR_H
#define INC_3D4_RESOURCEMGR_H

#include <vector>
#include <string>
#include "Archives.h"
class ResourceMgr {
public:
    int loadFromPath(const char* name);
    std::vector<char> Res(const char* name);
    std::vector<char> Res(std::string name);
    Archives archives;
};

extern ResourceMgr res;
#endif //INC_3D4_RESOURCEMGR_H
