//
// Created by caspasex on 2019/10/17.
//

#pragma once
#ifndef INC_3D_CONFIG_H
#define INC_3D_CONFIG_H

#ifdef __APPLE__
#define PROJECT_ROOT_DIR "/Users/xarvie/Desktop/chain-3d/"
#define RES_DIR PROJECT_ROOT_DIR"resources/"
#define SHADER_DIR RES_DIR"Shader/"
#elif __WIN32
#define PROJECT_ROOT_DIR "Z:/chain-3d"
//#define PROJECT_ROOT_DIR "../"
#define RES_DIR PROJECT_ROOT_DIR"resources/"
#define SHADER_DIR PROJECT_ROOT_DIR"code/Graphics/shader/"
#endif

#define USE_SDL2
#define __EMSCRIPTEN__X
#define USE_GUI
#define IOSX

#define USE_ASSIMP
#if defined(IOS) or defined(__EMSCRIPTEN__)
#undef USE_ASSIMP
#endif
#define GLES_SILENCE_DEPRECATION
#include "OpenglHeader.h"
#endif //DIR_CONFIG_H
