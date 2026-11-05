#include "viewport.hpp"

int main() {
    oc::Viewport viewport(1270, 720);
    
    viewport.init();
    viewport.poll();
    viewport.quit();
    
    return 0;
}