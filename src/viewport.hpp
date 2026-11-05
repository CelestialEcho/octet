#pragma once

#include <SDL3/SDL.h>
#include <glad/glad.h>
#include <logc/log.h>

#include "input.hpp"

namespace oc {

class Viewport {
    bool running;
    int width, height;
    
    SDL_Window* window;
    SDL_GLContext ctx;
    
public:
    Viewport( const int& width, const int& height ) : running(true), height(height), width(width) {}

    int getHeight() const { return height; }
    int getWidth() const { return width; }
    
    bool init() {
        this->window = SDL_CreateWindow("Octet", width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
        if (!window) {
            log_fatal("CreateWindow: %s\n", SDL_GetError());
            return false;
        }

        this->ctx = SDL_GL_CreateContext(window);
        if (!ctx) {
            log_fatal("CreateContext: %s\n", SDL_GetError());
            return false;
        }

        if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
            log_fatal("GLAD: failed\n");
            return false;
        }

        log_trace("GL driver version: %s | GLSL version: %s\n", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));
        SDL_GL_SetSwapInterval(1);

        SDL_GetWindowSizeInPixels(window, &width, &height);
        glViewport(0, 0, width, height);
      
        return true;
    }

    void poll(Input& input) {
        while (running) {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_EVENT_QUIT) {
                    running = false;
                }
                input.handle(event);
            }
            
    
            glClearColor(0.1f, 0.1f, 0.1f, 1.f);
            glClear(GL_COLOR_BUFFER_BIT);
            SDL_GL_SwapWindow(window);
            input.clear();
        }
    }

    void quit() {
        SDL_GL_DestroyContext(ctx);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
};
    
}