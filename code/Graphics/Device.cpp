//
// Created by caspasex on 2020/6/29.
//

#include "Device.h"

Device::Window *Device::_window;

bool isFullScreen = false;

Device::Device() {

};

void Device::init() {
    glfwInit();
    int monitorCount = 0;
    _window = new Device::Window();
    GLFWmonitor **pMonitor = glfwGetMonitors(&monitorCount);

    if (pMonitor == nullptr) {
        std::cout << "error getMonitors" << std::endl;
    }
    this->_monitors.resize(monitorCount);

    for (int i = 0; i < monitorCount; i++) {
        const GLFWvidmode *mode = glfwGetVideoMode(pMonitor[i]);
        Monitor m;
        m._id = i;
        m._w = mode->width;
        m._h = mode->height;
        this->_monitors[i] = m;
    }
}

int Device::createWindow(std::string title, int x, int y, int fullScreen, int lockMouse) {

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWmonitor *pMonitor = isFullScreen ? glfwGetPrimaryMonitor() : NULL;
    GLFWwindow *window = glfwCreateWindow(x, y, title.c_str(), pMonitor, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    this->_window->_glfwPtr = window;
    glfwMakeContextCurrent(window);
    glfwSetErrorCallback(error_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_move_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    //glEnable(GL_CULL_FACE);

    glfwWindowHint(GLFW_SAMPLES, 2);
    glEnable(GL_BLEND);
    int xBuffer = 0, yBuffer = 0;
    glfwGetFramebufferSize(window, (int *) &xBuffer, (int *) &yBuffer);
    glViewport(0, 0, xBuffer, yBuffer);

    Device::_window->_w = x;
    Device::_window->_h = y;
    Device::_window->_bw = xBuffer;
    Device::_window->_bh = yBuffer;
    worldData->w = xBuffer;
    worldData->h = yBuffer;
    return 0;
}

void Device::getScreenSize(int &width, int &height, int monitorID) {
    if (monitorID >= _monitors.size())
        return;
    width = _monitors[monitorID]._w;
    height = _monitors[monitorID]._h;
}

void Device::getWindowsSize(int &width, int &height, int windowID) {
    glfwGetFramebufferSize(static_cast<GLFWwindow *>(_window->_glfwPtr), &width,
                           &height);
}

void Device::error_callback(int error, const char *description) {

}

void Device::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (action != GLFW_PRESS)
        return;
    switch (key) {
        case GLFW_KEY_ESCAPE:
            break;
        case GLFW_KEY_V:
        {
            static int LineMode = GL_FILL;
            if (LineMode == GL_FILL) {
                LineMode = GL_LINE;
            } else {
                LineMode = GL_FILL;
            }
            glPolygonMode(GL_FRONT_AND_BACK, LineMode);
            break;
        }
        default:
            break;
    }
}

void Device::processInput() {
    GLFWwindow *window = (GLFWwindow *) Device::_window->_glfwPtr;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        worldData->camera.ProcessKeyboard(FORWARD, worldData->deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        worldData->camera.ProcessKeyboard(BACKWARD, worldData->deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        worldData->camera.ProcessKeyboard(LEFT, worldData->deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        worldData->camera.ProcessKeyboard(RIGHT, worldData->deltaTime);

}

void Device::mouse_move_callback(GLFWwindow *window, double xpos, double ypos) {
    if (worldData->firstMouse) {
        worldData->lastX = xpos;
        worldData->lastY = ypos;
        worldData->firstMouse = false;
    }
    float xoffset = xpos - worldData->lastX;
    float yoffset = worldData->lastY - ypos;
    worldData->lastX = xpos;
    worldData->lastY = ypos;
    worldData->camera.ProcessMouseMovement(xoffset, yoffset);
}

void Device::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void Device::scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    worldData->camera.ProcessMouseScroll(yoffset);
}

void Device::mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
    if (action == GLFW_PRESS)
        switch (button) {
            case GLFW_MOUSE_BUTTON_LEFT:

                break;
            case GLFW_MOUSE_BUTTON_MIDDLE:

                break;
            case GLFW_MOUSE_BUTTON_RIGHT:

                break;
            default:
                return;
        }
    return;
}

bool Device::shouldClose() {
    return !glfwWindowShouldClose((GLFWwindow *) this->_window->_glfwPtr);
}

void Device::swapBuffers() {
    glfwSwapBuffers((GLFWwindow *) this->_window->_glfwPtr);
}

void Device::pollEvents() {
    glfwPollEvents();
}

void Device::shutDown() {
    glfwTerminate();
}

float Device::getTime() {
    return glfwGetTime();
}
void Device::VSYNC(bool on)
{

    glfwSwapInterval((int)on);
}