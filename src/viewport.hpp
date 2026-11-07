#pragma once

#include <SDL3/SDL.h>
#include <glad/glad.h>
#include <logc/log.h>
#include <nanovg/nanovg.h>
#define NANOVG_GL3_IMPLEMENTATION
#include <nanovg/nanovg_gl.h>

#include "input.hpp"
#include "gui.hpp"

namespace oc {

class Viewport {
    bool running = true;
    int width, height;

    SDL_Window* window = nullptr;
    SDL_GLContext ctx = nullptr;
    NVGcontext* vg = nullptr;
    bool guiInitialized = false;

    Gui gui;

public:
    Viewport(int width, int height) : width(width), height(height) {}

    int getHeight() const { return height; }
    int getWidth() const { return width; }

    SDL_Window*& getWindow() { return window; }
    SDL_GLContext& getGLCtx() { return ctx; }

    bool init() {
        if (!SDL_Init(SDL_INIT_VIDEO)) {
            log_fatal("SDL_Init: %s", SDL_GetError());
            return false;
        }

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

        window = SDL_CreateWindow("Octet", width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
        if (!window) {
            log_fatal("Error creating SDL window: %s", SDL_GetError());
            quit();
            return false;
        }

        ctx = SDL_GL_CreateContext(window);
        if (!ctx) {
            log_fatal("Error creating OpenGL context: %s", SDL_GetError());
            quit();
            return false;
        }

        SDL_GL_MakeCurrent(window, ctx);
        SDL_SetWindowSurfaceVSync(window, 0);
        SDL_GL_SetSwapInterval(0);

        if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
            log_fatal("Failed to load OpenGL functions.");
            quit();
            return false;
        }

        log_info("GL driver version: %s | GLSL version: %s",
                 glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));

        SDL_GetWindowSizeInPixels(window, &width, &height);

        vg = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES);
        if (!vg) {
            log_fatal("Failed to create nanovg context");
            quit();
            return false;
        }

        gui.init(window, ctx);
        guiInitialized = true;

        return true;
    }

    void poll(Input& input) {
        while (running) {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                gui.handleInput(&event);
                if (event.type == SDL_EVENT_QUIT) {
                    running = false;
                } else if (event.type == SDL_EVENT_WINDOW_RESIZED) {
                    SDL_GetWindowSizeInPixels(window, &width, &height);
                }
                input.handle(event);
            }

            glViewport(0, 0, width, height);
            glClearColor(0.1f, 0.1f, 0.1f, 1.f);
            glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

            nvgBeginFrame(vg, width, height, 1.f);
            /*
                nvgBeginPath(vg);
                nvgCircle(vg, 300, 300, 180);
                nvgFillColor(vg, nvgRGBA(255, 128, 51, 255));
                nvgFill(vg);
            */
            nvgEndFrame(vg);

            // gui.poll() сам делает NewFrame/Render/RenderDrawData,
            // поэтому вызываем его после NanoVG — ImGui рисуется поверх.
            gui.poll();

            SDL_GL_SwapWindow(window);
            input.clear();
        }
    }

    void quit() {
        if (guiInitialized) {
            gui.quit();
            guiInitialized = false;
        }
        if (vg) {
            nvgDeleteGL3(vg);
            vg = nullptr;
        }
        if (ctx) {
            SDL_GL_DestroyContext(ctx);
            ctx = nullptr;
        }
        if (window) {
            SDL_DestroyWindow(window);
            window = nullptr;
        }
        SDL_Quit();
    }
};

}
