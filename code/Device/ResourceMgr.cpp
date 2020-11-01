//
// Created by xarvie on 2020/10/8.
//

#include "ResourceMgr.h"
#include <iostream>
ResourceMgr res;
int ResourceMgr::loadFromPath(const char* name){
    return archives.openDataFile(name);
}

std::vector<char> ResourceMgr::Res(const char* name){
    return archives.readFile(name);
}

std::vector<char> ResourceMgr::Res(std::string name){
    return archives.readFile(name.c_str());
}