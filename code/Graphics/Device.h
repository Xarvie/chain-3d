//
// Created by caspasex on 2020/6/29.
//

#pragma once
#ifndef INC_3D_DEVICE_H
#define INC_3D_DEVICE_H

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <Graphics/Camera.h>
#include <Graphics/Shader.h>

#include <iostream>
#include <unordered_map>
#include "Config.h"

#include "Model.h"
#include "Data.h"

#if (USE_SDL2)
#include "SDL.h"
typedef SDL_Window DeviceWindow;
constexpr int KEY_UP = SDL_KEYUP;
constexpr int KEY_DOWN = SDL_KEYDOWN;
constexpr int MOUSE_BUTTON_L = SDL_BUTTON_LEFT;
constexpr int MOUSE_BUTTON_R = SDL_BUTTON_RIGHT;
constexpr int MOUSE_BUTTON_M = SDL_BUTTON_MIDDLE;
constexpr int MOUSE_BUTTON_DOWN = SDL_MOUSEBUTTONDOWN;
constexpr int MOUSE_BUTTON_UP = SDL_MOUSEBUTTONUP;
#else
#include <GLFW/glfw3.h>
    typedef GLFWwindow DeviceWindow;
    constexpr int KEY_UP = GLFW_RELEASE;
    constexpr int KEY_DOWN = GLFW_PRESS;
    constexpr int MOUSE_BUTTON_L = GLFW_MOUSE_BUTTON_LEFT;
    constexpr int MOUSE_BUTTON_R = GLFW_MOUSE_BUTTON_RIGHT;
    constexpr int MOUSE_BUTTON_M = GLFW_MOUSE_BUTTON_MIDDLE;
    constexpr int MOUSE_BUTTON_DOWN = GLFW_PRESS;
    constexpr int MOUSE_BUTTON_UP = GLFW_RELEASE;
#endif

class Device {
public:
    Device();

    Device(const Device &) = delete;

public:
    class Monitor {
    public:
        int _id;
        int _w;
        int _h;
    };

    std::vector<Monitor> _monitors;
#define setbit(x,y)  x|=(1<<y)
#define clrbit(x,y)  x&=~(1<<y)
#define reversebit(x,y)  x^=(1<<y)
#define getbit(x,y)   ((x) >> (y)&1)

    class GamePad{
    public:
        enum ControlType{
            CT_UP = 0,
            CT_DOWN,
            CT_LEFT,
            CT_RIGHT,
            CT_A,
            CT_B,
            CT_X,
            CT_Y,
            CT_START,
            CT_BACK,
        };
    public:
        int up(bool press);
        int down(bool press);
        int left(bool press);
        int right(bool press);
        int a(bool press);
        int b(bool press);
        int x(bool press);
        int y(bool press);

        int start(bool press);
        int back(bool press);



    public:
        class ControlState{
        public:
            unsigned int curStates = 0;
            unsigned int preStates = 0;
            unsigned int newDown = 0;
            unsigned int newUp = 0;
            int detectControlState();

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
        };
        ControlState cs;

    };
    GamePad gp;
    class Window {
    public:
        int _w;
        int _h;
        int _bw;
        int _bh;
        void *rawPtr;
        void *content;
#if (USE_SDL2)
        SDL_GLContext sdlContext;
#endif
    };

    static Window *_window;

    class OperateEvent {
        union Date {
            struct {
                int _op;//0 press, 1 up, 2 wheel click, 3 wheel up, 4 wheel down
                double _x;
                double _y;
            } _mouseEv;
            struct {
                int _op;//0 press, 1 up
                int _key;
            } _key;
        } _data;

    };

public:
    void init();

    int createWindow(std::string title, int x, int y, int fullScreen, int lockMouse);

    void getScreenSize(int &width, int &height, int monitorID = 0);

    void getWindowsSize(int &width, int &height, int windowID);

    bool running();

    static void swapBuffers();

    void pollEvents();

    void shutDown();

    static float getTime();

    void VSYNC(bool on);

    static void MSAA();

public:
    static void framebuffer_size_callback(DeviceWindow *window, int width, int height);

    static void mouse_move_callback(DeviceWindow *window, double xpos, double ypos);

    static void scroll_callback(DeviceWindow *window, double xoffset, double yoffset);

    static void mouse_button_callback(DeviceWindow *window, int button, int action, int mods);

    static void processInput();

    static void error_callback(int error, const char *description);

    static void key_callback(DeviceWindow *window, int key, int scancode, int action, int mods);


    bool _running = true;
};


#endif //INC_3D_DEVICE_H
