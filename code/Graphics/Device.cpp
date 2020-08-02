//
// Created by caspasex on 2020/6/29.
//

#include "Device.h"

Device::Window *Device::_window;

bool isFullScreen = false;


int Device::GamePad::up(bool press){
    if(press)
        this->cs.curStates |= (1u << ControlType::CT_UP);
    else
        this->cs.curStates &= ~(1u << ControlType::CT_UP);

    return 0;
}

int Device::GamePad::down(bool press){
    if(press)
        this->cs.curStates |= (1u << ControlType::CT_DOWN);
    else
        this->cs.curStates &= ~(1u << ControlType::CT_DOWN);
    return 0;
}

int Device::GamePad::left(bool press){
    if(press)
        this->cs.curStates |= (1u << ControlType::CT_LEFT);
    else
        this->cs.curStates &= ~(1u << ControlType::CT_LEFT);
    return 0;
}

int Device::GamePad::right(bool press){
    if(press)
        this->cs.curStates |= (1u << ControlType::CT_RIGHT);
    else
        this->cs.curStates &= ~(1u << ControlType::CT_RIGHT);
    return 0;
}

int Device::GamePad::a(bool press){
    if(press)
        this->cs.curStates |= (1u << ControlType::CT_A);
    else
        this->cs.curStates &= ~(1u << ControlType::CT_A);
    return 0;
}

int Device::GamePad::b(bool press){
    if(press)
        this->cs.curStates |= (1u << ControlType::CT_B);
    else
        this->cs.curStates &= ~(1u << ControlType::CT_B);
    return 0;
}

int Device::GamePad::x(bool press){
    if(press)
        this->cs.curStates |= (1u << ControlType::CT_X);
    else
        this->cs.curStates &= ~(1u << ControlType::CT_X);
    return 0;
}

int Device::GamePad::y(bool press){
    if(press)
        this->cs.curStates |= (1u << ControlType::CT_Y);
    else
        this->cs.curStates &= ~(1u << ControlType::CT_Y);
    return 0;
}

int Device::GamePad::start(bool press){
    if(press)
        this->cs.curStates |= (1u << ControlType::CT_START);
    else
        this->cs.curStates &= ~(1u << ControlType::CT_START);
    return 0;
}

int Device::GamePad::back(bool press){
    if(press)
        this->cs.curStates |= (1u << ControlType::CT_BACK);
    else
        this->cs.curStates &= ~(1u << ControlType::CT_BACK);
    return 0;
}

int Device::GamePad::ControlState::detectControlState(){
    unsigned int diff = this->curStates ^ this->preStates;
    this->newDown = diff & this->curStates;
    this->newUp = diff & (~ this->curStates);

    if((newDown | newUp) == 0)
        return 0;


    if(((newDown) >> (ControlType::CT_UP)&1u))
         upEvent(true);
    if(((newDown) >> (ControlType::CT_DOWN)&1u))
        downEvent(true);
    if(((newDown) >> (ControlType::CT_LEFT)&1u))
        leftEvent(true);
    if(((newDown) >> (ControlType::CT_RIGHT)&1u))
        rightEvent(true);
    if(((newDown) >> (ControlType::CT_A)&1u))
        aEvent(true);
    if(((newDown) >> (ControlType::CT_B)&1u))
        bEvent(true);
    if(((newDown) >> (ControlType::CT_X)&1u))
        xEvent(true);
    if(((newDown) >> (ControlType::CT_Y)&1u))
        yEvent(true);
    if(((newDown) >> (ControlType::CT_START)&1u))
        startEvent(true);
    if(((newDown) >> (ControlType::CT_BACK)&1u))
        backEvent(true);


    if(((newUp) >> (ControlType::CT_UP)&1u))
        upEvent(false);
    if(((newUp) >> (ControlType::CT_DOWN)&1u))
        downEvent(false);
    if(((newUp) >> (ControlType::CT_LEFT)&1u))
        leftEvent(false);
    if(((newUp) >> (ControlType::CT_RIGHT)&1u))
        rightEvent(false);
    if(((newUp) >> (ControlType::CT_A)&1u))
        aEvent(false);
    if(((newUp) >> (ControlType::CT_B)&1u))
        bEvent(false);
    if(((newUp) >> (ControlType::CT_X)&1u))
        xEvent(false);
    if(((newUp) >> (ControlType::CT_Y)&1u))
        yEvent(false);
    if(((newUp) >> (ControlType::CT_START)&1u))
        startEvent(false);
    if(((newUp) >> (ControlType::CT_BACK)&1u))
        backEvent(false);

    return 0;
}

int Device::GamePad::ControlState::upEvent(bool press){
    worldData->bomber->upEvent(press);
    return 0;
}

int Device::GamePad::ControlState::downEvent(bool press){
    worldData->bomber->downEvent(press);
    return 0;
}

int Device::GamePad::ControlState::leftEvent(bool press){
    worldData->bomber->leftEvent(press);
    return 0;
}

int Device::GamePad::ControlState::rightEvent(bool press){
    worldData->bomber->rightEvent(press);
    return 0;
}

int Device::GamePad::ControlState::aEvent(bool press){
    return 0;
}

int Device::GamePad::ControlState::bEvent(bool press){
    return 0;
}

int Device::GamePad::ControlState::xEvent(bool press){
    return 0;
}

int Device::GamePad::ControlState::yEvent(bool press){
    return 0;
}

int Device::GamePad::ControlState::startEvent(bool press){
    return 0;
}
int Device::GamePad::ControlState::backEvent(bool press){
    return 0;
}

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

extern bool GUIMode;
static double mouseX = 0;
static double mouseY = 0;

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
        case GLFW_KEY_F1:
        {

            GUIMode = !GUIMode;
            if (GUIMode) {
                glfwGetCursorPos(window, &mouseX, &mouseY);
                //glfwSetCursorPos(window, 1, 1);
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

            } else {
                glfwSetCursorPos(window, mouseX, mouseY);
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            }
            break;
        }
        case GLFW_KEY_F2:
        {
            worldData->shadowOn = !worldData->shadowOn;
            break;
        }
        case GLFW_KEY_F3:
        {
            worldData->particleOn = !worldData->particleOn;
            break;
        }
        case GLFW_KEY_F4:
        {
            worldData->bloomOn = !worldData->bloomOn;
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


    worldData->d->gp.up(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS);
    worldData->d->gp.down(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS);
    worldData->d->gp.left(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS);
    worldData->d->gp.right(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS);
    worldData->d->gp.a(glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS);
    worldData->d->gp.b(glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS);
    worldData->d->gp.x(glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS);
    worldData->d->gp.y(glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS);
    worldData->d->gp.start(glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS);
    worldData->d->gp.back(glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS);


}

void Device::mouse_move_callback(GLFWwindow *window, double xpos, double ypos) {
    if(GUIMode)
        return ;
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
    if(GUIMode)
        return ;
    worldData->camera.ProcessMouseScroll(yoffset);
}

void Device::mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
    if(GUIMode)
        return ;

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
    this->gp.cs.detectControlState();
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