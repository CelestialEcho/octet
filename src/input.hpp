#pragma once

#include <SDL3/SDL.h>
#include <array>
#include <glm/glm.hpp>

namespace oc {

class Input {
    std::array<bool, SDL_SCANCODE_COUNT> held;
    std::array<bool, SDL_SCANCODE_COUNT> pressed;
    std::array<bool, SDL_SCANCODE_COUNT> released;

    struct Mouse {
        glm::vec2 pos;
        glm::vec2 delta;
        bool isLeftDown = false, isMiddleDown = false, isRightDown = false;
    };

    Mouse mouse;
    
public:
    Input() = default;
    
    void handle( const SDL_Event& event ) {        
        if (event.type == SDL_EVENT_KEY_DOWN) {
            if (!event.key.repeat && !held[event.key.scancode]) {
                pressed[event.key.scancode] = true;
            }
            held[event.key.scancode] = true;
            
        } else if (event.type == SDL_EVENT_KEY_UP) {
            held[event.key.scancode] = false;
            released[event.key.scancode] = true;
        }

        if (event.type == SDL_EVENT_MOUSE_MOTION) {
            mouse.pos = glm::vec2( event.motion.x, event.motion.y );
            mouse.delta += glm::vec2( event.motion.xrel, event.motion.yrel );
            
        } else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
            if (event.button.button == SDL_BUTTON_LEFT) { mouse.isLeftDown = true; }
            if (event.button.button == SDL_BUTTON_MIDDLE) { mouse.isMiddleDown = true; }
            if (event.button.button == SDL_BUTTON_RIGHT) { mouse.isRightDown = true; }
            
        } else if (event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
            if (event.button.button == SDL_BUTTON_LEFT) { mouse.isLeftDown = false; }
            if (event.button.button == SDL_BUTTON_MIDDLE) { mouse.isMiddleDown = false; }
            if (event.button.button == SDL_BUTTON_RIGHT) { mouse.isRightDown = false; }
        }
        
        if (event.type == SDL_EVENT_WINDOW_FOCUS_LOST) {
            held.fill(false);
        }
    }

    void clear() {
        pressed.fill(false);
        released.fill(false);
        mouse.delta = { 0.f, 0.f };
    }

    bool isPressed(SDL_Scancode scancode) {
        return held[scancode];
    }

    bool wasPressed(SDL_Scancode scancode) {
        return pressed[scancode];
    }

    Mouse getMouse() const {
        return mouse;
    }
};
    
}