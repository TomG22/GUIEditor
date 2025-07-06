#include <iostream>
#include <stdexcept>
#include <thread>

#include "Window.h"
#include "Widget.h"

int main() {
    Window* window = new Window();

    try {
        std::thread windowThread = std::thread(&Window::startWindowLoop, window);

        Widget* absWidget = window->makeWidget();
        absWidget->bgColor = {0.5f, 0.5f, 0.5f, 1.0f};
        absWidget->requestBGMeshCreation();
        absWidget->setAbsTransform({0.0f, 0.0f}, {300.0f, 300.0f});
        absWidget->setRelRadius(0.5f);
        absWidget->lockZIndex = false;

        Widget* relWidget = window->makeWidget();
        relWidget->bgColor = {0.5f, 0.1f, 0.1f, 1.0f};
        relWidget->requestBGMeshCreation();
        relWidget->setRelPos(0.5f, 0.25f);
        relWidget->setRelSize(0.5f, 0.5f);
        relWidget->setAbsRadius(20.0f);
        relWidget->lockZIndex = false;


        windowThread.join();
    } catch (const std::runtime_error& e){
        std::cout << "Window ERROR: " << e.what() << std::endl;
        std::exit(1);
    }

    return 0;
}
