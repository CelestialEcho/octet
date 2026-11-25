#pragma once

#include "gui.hpp"
#include "input.hpp"
#include "viewport.hpp"

namespace oc {
    
class App {
    Gui gui;
    Input input;
    Viewport viewport;
    
public:
    App(float sWidth, float sHeight, const char* winTitle) :  viewport(sWidth, sHeight) {
        if (viewport.init()) {
            gui.init(viewport.getWindow(), viewport.getGlContext());
        } 
    }

    void run() {
        viewport.run(&gui, &input);
    }

    ~App() {
        gui.quit();
        viewport.quit();
    }
};
    
}