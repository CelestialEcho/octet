#pragma once

#include <SDL3/SDL.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_sdl3.h>


namespace oc {

class Gui {
public:
    bool init(SDL_Window* window, SDL_GLContext glContext) noexcept {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.IniFilename = nullptr;
        ImGui::StyleColorsDark();
        
        if (!ImGui_ImplSDL3_InitForOpenGL(window, glContext)) {
            return false;
        }
        
        if (!ImGui_ImplOpenGL3_Init(nullptr)) {
            return false;
        }
        
        return true;
    }

    void draw(float windowHeight, float windowLength) noexcept {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        ImGui::SetNextWindowPos(ImVec2(-1, -1));
        ImGui::SetNextWindowSize(ImVec2(200, windowLength + 1));
        ImGui::Begin("main", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoNav);
        ImGui::Text("Hello from ImGui");
        ImGui::End();
        
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void quit() {
        if (ImGui::GetCurrentContext()) {
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplSDL3_Shutdown();
            ImGui::DestroyContext();
        }
    }

    void handle(const SDL_Event& event) {
        ImGui_ImplSDL3_ProcessEvent(&event);
    }
};
    
}