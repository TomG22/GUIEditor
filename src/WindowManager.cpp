#include <cassert>
#include <iostream>

#include "WindowManager.h"

static WindowManager* winManager = nullptr;

void glfwErrorCallback(int error, const char* description) {
    fprintf(stderr, "GLFW Error (%d): %s\n", error, description);
}

void monitorCallback(GLFWmonitor* monitor, int event) {
    if (winManager) {
        winManager->handleMonitorEvent(monitor, event);
    }
}

WindowManager::WindowManager() {
    winManager = this;
    initGLFW();
}

void WindowManager::initGLFW() {
    // Set the debug callback for all GLFW errors
    glfwSetErrorCallback(glfwErrorCallback);

    // Check if GLFW initialization errors
    if (!glfwInit()) {
        throw std::runtime_error("WindowManager ERROR: GLFW Initialization failed");
    }

    // Create the GLFW window
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwSetMonitorCallback(monitorCallback);


    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    assert(monitor && "WindowManager ERROR: Failed to get primary monitor");

    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    assert(mode && "WindowManager ERROR: Failed to get video mode");

    screenWidth = mode->width;
    screenHeight = mode->height;
}

Window* WindowManager::createWindow(int width, int height) {
    assert(width >= 0 && height >= 0);

    Window* window = new Window(static_cast<float>(width),
                                static_cast<float>(height));
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

void WindowManager::handleMonitorEvent(GLFWmonitor* monitor, int event) {
    if (event == GLFW_CONNECTED) {
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);

        if (mode) {
            screenWidth = mode->width;
            screenHeight = mode->height;
        }
    }
}
