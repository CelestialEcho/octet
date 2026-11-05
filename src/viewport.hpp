#pragma once
#define LOGGING_ENABLED

#include <SDL3/SDL.h>
#include <glad/glad.h>
#include <logc/log.h>

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

    void poll() {
        while (running) {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_EVENT_QUIT || event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE) {
                    running = false;
                }
                else if (event.type == SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED) {
                    SDL_GetWindowSizeInPixels(window, &width, &height);
                    glViewport(0, 0, width, height);
                }
            }
    
            glClearColor(0.1f, 0.1f, 0.12f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            SDL_GL_SwapWindow(window);
        }
    }

    void quit() {
        SDL_GL_DestroyContext(ctx);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
};
    
}