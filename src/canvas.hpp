#pragma once

#include <logc/log.h>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <nanovg/nanovg.h>
#define NANOVG_GL3_IMPLEMENTATION
#include <nanovg/nanovg_gl.h>

#include <vector>

class Canvas {
    struct Camera {
        glm::dvec2 pos = { 0, 0 };
        float zoom = 1.f;
    } localCamera;

    struct Brush {
        NVGcolor color;
        float size;
    } brush;

    struct Stroke {
        glm::uint16 id;
        glm::dvec2 pos;
        Brush usedBrush;
    };

    NVGcontext* ctx = nullptr;
    std::vector<Stroke> strokeBuffer;
    
public:
    Canvas() = default;
    Camera& getCamera() { return localCamera; }

    bool init() {
        ctx = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES);
        if (!ctx) {
            log_fatal("Failed to create nanovg context");
            return false;
        }
        
        return true;
    }

    void draw(const float& width, const float& height) {
        nvgSave(ctx);
        nvgTranslate(ctx, width * 0.5f, height * 0.5f);
        nvgScale(ctx, (float)localCamera.zoom, (float)localCamera.zoom);
        nvgTranslate(ctx, (float)-localCamera.pos.x, (float)-localCamera.pos.y);
        nvgBeginFrame(ctx, width, height, 1.f);
        /* world coords drawing */

        
        nvgEndFrame(ctx);
        nvgRestore(ctx);
    }

    void quit() {
        if (ctx) {
            nvgDeleteGL3(ctx);
            ctx = nullptr;
        }
    }

    void pushStroke(const float& x, const float& y) {
        
    }
};