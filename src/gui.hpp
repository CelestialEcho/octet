#pragma once

#include <SDL3/SDL.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl3.h>
#include <imgui/imgui_impl_opengl3.h>

namespace oc {

class Gui {
    
public:
    Gui() = default;

    void init(SDL_Window* window, SDL_GLContext ctx) {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGui_ImplSDL3_InitForOpenGL(window, ctx);
        ImGui_ImplOpenGL3_Init("#version 460");
    }

    void handleInput(SDL_Event* event) {
        ImGui_ImplSDL3_ProcessEvent(event);
    }
    
    void poll() noexcept {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Octet");
            ImGui::TextColored(ImVec4(1.0, 0.3, 0.3, 1.0), "Hello World!");
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }    

    void quit() noexcept {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL3_Shutdown();
        ImGui::DestroyContext();
    }
};
    
}