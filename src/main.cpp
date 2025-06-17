#include <iostream>
#include <stdexcept>
#include <thread>

#include "Window.h"
#include "Frame.h"

int main() {
    Window* window = new Window();

    window->postToRenderThread([=]() {
        Frame* frame = new Frame();
        window->addFrame(frame);
    });

    try {
        std::thread windowThread = std::thread(&Window::startWindowLoop, window);
        windowThread.detach();
    } catch (const std::runtime_error& e){
        std::cout << "Window ERROR: " << e.what() << std::endl;
    }

    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    return 0;
}
