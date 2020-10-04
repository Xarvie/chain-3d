//
// Created by Xarvie on 12/12/2019.
//

#include "gui.h"

#include "Data.h"

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

int gui::clean()
{
    ImGui_ImplOpenGL3_Shutdown();
#if USE_SDL2
    ImGui_ImplSDL2_Shutdown();
#else
    ImGui_ImplGlfw_Shutdown();
#endif

    ImGui::DestroyContext();
    return 0;
}

int gui::render(){
    ImGui_ImplOpenGL3_NewFrame();
#if USE_SDL2
    ImGui_ImplSDL2_NewFrame(this->window);
#else
    ImGui_ImplGlfw_NewFrame();
#endif
    ImGui::NewFrame();

    // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
    if (show_demo_window)
        ImGui::ShowDemoWindow(&show_demo_window);
    ImGuiWindowFlags window_flags = 0;
    window_flags |= ImGuiWindowFlags_NoTitleBar;
    ImGui::Begin("FPS", nullptr, window_flags);
    ImGui::Text("%.2f ms/frame (%.0f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();


    {
        static float f = 0.0f;
        static int counter = 0;

        ImGui::Begin("Terminal");

        ImGui::Text("-");
        ImGui::Checkbox("Checkbox show_demo_window", &show_demo_window);
        ImGui::Checkbox("Checkbox show_another_window", &show_another_window);
        ImGui::Text("light1Pos");
        ImGui::DragFloat("##light1Pos.x", &worldData->light1Pos.x, 1.0);
        ImGui::DragFloat("##light1Pos.y", &worldData->light1Pos.y, 1.0);
        ImGui::DragFloat("##light1Pos.z", &worldData->light1Pos.z, 1.0);
        ImGui::Text("plane");
        ImGui::DragFloat("##near_plane", &worldData->near_plane, 1.0);
        ImGui::DragFloat("##far_plane", &worldData->far_plane, 1.0);
        ImGui::Text("ortho");
        ImGui::DragFloat("##orthoLeft", &worldData->orthoLeft, 1.0);
        ImGui::DragFloat("##orthoRight", &worldData->orthoRight, 1.0);
        ImGui::DragFloat("##orthoBottom", &worldData->orthoBottom, 1.0);
        ImGui::DragFloat("##orthoTop", &worldData->orthoTop, 1.0);
        ImGui::Text("lookUpPos");
        ImGui::DragFloat("##lookUpPos.x", &worldData->lookUpPos.x, 1.0);
        ImGui::DragFloat("##lookUpPos.y", &worldData->lookUpPos.y, 1.0);
        ImGui::DragFloat("##lookUpPos.z", &worldData->lookUpPos.z, 1.0);
        ImGui::Text("lookCenterPos");
        ImGui::DragFloat("##lookCenterPos.x", &worldData->lookCenterPos.x, 1.0);
        ImGui::DragFloat("##lookCenterPos.y", &worldData->lookCenterPos.y, 1.0);
        ImGui::DragFloat("##lookCenterPos.z", &worldData->lookCenterPos.z, 1.0);
        ImGui::Text("polyoffset");
        ImGui::DragFloat("##polyoffset.x", &worldData->offset1, 1.0);
        ImGui::DragFloat("##polyoffset.y", &worldData->offset2, 1.0);
        ImGui::Text("light1offset");
        ImGui::DragFloat("##light1offset.x", &worldData->light1Offset.x, 1.0);
        ImGui::DragFloat("##light1offset.y", &worldData->light1Offset.y, 1.0);
        ImGui::DragFloat("##light1offset.z", &worldData->light1Offset.z, 1.0);
        ImGui::Text("ro");
        ImGui::DragFloat("##ro", &worldData->ro, 1.0);
        ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

        if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);
        ImGui::Text("pos %.3f,%.3f,%.3f", worldData->camera.Position.x, worldData->camera.Position.y, worldData->camera.Position.z);

        ImGui::End();
    }

    // 3. Show another simple window.
    if (show_another_window)
    {
        ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        ImGui::Text("Hello from another window!");
        if (ImGui::Button("Close Me"))
            show_another_window = false;
        ImGui::End();
    }
    // Rendering
    ImGui::Render();
#if USE_SDL2
    glViewport(0, 0, (int)io->DisplaySize.x, (int)io->DisplaySize.y);
    glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    //SDL_GL_SwapWindow(window);
#else
    int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        //glfwSwapBuffers(window);
#endif

    return 0;
}

int gui::init(DeviceWindow* window)
{
    this->window = window;
    const char* glsl_version = "#version 150";
    bool err = false;
    err = gladLoadGL();
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
     io = &ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

#ifdef USE_SDL2
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init(glsl_version);
#else
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
#endif
    static const ImWchar ranges2[] =
            {
                    0x2000, 0x206F,
                    0x3000, 0x30FF,
                    0x31F0, 0x31FF,
                    0xFF00, 0xFFEF,
                    0x4e00, 0x9FAF,
                    0,
            };

    ImFontConfig config;
    config.MergeMode = true;
    static const ImWchar ranges1[] =
            {
                    0x0020, 0x00FF,
                    0,
            };

#if defined(WIN32)
    ImFont* font = io->Fonts->AddFontFromFileTTF(RES_DIR"Font/zqk.ttf", 16, NULL, ranges2);
    IM_ASSERT(font != NULL);
    ImFont* font2 = io->Fonts->AddFontFromFileTTF("c:/Windows/Fonts/consola.ttf", 16, &config, ranges1);
    IM_ASSERT(font2 != NULL);
#elif defined(LINUX)
    ImFont* font = io.Fonts->AddFontFromFileTTF(RES_DIR"Font/zqk.ttf", 16, NULL, ranges2);
    IM_ASSERT(font != NULL);
    ImFont* font2 = io.Fonts->AddFontFromFileTTF("c:/Windows/Fonts/consola.ttf", 16, &config, ranges1);
    IM_ASSERT(font2 != NULL);
#elif defined(__APPLE__)
    ImFont* font = io.Fonts->AddFontFromFileTTF(RES_DIR"Font/zqk.ttf", 16, NULL, ranges2);
    IM_ASSERT(font != NULL);
    ImFont* font2 = io.Fonts->AddFontFromFileTTF("/System/Library/Fonts/Menlo.ttc", 16, &config, ranges1);
    IM_ASSERT(font2 != NULL);
#endif


    io->Fonts->Build();


    ImGuiStyle& style = ImGui::GetStyle();
    //style.ScaleAllSizes(1.0);

    //io.DisplayFramebufferScale = { 2, 2 };

    io->FontGlobalScale = 1.0f;
    return 0;
}


#include <cmath>
using namespace std;
const float Pi=3.14159265;

float Point::Length()
{
    return sqrt(x*x + y*y);
}

float Distance(Point& pPoint1, Point& pPoint2)
{
    float subX=pPoint1.getX()-pPoint2.getX();
    float subY=pPoint1.getY()-pPoint2.getY();
    return sqrt(subX * subX + subY * subY);
}
//得到两向量的点积(即内积)
float DotProduct(Point& pPoint1, Point& pPoint2)
{
    return pPoint1.getX() * pPoint2.getX() + pPoint1.getY() * pPoint2.getY();
}

bool AngleLargeThanPi(Point& point1, Point& point2)
{
    float temp=point1.getX() * point2.getY() - point2.getX()* point1.getY();
    return ( temp < 0);//>1801
}

float AngleBetweenPoints(Point& pPoint1, Point& pPoint2)
{
    float cos_theta = DotProduct(pPoint1,pPoint2) / (pPoint1.Length() * pPoint2.Length());
    if(AngleLargeThanPi(pPoint1,pPoint2) )//vec theta
        return 360-acos(cos_theta)*180/Pi;
    else
        return acos(cos_theta)*180/Pi;
}
