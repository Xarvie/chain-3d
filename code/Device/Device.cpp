//
// Created by caspasex on 2020/6/29.
//

#include "Device.h"

#ifdef __EMSCRIPTEN__
#include "emscripten.h"
#include <emscripten/html5.h>
#endif
Device::Window *Device::_window;

bool isFullScreen = false;

Device* Device::get() {
    static Device self;
    return &self;
}

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
    //worldData->bomber->upEvent(press);
    return 0;
}

int Device::GamePad::ControlState::downEvent(bool press){
    //worldData->bomber->downEvent(press);
    return 0;
}

int Device::GamePad::ControlState::leftEvent(bool press){
   // worldData->bomber->leftEvent(press);
    return 0;
}

int Device::GamePad::ControlState::rightEvent(bool press){
   // worldData->bomber->rightEvent(press);
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

void Device::getScreenSize(int &width, int &height, int monitorID) {
    if (monitorID >= _monitors.size())
        return;
    width = _monitors[monitorID]._w;
    height = _monitors[monitorID]._h;
}


static double mouseX = 0;
static double mouseY = 0;
//SDL_bool fullscreen = SDL_FALSE;
void Device::mouse_button_callback(DeviceWindow *window, int button, int action, int mods) {

    if(action == MOUSE_BUTTON_DOWN) {
        switch (button) {
            case MOUSE_BUTTON_L:
//                SDL_SetWindowFullscreen(window,
//                                        fullscreen == SDL_FALSE?fullscreen=SDL_TRUE:fullscreen=SDL_FALSE);
                break;
            case MOUSE_BUTTON_M:

                break;
            case MOUSE_BUTTON_R:

                break;
            default:
                return;
        }
    }
    else if(action == MOUSE_BUTTON_UP) {
        switch (button) {
            case MOUSE_BUTTON_L:

                break;
            case MOUSE_BUTTON_M:

                break;
            case MOUSE_BUTTON_R:

                break;
            default:
                return;
        }
    }

    return;
}


#if !defined(USE_SDL2)
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
    //std::this_thread::sleep_for(std::chrono::seconds(10));
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    //std::this_thread::sleep_for(std::chrono::seconds(10));
    GLFWmonitor *pMonitor = isFullScreen ? glfwGetPrimaryMonitor() : NULL;
    DeviceWindow *window = glfwCreateWindow(x, y, title.c_str(), pMonitor, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    this->_window->rawPtr = window;
    glfwMakeContextCurrent(window);
    glfwSetErrorCallback(error_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_move_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

#if !defined(__EMSCRIPTEN__)
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
#endif

    int xBuffer = 0, yBuffer = 0;
    glfwGetFramebufferSize(window, (int *) &xBuffer, (int *) &yBuffer);
    glViewport(0, 0, xBuffer, yBuffer);

    Device::_window->_w = x;
    Device::_window->_h = y;
    Device::_window->_bw = xBuffer;
    Device::_window->_bh = yBuffer;
//    worldData->w = xBuffer;
//    worldData->h = yBuffer;
    return 0;
}


void Device::getWindowsSize(int &width, int &height, int windowID) {
    glfwGetFramebufferSize(_window->rawPtr, &width,
                           &height);
}

void Device::error_callback(int error, const char *description) {

}


void Device::key_callback(DeviceWindow *window, int key, int scancode, int action, int mods) {
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
            //glPolygonMode(GL_FRONT_AND_BACK, LineMode);
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
//            worldData->shadowOn = !worldData->shadowOn;
            break;
        }
        case GLFW_KEY_F3:
        {
//            worldData->particleOn = !worldData->particleOn;
            break;
        }
        case GLFW_KEY_F4:
        {
//            worldData->bloomOn = !worldData->bloomOn;
            break;
        }
        default:
            break;
    }
}

void Device::processInput() {
    DeviceWindow *window = (DeviceWindow *) Device::_window->rawPtr;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
//    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//        worldData->camera.ProcessKeyboard(FORWARD, worldData->deltaTime);
//    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//        worldData->camera.ProcessKeyboard(BACKWARD, worldData->deltaTime);
//    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//        worldData->camera.ProcessKeyboard(LEFT, worldData->deltaTime);
//    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//        worldData->camera.ProcessKeyboard(RIGHT, worldData->deltaTime);
//
//
//    worldData->d->gp.up(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS);
//    worldData->d->gp.down(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS);
//    worldData->d->gp.left(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS);
//    worldData->d->gp.right(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS);
//    worldData->d->gp.a(glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS);
//    worldData->d->gp.b(glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS);
//    worldData->d->gp.x(glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS);
//    worldData->d->gp.y(glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS);
//    worldData->d->gp.start(glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS);
//    worldData->d->gp.back(glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS);


}

void Device::mouse_move_callback(DeviceWindow *window, double xpos, double ypos) {
    if(GUIMode)
        return ;
//    if (worldData->firstMouse) {
//        worldData->lastX = xpos;
//        worldData->lastY = ypos;
//        worldData->firstMouse = false;
//    }
//    float xoffset = xpos - worldData->lastX;
//    float yoffset = worldData->lastY - ypos;
//    worldData->lastX = xpos;
//    worldData->lastY = ypos;
//    worldData->camera.ProcessMouseMovement(xoffset, yoffset);
}

void Device::framebuffer_size_callback(DeviceWindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void Device::scroll_callback(DeviceWindow *window, double xoffset, double yoffset) {
    if(GUIMode)
        return ;
//    worldData->camera.ProcessMouseScroll(yoffset);
}

void Device::swapBuffers() {
    glfwSwapBuffers((DeviceWindow *) Device::_window->rawPtr);
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

void Device::MSAA(int msaa) {
        glfwWindowHint(GLFW_SAMPLES, msaa);
}
bool Device::running() {
    _running = !glfwWindowShouldClose((DeviceWindow *) this->_window->rawPtr);
    return _running;
}

int Device::getDrawSize(int *w, int* h){
#if defined(__EMSCRIPTEN__)
        return emscripten_get_canvas_element_size("#canvas", w, h);
#endif

    glfwGetFramebufferSize(_window->rawPtr, w,
                           h);
    return 0;
}

#else

void Device::init() {
    _window = new Window;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) < 0) {
        std::cout << "SDL_Init error Line:" << __LINE__ << std::endl;
        abort();
    }
#if defined(IOS)
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_EGL, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

#elif defined(__EMSCRIPTEN__)
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#else
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
#endif
//    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
//    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
//    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
//    std::cout << __LINE__ << std::endl;
//
//    int monitorCount = 0;
//    _window = new Device::Window();
//    monitorCount = SDL_GetNumVideoDisplays();
//    std::cout << __LINE__ << std::endl;
//    if (monitorCount == 0) {
//        std::cout << "error getMonitors" << std::endl;
//        abort();
//    }
//
//    this->_monitors.resize(monitorCount);
//
//    for (int i = 0; i < monitorCount; i++) {
//        SDL_Rect rc;
//        SDL_GetDisplayBounds(i, &rc);
//        Monitor m;
//        m._id = i;
//        m._w = rc.w;
//        m._h = rc.h;
//        this->_monitors[i] = m;
//    }
}

int Device::createWindow(std::string title, int x, int y, int fullScreen, int lockMouse) {
#if defined(IOS)
    auto* window = SDL_CreateWindow(title.c_str(),
                                    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                    x<0?this->_monitors[0]._w:x, y<0?this->_monitors[0]._h:y,
                                    SDL_WINDOW_FULLSCREEN  |SDL_WINDOW_INPUT_GRABBED | SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
#elif defined(__EMSCRIPTEN__)
    auto* window = SDL_CreateWindow(title.c_str(),
                                    0, 0,
                                    x<0?this->_monitors[0]._w:x, y<0?this->_monitors[0]._h:y,
                                    SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    if(window == NULL)
    std::cout << "NULL" << std::endl;
#else
    auto* window = SDL_CreateWindow(title.c_str(),
                                    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                    x<0?this->_monitors[0]._w:x, y<0?this->_monitors[0]._h:y,
                                    SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
#endif
    std::cout << SDL_GetError() << std::endl;
    Device::_window->sdlContext = SDL_GL_CreateContext(window);
    Device::_window->rawPtr = window;
    SDL_GL_MakeCurrent(window, Device::_window->sdlContext);
#if(!defined(IOS) and !defined(__EMSCRIPTEN__))
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
#endif

    int xBuffer = x, yBuffer = y;
    SDL_GL_GetDrawableSize(window, &xBuffer, &yBuffer);
    glViewport(0, 0, xBuffer, yBuffer);

    Device::_window->_w = x;
    Device::_window->_h = y;
    Device::_window->_bw = xBuffer;
    Device::_window->_bh = yBuffer;
    return 0;
}


void Device::getWindowsSize(int &width, int &height, int windowID) {

    SDL_GetWindowSize(static_cast<DeviceWindow*>(_window->rawPtr), &width, &height);

}

void Device::error_callback(int error, const char *description) {

}

void Device::key_callback(SDL_Window *window, int key, int scancode, int action, int mods) {
        if(action == KEY_DOWN)
        {
            key;
        }
        else if(action == KEY_UP)
        {
            key;
        }

    //    if (action != GLFW_PRESS)
//        return;
//    switch (key) {
//        case GLFW_KEY_ESCAPE:
//            break;
//        case GLFW_KEY_V:
//        {
//            static int LineMode = GL_FILL;
//            if (LineMode == GL_FILL) {
//                LineMode = GL_LINE;
//            } else {
//                LineMode = GL_FILL;
//            }
//            glPolygonMode(GL_FRONT_AND_BACK, LineMode);
//            break;
//        }
//        case GLFW_KEY_F1:
//        {
//
//            GUIMode = !GUIMode;
//            if (GUIMode) {
//                glfwGetCursorPos(window, &mouseX, &mouseY);
//                //glfwSetCursorPos(window, 1, 1);
//                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
//
//            } else {
//                glfwSetCursorPos(window, mouseX, mouseY);
//                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//            }
//            break;
//        }
//        case GLFW_KEY_F2:
//        {
//            worldData->shadowOn = !worldData->shadowOn;
//            break;
//        }
//        case GLFW_KEY_F3:
//        {
//            worldData->particleOn = !worldData->particleOn;
//            break;
//        }
//        case GLFW_KEY_F4:
//        {
//            worldData->bloomOn = !worldData->bloomOn;
//            break;
//        }
//        default:
//            break;
//    }
}

void Device::processInput() {
//    DeviceWindow *window = (DeviceWindow *) Device::_window->rawPtr;
//    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//        glfwSetWindowShouldClose(window, true);
//    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//        worldData->camera.ProcessKeyboard(FORWARD, worldData->deltaTime);
//    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//        worldData->camera.ProcessKeyboard(BACKWARD, worldData->deltaTime);
//    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//        worldData->camera.ProcessKeyboard(LEFT, worldData->deltaTime);
//    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//        worldData->camera.ProcessKeyboard(RIGHT, worldData->deltaTime);
//
//
//    worldData->d->gp.up(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS);
//    worldData->d->gp.down(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS);
//    worldData->d->gp.left(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS);
//    worldData->d->gp.right(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS);
//    worldData->d->gp.a(glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS);
//    worldData->d->gp.b(glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS);
//    worldData->d->gp.x(glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS);
//    worldData->d->gp.y(glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS);
//    worldData->d->gp.start(glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS);
//    worldData->d->gp.back(glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS);
//

}

void Device::mouse_move_callback(DeviceWindow *window, double xpos, double ypos) {
//    if(GUIMode)
//        return ;
//    if (worldData->firstMouse) {
//        worldData->lastX = xpos;
//        worldData->lastY = ypos;
//        worldData->firstMouse = false;
//    }
//    float xoffset = xpos - worldData->lastX;
//    float yoffset = worldData->lastY - ypos;
//    worldData->lastX = xpos;
//    worldData->lastY = ypos;
//    worldData->camera.ProcessMouseMovement(xoffset, yoffset);
}

void Device::framebuffer_size_callback(DeviceWindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void Device::scroll_callback(DeviceWindow *window, double xoffset, double yoffset) {
//    if(GUIMode)
//        return ;
//    worldData->camera.ProcessMouseScroll(yoffset);
}

void Device::swapBuffers() {
    SDL_GL_SwapWindow((DeviceWindow *) Device::_window->rawPtr);
}

bool Device::running() {
    return _running;
}

void Device::pollEvents() {
    static SDL_Event e;

    while (SDL_PollEvent(&e)) {
#ifdef USE_GUI
        //ImGui_ImplSDL2_ProcessEvent(&e);
#endif
        switch (e.type) {
            case SDL_FINGERMOTION:
            case SDL_FINGERDOWN:
            case SDL_FINGERUP: {
                //std::cout <<"finger" << __LINE__ << std::endl;
                break;
            }
            case SDL_QUIT:
                _running = false;
                break;
            case SDL_KEYDOWN:
            case SDL_KEYUP:{
                this->key_callback((DeviceWindow *) this->_window->rawPtr,
                                   e.key.keysym.sym,
                                   e.key.keysym.scancode,
                                   e.type,
                                   e.key.keysym.mod
                );
                //std::cout <<"finger" << __LINE__ << std::endl;
                break;
            }
            case SDL_MOUSEBUTTONDOWN:
            {
//                SDL_SetWindowFullscreen((DeviceWindow *) this->_window->rawPtr,
//                                        fullscreen == SDL_FALSE?fullscreen=SDL_TRUE:fullscreen=SDL_FALSE);
                this->mouse_button_callback((DeviceWindow *) this->_window->rawPtr,e.button.button ,e.type, 0);
//                std::cout <<"down" << __LINE__ << std::endl;
                break;
            }
            case SDL_MOUSEBUTTONUP:
                this->mouse_button_callback((DeviceWindow *) this->_window->rawPtr,e.button.button ,e.type, 0);
//                std::cout <<"up" << __LINE__ << std::endl;
                break;
            case SDL_MOUSEMOTION:
            {
                //std::cout <<"finger" << __LINE__ << std::endl;
                break;
            }
            case SDL_WINDOWEVENT_RESIZED:
            {
                std::cout << "Window resized to: " << e.window.data1 << " - " << e.window.data2 << '\n';
                break;
            }

        }

    }

}

void Device::shutDown() {

    SDL_DestroyWindow((DeviceWindow *) this->_window->rawPtr);
}

#include <ctime>
float Device::getTime() {
    return SDL_GetTicks()/1000.0f;
    //return (float)(std::clock()*1000/ CLOCKS_PER_SEC)/1000;
}

void Device::VSYNC(bool on)
{
    SDL_GL_SetSwapInterval((int)on);
}

void Device::MSAA(int msaa) {
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, msaa);
}

int Device::getDrawSize(int *w, int* h){
#if defined(__EMSCRIPTEN__)
        return emscripten_get_canvas_element_size("#canvas", w, h);
#else
    SDL_GL_GetDrawableSize(_window->rawPtr, w , h);
#endif
    return 0;
}
#endif
