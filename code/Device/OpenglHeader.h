//
// Created by xarvie on 2020/10/6.
//

#ifndef INC_3D_OPENGLHEAD_H
#define INC_3D_OPENGLHEAD_H
#include "Config.h"

#if defined(IOS)
#include <OpenGLES/ES3/gl.h>
#include <OpenGLES/ES3/glext.h>

#elif defined(__EMSCRIPTEN__)
#include <GLES3/gl3.h>
#include <GLES3/gl2ext.h>
#else
#include <glad/glad.h>
#endif
#endif //INC_3D_OPENGLHEAD_H
