#include "app.hpp"

int main() {

    oc::App* app = new oc::App(1280, 720, "Octet preview");
    app->run();
    delete(app);
    
    return 0;
}