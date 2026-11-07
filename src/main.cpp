#include "viewport.hpp"
#include "input.hpp"

int main() {
    oc::Input input;
    oc::Viewport viewport(1270, 720);
    
    viewport.init();
    viewport.poll(input);
    viewport.quit();
    
    return 0;
}