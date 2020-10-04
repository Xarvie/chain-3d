//
// Created by Xarvie on 12/12/2019.
//

#ifndef INC_3D_GUI_H
#define INC_3D_GUI_H

// dear imgui: standalone example application for GLFW + OpenGL 3, using programmable pipeline
// If you are new to dear imgui, see examples/README.txt and documentation at the top of imgui.cpp.
// (GLFW is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan graphics context creation, etc.)


#include "Config.h"
#include "imgui.h"
#if USE_SDL2
#include "imgui_impl_sdl.h"
#else
#include "imgui_impl_glfw.h"
#endif
#include "imgui_impl_opengl3.h"
#include <stdio.h>

#include <fstream>
#include <streambuf>
//#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include <glad/glad.h>

// About Desktop OpenGL function loaders:
//  Modern desktop OpenGL doesn't have a standard portable header file to load OpenGL function pointers.
//  Helper libraries are often used for this purpose! Here we are supporting a few common ones (gl3w, glew, glad).
//  You may use another loader/header of your choice (glext, glLoadGen, etc.), or chose to manually implement your own.
//#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
//#include <GL/gl3w.h>    // Initialize with gl3wInit()
//#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
//#include <GL/glew.h>    // Initialize with glewInit()
//#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
//#include <glad/glad.h>  // Initialize with gladLoadGL()
//
//#endif

// Include glfw3.h after our OpenGL definitions
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

#include "Camera.h"
#include "Device.h"
class gui {
public:
    int init(DeviceWindow* window);
    int render();
    int clean();
    DeviceWindow* window;

    bool show_demo_window = true;
    bool show_another_window = false;

    ImGuiIO* io;
#if USE_SDL2
    SDL_GLContext* gl_context;
#endif
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    //const char* fileToEdit = "C:/Users/Xarvie/Desktop/code/imgui-glfw3/code/imgui_demo.cpp";
};


class Point
{
public:
    Point()
    {
        x=0.0;
        y=0.0;
    }
    Point(float inx, float iny)
    {
        x=inx;
        y=iny;
    }
//析构函数
    ~Point(){}
    float getX() {return x;}
    float getY() {return y;}
//重载=操作符,实现两向量变量的赋值
    Point operator =(Point& inPoint)
    {
        Point temp;
        temp.x=inPoint.x;
        temp.y=inPoint.y;
        return temp;
    }
//重载+操作符,实现两向量变量的相加
    Point operator+(const Point& inPoint)
    {
//返回相加的结果
        return Point(inPoint.x + x, inPoint.y + y);
    }
//重载-操作符,实现两向量变量的相减
    Point operator-(const Point& inPoint)
    {
//返回相减的结果
        return Point(x - inPoint.x, y - inPoint.y);
    }
//重载*操作符,实现一个向量变量和一个浮点数的乘法
    Point operator*(float num)
    {
//返回缩放了的向量
        return Point(x * num, y * num);
    }
//重载/操作符,实现一个向量变量和一个浮点数的除法
    Point operator/(float num)
    {
//返回缩放了的向量
        return Point(x / num, y / num);
    }
//得到一个向量的绝对长度,即距原点的距离
    float Length();
private:
    float x;
    float y;
};
#endif //INC_3D_GUI_H
