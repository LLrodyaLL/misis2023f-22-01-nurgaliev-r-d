#include <iostream>

/*#include "imgui.h"
#include "GLFW/glfw3.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

int main()
{
    GLFWwindow* window = glfwCreateWindow(1280, 720, "AstMarker", nullptr, nullptr);
    if (window == nullptr)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync


    ImGui::SetNextWindowPos(ImVec2(2, 7));
    ImGui::SetNextWindowSize(ImVec2(4, 6));

    ImGui::Begin("First window");
    ImGui::Text("This is window A");
    ImGui::End();

    ImGui::Begin("First window");
    ImGui::Button("Button on window A");
    ImGui::End();

    return 0;
}*/

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>

int main()
{
    // Инициализация GLFW
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(800, 600, "ImGui Example", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // Инициализация ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // Главный цикл приложения
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Создание базового окна
        ImGui::SetNextWindowPos(ImVec2(5, 9));
        ImGui::SetNextWindowSize(ImVec2(456, 456));
        ImGui::Begin("AstMarker");

        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Очистка ресурсов
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
