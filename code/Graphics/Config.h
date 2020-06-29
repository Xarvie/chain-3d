//
// Created by caspasex on 2019/10/17.
//

#pragma once
#ifndef INC_3D_CONFIG_H
#define INC_3D_CONFIG_H

#ifdef __APPLE__
#define PROJECT_ROOT_DIR "../"
#define RES_DIR PROJECT_ROOT_DIR"resources/"
#define SHADER_DIR PROJECT_ROOT_DIR"code/Graphics/shader/"
#elif __WIN32
#define RES_DIR "C:/Users/caspasex/Desktop/3dm/resources"
#define SHADER_DIR "C:/Users/caspasex/Desktop/3dm/code/shader"
#endif

#endif //DIR_CONFIG_H
