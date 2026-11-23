#pragma once

#include <cstring>

#include <imgui/imgui.h>

namespace ImGuiEx
{
    inline void SectionGap()
    {
        ImGui::Dummy(ImVec2(0, 2));
    }

    inline bool BrushSize(const char* label, int* size, int minSize = 1, int maxSize = 100)
    {
        ImDrawList* draw = ImGui::GetWindowDrawList();
        const ImGuiStyle& style = ImGui::GetStyle();

        const float boxSize = ImGui::GetFrameHeight() * 2.0f;
        const ImVec2 pos = ImGui::GetCursorScreenPos();
        const ImVec2 center = ImVec2(pos.x + boxSize * 0.5f, pos.y + boxSize * 0.5f);
        const float frameRadius = boxSize * 0.5f;

        float brushRadius = frameRadius * (float)*size / (float)maxSize;
        if (brushRadius < 1.0f) {
            brushRadius = 1.0f;
        }

        draw->AddCircleFilled(center, frameRadius, ImGui::GetColorU32(ImGuiCol_FrameBg));
        draw->AddCircle(center, frameRadius, ImGui::GetColorU32(ImGuiCol_Border));
        draw->AddCircleFilled(center, brushRadius, ImGui::GetColorU32(ImGuiCol_SliderGrab));
        draw->AddCircle(center, brushRadius, ImGui::GetColorU32(ImGuiCol_Text));
        ImGui::Dummy(ImVec2(boxSize, boxSize));

        ImGui::SameLine();
        const float blockHeight = ImGui::GetTextLineHeight() + style.ItemSpacing.y + ImGui::GetFrameHeight();
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + (boxSize - blockHeight) * 0.5f);

        ImGui::BeginGroup();
        ImGui::TextUnformatted(label, strstr(label, "##"));

        ImGui::PushID(label);
        ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
        const bool changed = ImGui::SliderInt("##slider", size, minSize, maxSize, "", ImGuiSliderFlags_AlwaysClamp);
        ImGui::PopID();
        ImGui::EndGroup();

        SectionGap();
        return changed;
    }
}