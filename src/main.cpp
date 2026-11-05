#include "viewport.hpp"
#include "input.hpp"

int main() {
    oc::Viewport viewport(1270, 720);
    oc::Input input;
    
    viewport.init();
    viewport.poll(input);
    viewport.quit();
    
    return 0;
}