#include <iostream>
#include <stdexcept>

#include "Window.h"
#include "Renderer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

void glfwErrorCallback(int error, const char* description) {
    fprintf(stderr, "GLFW Error (%d): %s\n", error, description);
}

Window::Window() : window(nullptr) {
    try {
        initGLFW();
    } catch (const std::runtime_error&) {
        std::cerr << "GLFW Initialization failed" << std::endl;
    }
}

void Window::RegisterListener(WindowListener* listener) {
    listeners.push_back(listener);
}

void Window::addFrame(Frame* frame) {
    frames.push_back(frame);
}

void Window::initGLFW() {
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

void Window::startWindowLoop() {
    window = glfwCreateWindow(1440, 700, "GLFW Window", nullptr, nullptr);

    // Check if window creation errors
    if (window == nullptr) {
        throw std::runtime_error("GLFW window creation failed");
        glfwTerminate();
    }

    // Set the current context to our window
    glfwMakeContextCurrent(window);

    // Set the window attributes
    glfwSwapInterval(1);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    // Save the reference of the current gui instance
    glfwSetWindowUserPointer(window, this);

    // Set the callbacks for the window
    glfwSetKeyCallback(window, Window::keyCallback);
    glfwSetErrorCallback(glfwErrorCallback);

    // Check if GLAD initialization errors
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        throw std::runtime_error("GLAD initialization failed");
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    Shader* shader2D = new Shader("../res/shaders/2DVertexColor.shader");
    //shader2D->Bind();
    //shader2D->SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
    //shader2D->Unbind();

    Renderer renderer;
    renderer.clearColor(0.3f, 0.9f, 0.9f, 1.0f);

    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(window)) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        renderer.Clear();

        // Fetch from the command queue before rendering
        std::lock_guard<std::mutex> lock(cmdQueueMut);
        while (!cmdQueue.empty()) {
            cmdQueue.front()();
            cmdQueue.pop();
        }

        float time = static_cast<float>(glfwGetTime());
        shader2D->Bind();
        shader2D->SetUniform1f("u_Time", time);

        for (Frame* frame : frames) {
            renderer.Draw(frame->background->va, frame->background->ib, *shader2D);
        }

        GLCall(glfwSwapBuffers(window));
        GLCall(glfwPollEvents());
    }

    delete shader2D;

    glfwDestroyWindow(window);
    glfwTerminate();
}

bool Window::isKeyDown(int keyCode) {
    if (!window)
        return false;

    return glfwGetKey(window, keyCode) != 0;
}

void Window::handleKey(int key, int scancode, int action, int mods) {
    for (auto* listener : listeners) {
        listener->OnKey(key, scancode, action, mods);
    }
}

void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // Get a reference to the gui for our key callback
    Window* gui = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (gui) {
        // Call the non-static keyCallback member function
        gui->handleKey(key, scancode, action, mods);
    }
}

void Window::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void Window::postToRenderThread(std::function<void()> command) {
    std::lock_guard<std::mutex> lock(cmdQueueMut);
    cmdQueue.push(std::move(command));
}
