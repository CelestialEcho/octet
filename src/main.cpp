#include "viewport.hpp"
#include "input.hpp"
#include "gui.hpp"

int main() {
    oc::Gui gui;
    oc::Input input;
    oc::Viewport viewport(1270, 720, gui);
    
    viewport.init();
    viewport.poll(input);
    viewport.quit();
    
    return 0;
}