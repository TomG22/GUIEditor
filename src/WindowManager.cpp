#include <iostream>

#include "WindowManager.h"

void glfwErrorCallback(int error, const char* description) {
    fprintf(stderr, "GLFW Error (%d): %s\n", error, description);
}

WindowManager::WindowManager() {
    try {
        initGLFW();
    } catch (const std::runtime_error&) {
        std::cerr << "GLFW Initialization failed" << std::endl;
    }
}

void WindowManager::initGLFW() {
    // Set the debug callback for all GLFW errors
    glfwSetErrorCallback(glfwErrorCallback);

    // Check if GLFW initialization errors
    if (!glfwInit()) {
        throw std::runtime_error("");
    }

    // Create the GLFW window
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

Window* WindowManager::createWindow() {
    Window* window = new Window();
    windows.push_back(window);
    return window;
}

void WindowManager::startEventLoop() {
    while (!windows.empty()) {
        glfwPollEvents();

        for (auto it = windows.begin(); it != windows.end();) {
            Window* window = *it;

            if (window->shouldClose()) {
                delete window;
                it = windows.erase(it);
            } else {
                window->render();
                ++it;
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    glfwTerminate();
}
