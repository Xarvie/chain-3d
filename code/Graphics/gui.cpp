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
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    return 0;
}

int gui::render(){
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
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

    {
        auto cpos = editor.GetCursorPosition();
        ImGui::Begin("Text Editor Demo", nullptr, ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_MenuBar);
        ImGui::SetWindowSize(ImVec2(800, 600), ImGuiCond_FirstUseEver);
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Save"))
                {
                    auto textToSave = editor.GetText();
                    /// save text....
                }
                if (ImGui::MenuItem("Quit", "Alt-F4"))
                    return -1;
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Edit"))
            {
                bool ro = editor.IsReadOnly();
                if (ImGui::MenuItem("Read-only mode", nullptr, &ro))
                    editor.SetReadOnly(ro);
                ImGui::Separator();

                if (ImGui::MenuItem("Undo", "ALT-Backspace", nullptr, !ro && editor.CanUndo()))
                    editor.Undo();
                if (ImGui::MenuItem("Redo", "Ctrl-Y", nullptr, !ro && editor.CanRedo()))
                    editor.Redo();

                ImGui::Separator();

                if (ImGui::MenuItem("Copy", "Ctrl-C", nullptr, editor.HasSelection()))
                    editor.Copy();
                if (ImGui::MenuItem("Cut", "Ctrl-X", nullptr, !ro && editor.HasSelection()))
                    editor.Cut();
                if (ImGui::MenuItem("Delete", "Del", nullptr, !ro && editor.HasSelection()))
                    editor.Delete();
                if (ImGui::MenuItem("Paste", "Ctrl-V", nullptr, !ro && ImGui::GetClipboardText() != nullptr))
                    editor.Paste();

                ImGui::Separator();

                if (ImGui::MenuItem("Select all", nullptr, nullptr))
                    editor.SetSelection(TextEditor::Coordinates(), TextEditor::Coordinates(editor.GetTotalLines(), 0));

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("View"))
            {
                if (ImGui::MenuItem("Dark palette"))
                    editor.SetPalette(TextEditor::GetDarkPalette());
                if (ImGui::MenuItem("Light palette"))
                    editor.SetPalette(TextEditor::GetLightPalette());
                if (ImGui::MenuItem("Retro blue palette"))
                    editor.SetPalette(TextEditor::GetRetroBluePalette());
                if (ImGui::MenuItem("VS Light Palette"))
                    editor.SetPalette(TextEditor::GetVSLightPalette());

                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        ImGui::Text("%6d/%-6d %6d lines  | %s | %s | %s | %s", cpos.mLine + 1, cpos.mColumn + 1, editor.GetTotalLines(),
                    editor.IsOverwrite() ? "Ovr" : "Ins",
                    editor.CanUndo() ? "*" : " ",
                    editor.GetLanguageDefinition().mName.c_str(), fileToEdit);

        editor.Render("TextEditor");
        ImGui::End();
    }

    // Rendering
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    //glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
    //glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    return 0;
}
int gui::init(GLFWwindow* window)
{
    this->window = window;
    const char* glsl_version = "#version 150";
    bool err = false;
    err = gladLoadGL();
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

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
    ImFont* font = io.Fonts->AddFontFromFileTTF(RES_DIR"Font/zqk.ttf", 16, NULL, ranges2);
    IM_ASSERT(font != NULL);
    ImFont* font2 = io.Fonts->AddFontFromFileTTF("c:/Windows/Fonts/consola.ttf", 16, &config, ranges1);
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





    io.Fonts->Build();


    ImGuiStyle& style = ImGui::GetStyle();
    //style.ScaleAllSizes(1.0);

    //io.DisplayFramebufferScale = { 2, 2 };

    io.FontGlobalScale = 1.0f;
    // Our state




///////////////////////////////////////////////////////////////////////
// TEXT EDITOR SAMPLE

    auto lang = TextEditor::LanguageDefinition::CPlusPlus();

    // set your own identifiers
    static const char* identifiers[] = {
            "HWND", "HRESULT", "LPRESULT","D3D11_RENDER_TARGET_VIEW_DESC", "DXGI_SWAP_CHAIN_DESC","MSG","LRESULT","WPARAM", "LPARAM","UINT","LPVOID",
            "ID3D11Device", "ID3D11DeviceContext", "ID3D11Buffer", "ID3D11Buffer", "ID3D10Blob", "ID3D11VertexShader", "ID3D11InputLayout", "ID3D11Buffer",
            "ID3D10Blob", "ID3D11PixelShader", "ID3D11SamplerState", "ID3D11ShaderResourceView", "ID3D11RasterizerState", "ID3D11BlendState", "ID3D11DepthStencilState",
            "IDXGISwapChain", "ID3D11RenderTargetView", "ID3D11Texture2D", "TextEditor" };
    static const char* idecls[] =
            {
                    "typedef HWND_* HWND", "typedef long HRESULT", "typedef long* LPRESULT", "struct D3D11_RENDER_TARGET_VIEW_DESC", "struct DXGI_SWAP_CHAIN_DESC",
                    "typedef tagMSG MSG\n * Message structure","typedef LONG_PTR LRESULT","WPARAM", "LPARAM","UINT","LPVOID",
                    "ID3D11Device", "ID3D11DeviceContext", "ID3D11Buffer", "ID3D11Buffer", "ID3D10Blob", "ID3D11VertexShader", "ID3D11InputLayout", "ID3D11Buffer",
                    "ID3D10Blob", "ID3D11PixelShader", "ID3D11SamplerState", "ID3D11ShaderResourceView", "ID3D11RasterizerState", "ID3D11BlendState", "ID3D11DepthStencilState",
                    "IDXGISwapChain", "ID3D11RenderTargetView", "ID3D11Texture2D", "class TextEditor" };
    for (int i = 0; i < sizeof(identifiers) / sizeof(identifiers[0]); ++i)
    {
        TextEditor::Identifier id;
        id.mDeclaration = std::string(idecls[i]);
        lang.mIdentifiers.insert(std::make_pair(std::string(identifiers[i]), id));
    }
    editor.SetLanguageDefinition(lang);
    //editor.SetPalette(TextEditor::GetLightPalette());

    // error markers
    TextEditor::ErrorMarkers markers;
    markers.insert(std::make_pair<int, std::string>(6, "Example error here:\nInclude file not found: \"TextEditor.h\""));
    markers.insert(std::make_pair<int, std::string>(41, "Another example error"));
    editor.SetErrorMarkers(markers);

    // "breakpoint" markers
    //TextEditor::Breakpoints bpts;
    //bpts.insert(24);
    //bpts.insert(47);
    //editor.SetBreakpoints(bpts);


    //	static const char* fileToEdit = "test.cpp";

    {
        std::ifstream t(fileToEdit);
        if (t.good())
        {
            std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
            editor.SetText(str);
        }
    }

    //////////////////////////////



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
