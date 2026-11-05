#pragma once

#include <SDL3/SDL.h>
#include <array>

namespace oc {

class Input {
    std::array<bool, SDL_SCANCODE_COUNT> held;
    std::array<bool, SDL_SCANCODE_COUNT> pressed;
    std::array<bool, SDL_SCANCODE_COUNT> released;
    
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
            
        } else if (event.type == SDL_EVENT_WINDOW_FOCUS_LOST) {
            held.fill(false);
        }
    }

    void clear() {
        pressed.fill(false);
        released.fill(false);
    }

    bool isPressed(SDL_Scancode scancode) {
        return held[scancode];
    }

    bool wasPressed(SDL_Scancode scancode) {
        return pressed[scancode];
    }
};
    
}