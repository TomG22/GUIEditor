#include <iostream>
#include <stdexcept>
#include <thread>

#include "Window.h"
#include "Widget.h"

int main() {
    Window* window = new Window();


    Widget* widget = window->makeWidget();
    window->postToRenderThread([=]() {
        widget->setSize({100.0f, 100.0f}, {300.0f, 300.0f});
        widget->bgColor = {0.5f, 0.5f, 0.5f, 1.0f};
        widget->createBackground();
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
