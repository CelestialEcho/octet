#pragma once

#include <SDL3/SDL.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_sdl3.h>

#include <logc/log.h>

#include "input.hpp"
#include "imgui_ex.hpp"

namespace oc {

class Gui {
    static constexpr float panelWidth = 200.0f;

    float brushColor[3]  = {};
    int   brushSize      = 4;
    bool  eraser         = false;
    float canvasColor[3] = {};
    bool  gridEnabled    = false;

    void drawSidePanel(float panelHeight) {
        ImGui::SetNextWindowPos(ImVec2(-1, -1));
        ImGui::SetNextWindowSize(ImVec2(panelWidth, panelHeight + 1));
        ImGui::Begin("main", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoNav);

        drawColorSettings();
        drawBrushSettings();
        drawCanvasSettings();
        drawProjectSettings();

        ImGui::End();
    }

    void drawColorSettings() {
        ImGui::SeparatorText("Color settings");
        ImGui::ColorPicker3("##BColor", brushColor);
        ImGuiEx::SectionGap();
    }

    void drawBrushSettings() {
        ImGui::SeparatorText("Brush settings");
        if (ImGuiEx::BrushSize("Size", &brushSize, 1, 100)) {
            
        }
        ImGui::Checkbox("Eraser", &eraser);
        ImGuiEx::SectionGap();
    }

    void drawCanvasSettings() {
        ImGui::SeparatorText("Canvas settings");
        ImGui::ColorPicker3("##VColor", canvasColor);
        ImGui::Checkbox("Grid", &gridEnabled);
        ImGuiEx::SectionGap();
    }

    void drawProjectSettings() {
        ImGui::SeparatorText("Project settings");
    }
public:
    bool init(SDL_Window* window, SDL_GLContext glContext) noexcept {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.IniFilename = nullptr;

        ImGui::StyleColorsDark();

        return ImGui_ImplSDL3_InitForOpenGL(window, glContext)
            && ImGui_ImplOpenGL3_Init(nullptr);
    }

    void draw(float /*windowHeight*/, float windowLength, Input& /*input*/) noexcept {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        drawSidePanel(windowLength);

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