#include "Window.h"

#include <thread>

int main() {
    Window window = Window();

    std::thread windowThread = std::thread(&Window::startWindowLoop, &window);
    windowThread.detach();

    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    return 0;
}
