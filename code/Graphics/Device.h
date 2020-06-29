//
// Created by caspasex on 2020/6/29.
//

#pragma once
#ifndef INC_3D_DEVICE_H
#define INC_3D_DEVICE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <Graphics/Camera.h>
#include <Graphics/Shader.h>

#include <iostream>
#include <unordered_map>
#include "Config.h"

#include "Model.h"
#include "Data.h"


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

    class Window {
    public:
        int _w;
        int _h;
        int _bw;
        int _bh;
        void *_glfwPtr;
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

    bool shouldClose();

    void swapBuffers();

    void pollEvents();

    void shutDown();

    float getTime();

public:
    static void framebuffer_size_callback(GLFWwindow *window, int width, int height);

    static void mouse_move_callback(GLFWwindow *window, double xpos, double ypos);

    static void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

    static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);

    static void processInput();

    static void error_callback(int error, const char *description);

    static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
};


#endif //INC_3D_DEVICE_H
