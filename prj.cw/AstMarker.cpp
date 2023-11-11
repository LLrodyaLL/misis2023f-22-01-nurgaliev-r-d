#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include<imgui_impl_opengl3_loader.h>
#include <stdio.h>
#include <string>
#include "nfd.h"
#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

#ifdef __EMSCRIPTEN__   
#include "../libs/emscripten/emscripten_mainloop_stub.h"
#endif

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}



bool showButtons = false;
bool showSubButtons = false;

// Main code
int main(int, char**)
{
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    const char* glsl_version = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

    // Create window with graphics context
    GLFWwindow* window = glfwCreateWindow(1280, 720, "AstMarker", nullptr, nullptr);
    if (window == nullptr)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsLight();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);


    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Main loop
#ifdef __EMSCRIPTEN__
    // For an Emscripten build we are disabling file-system access, so let's not attempt to do a fopen() of the imgui.ini file.
    // You may manually call LoadIniSettingsFromMemory() to load settings from your own storage.
    io.IniFilename = nullptr;
    EMSCRIPTEN_MAINLOOP_BEGIN
#else
    while (!glfwWindowShouldClose(window))
#endif
    {

        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGuiIO& io = ImGui::GetIO();
        float windowWidth = io.DisplaySize.x;
        float windowHeight = io.DisplaySize.y;


        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::SetNextWindowPos(ImVec2(100, 300));
            ImGui::SetNextWindowSize(ImVec2(500, 500));
            ImGui::SetNextWindowBgAlpha(1.0);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 2.0f);
            ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.0, 0.0, 0.0, 1.0));
            ImGui::Begin("FIRST WINDOW");

            ImGuiWindowFlags_NoScrollbar;

            ImVec2 windowSize_1 = ImGui::GetWindowSize();
            ImVec2 windowPos_1 = ImGui::GetWindowPos();
            ImVec2 textSize_1 = ImGui::CalcTextSize("Window 1");

            float posX_1 = windowPos_1.x + (windowSize_1.x - textSize_1.x) * 0.5f;
            float posY_1 = windowPos_1.y + (windowSize_1.y - textSize_1.y) * 0.5f;

            ImDrawList* drawList = ImGui::GetWindowDrawList();
            drawList->AddText(ImVec2(posX_1, posY_1), ImGui::GetColorU32(ImGuiCol_Text), "Window 1");


            ImGui::End();
            ImGui::PopStyleVar();
            ImGui::PopStyleColor();

            ImGui::SetNextWindowPos(ImVec2(700, 300));
            ImGui::SetNextWindowSize(ImVec2(500, 500));
            ImGui::SetNextWindowBgAlpha(1.0);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 2.0f);
            ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.0, 0.0, 0.0, 1.0));
            ImGui::Begin("SECOND WINDOW");

            ImGuiWindowFlags_NoScrollbar;

            ImVec2 windowSize_2 = ImGui::GetWindowSize();
            ImVec2 windowPos_2 = ImGui::GetWindowPos();
            ImVec2 textSize_2 = ImGui::CalcTextSize("Window 2");

            float posX_2 = windowPos_2.x + (windowSize_2.x - textSize_2.x) * 0.5f;
            float posY_2 = windowPos_2.y + (windowSize_2.y - textSize_2.y) * 0.5f;

            ImDrawList* drawList_2 = ImGui::GetWindowDrawList();
            drawList_2->AddText(ImVec2(posX_2, posY_2), ImGui::GetColorU32(ImGuiCol_Text), "Window 2");

           

            ImGui::End();
            ImGui::PopStyleVar();
            ImGui::PopStyleColor();

            ImGui::SetNextWindowPos(ImVec2(1300, 300));
            ImGui::SetNextWindowSize(ImVec2(500, 500));
            ImGui::SetNextWindowBgAlpha(1.0);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 2.0f);
            ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.0, 0.0, 0.0, 1.0));
            ImGui::Begin("OVERLAY WINDOW");

            ImGuiWindowFlags_NoScrollbar;
            
            ImVec2 windowSize_3 = ImGui::GetWindowSize();
            ImVec2 windowPos_3 = ImGui::GetWindowPos();
            ImVec2 textSize_3 = ImGui::CalcTextSize("Overlay Window");

            float posX_3 = windowPos_3.x + (windowSize_3.x - textSize_3.x) * 0.5f;
            float posY_3 = windowPos_3.y + (windowSize_3.y - textSize_3.y) * 0.5f;

            ImDrawList* drawList_3 = ImGui::GetWindowDrawList();
            drawList_3->AddText(ImVec2(posX_3, posY_3), ImGui::GetColorU32(ImGuiCol_Text), "Overlay Window");

            ImGui::End();
            ImGui::PopStyleVar();
            ImGui::PopStyleColor();



            ImGui::SetNextWindowPos(ImVec2(0, 0));
            ImGui::Begin("Settings");
            ImGuiWindowFlags_None;

            if (ImGui::Button("Files", ImVec2(160, 30))) {
                showButtons = !showButtons;
            }

            if (showButtons) {
                if (ImGui::Button("Import a set of points", ImVec2(160, 30))) {
                    nfdchar_t* outPath = NULL;
                    nfdresult_t result = NFD_OpenDialog(NULL, NULL, &outPath);

                    if (result == NFD_OKAY) {
                        puts("Success!");
                        puts(outPath);
                        free(outPath);
                    }
                    else if (result == NFD_CANCEL) {
                        puts("User pressed cancel.");
                    }
                    else {
                        printf("Error: %s\n", NFD_GetError());
                    }
                }

                if (ImGui::Button("Export", ImVec2(160, 30))) {
                    nfdchar_t* outPath = NULL;
                    nfdresult_t result = NFD_OpenDialog(NULL, NULL, &outPath);

                    if (result == NFD_OKAY) {
                        puts("Success!");
                        puts(outPath);
                        free(outPath);
                    }
                    else if (result == NFD_CANCEL) {
                        puts("User pressed cancel.");
                    }
                    else {
                        printf("Error: %s\n", NFD_GetError());
                    }
                }

                if (ImGui::Button("Close", ImVec2(160, 30))) {
                    showButtons = false;
                }
            }

            ImGui::End();

        }

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }
#ifdef __EMSCRIPTEN__
    EMSCRIPTEN_MAINLOOP_END;
#endif

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
