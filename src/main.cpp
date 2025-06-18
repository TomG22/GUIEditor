#include <iostream>
#include <stdexcept>
#include <thread>

#include "Window.h"
#include "Frame.h"

int main() {
    Window* window = new Window();

    window->postToRenderThread([=]() {
        Frame frame = Frame();
        frame.bottomLeft = {100.0f, 100.0f};
        frame.topRight = {300.0f, 300.0f};
        frame.bgColor = {0.5f, 0.5f, 0.5f, 1.0f};
        frame.createBackground();

        window->addFrame(frame);
    });

    try {
        std::thread windowThread = std::thread(&Window::startWindowLoop, window);
        windowThread.join();
    } catch (const std::runtime_error& e){
        std::cout << "Window ERROR: " << e.what() << std::endl;
    }

    return 0;
}
