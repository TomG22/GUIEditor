#include <iostream>
#include <stdexcept>
#include <thread>

#include "Window.h"
#include "Widget.h"

int main() {
    Window* window = new Window();


    //Widget* relWidget = window->makeWidget();
    Widget* absWidget = window->makeWidget();
    absWidget->setNotResizable();
    absWidget->setMoveable();
    absWidget->showHoverTips();
    absWidget->bgColor = {0.5f, 0.5f, 0.5f, 1.0f};
    window->postToRenderThread([=]() {
        //relWidget->createBackground();

        //relWidget->setRelPos(0.5f, 0.5f);
        //relWidget->setRelSize(0.5f, 0.5f);
        //relWidget->bgColor = {0.9f, 0.5f, 0.5f, 1.0f};

        absWidget->setAbsTransform({0.0f, 0.0f}, {300.0f, 300.0f});
        absWidget->createBackground();
        //absWidget->onKey(...);

    });


    try {
        std::thread windowThread = std::thread(&Window::startWindowLoop, window);
        windowThread.join();
    } catch (const std::runtime_error& e){
        std::cout << "Window ERROR: " << e.what() << std::endl;
        std::exit(1);
    }

    return 0;
}
