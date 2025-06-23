#include <iostream>
#include <stdexcept>

#include "GLDebug.h"
#include "Window.h"
#include "Renderer.h"

void glfwErrorCallback(int error, const char* description) {
    fprintf(stderr, "GLFW Error (%d): %s\n", error, description);
}

Window::Window()
    : window(nullptr),
      shader2D(nullptr),
      width(1440),
      height(700),
      renderer() {
    try {
        initGLFW();
    } catch (const std::runtime_error&) {
        std::cerr << "GLFW Initialization failed" << std::endl;
    }
}

void Window::RegisterListener(GuiListener* listener) {
    listeners.push_back(listener);
}

Widget* Window::makeWidget() {
    Widget* widget = new Widget();
    widgets.push_back(widget);
    listeners.push_back(widget);
    return widget;
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

void Window::updateCursor(Widget* widget) {
    if (widget->hoverState == HoverState::Inside && widget->canMove) {
        useResizeAllCursor();
    }
    else if (widget->hoverState == HoverState::TopLeft &&
             widget->canResizeTop && widget->canResizeLeft) {
        useResizeNWSECursor();
    }
    else if (widget->hoverState == HoverState::TopRight &&
             widget->canResizeTop && widget->canResizeRight) {
        useResizeNESWCursor();
    }
    else if (widget->hoverState == HoverState::BottomRight &&
             widget->canResizeBottom && widget->canResizeRight) {
        useResizeNWSECursor();
    }
    else if (widget->hoverState == HoverState::BottomLeft &&
             widget->canResizeBottom && widget->canResizeLeft) {
        useResizeNESWCursor();
    }
    else if (widget->hoverState == HoverState::Top &&
             widget->canResizeTop) {
        useVResizeCursor();
    }
    else if (widget->hoverState == HoverState::Right &&
             widget->canResizeRight) {
        useHResizeCursor();
    }
    else if (widget->hoverState == HoverState::Bottom &&
             widget->canResizeBottom) {
        useVResizeCursor();
    }
    else if (widget->hoverState == HoverState::Left &&
             widget->canResizeLeft) {
        useHResizeCursor();
    }
    else {
        useArrowCursor();
    }
}


void Window::startWindowLoop() {
    window = glfwCreateWindow(width, height, "GLFW Window", nullptr, nullptr);

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
    glfwSetCursorPosCallback(window, Window::cursorPosCallback);
    glfwSetMouseButtonCallback(window, Window::mouseButtonCallback);

    // Check if GLAD initialization errors
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        throw std::runtime_error("GLAD initialization failed");
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    arrowCursor = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
    hResizeCursor = glfwCreateStandardCursor(GLFW_HRESIZE_CURSOR);
    vResizeCursor = glfwCreateStandardCursor(GLFW_VRESIZE_CURSOR);
    resizeNESWCursor = glfwCreateStandardCursor(GLFW_RESIZE_NESW_CURSOR);
    resizeNWSECursor = glfwCreateStandardCursor(GLFW_RESIZE_NWSE_CURSOR);
    resizeAllCursor = glfwCreateStandardCursor(GLFW_RESIZE_ALL_CURSOR);

    glfwSetCursor(window, arrowCursor);

    shader2D = new Shader("../res/shaders/2DVertexColor.shader");

    proj = glm::ortho(0.0f, width * 1.0f, 0.0f, height * 1.0f, -1.0f, 1.0f);

    shader2D->Bind();
    shader2D->SetUniformMat4f("u_Proj", proj);
    shader2D->Unbind();

    renderer = new Renderer();
    renderer->clearColor(0.3f, 0.9f, 0.9f, 1.0f);

    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           !glfwWindowShouldClose(window)) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        renderer->Clear();

        // Fetch from the command queue before rendering
        std::lock_guard<std::mutex> lock(cmdQueueMut);
        while (!cmdQueue.empty()) {
            cmdQueue.front()();
            cmdQueue.pop();
        }

        for (Widget* widget : widgets) {
            if (widget->bgMesh != nullptr) {
                renderer->Draw(*(widget->bgMesh), *shader2D);
            }

            if (this->hoverState != widget->hoverState) {
                updateCursor(widget);
            }
        }

        GLCall(glfwSwapBuffers(window));
        GLCall(glfwPollEvents());
    }

    delete shader2D;

    glfwDestroyWindow(window);
    glfwTerminate();
}

void Window::useArrowCursor() {
    glfwSetCursor(window, arrowCursor);
}

void Window::useHResizeCursor() {
    glfwSetCursor(window, hResizeCursor);
}

void Window::useVResizeCursor() {
    glfwSetCursor(window, vResizeCursor);
}

void Window::useResizeNESWCursor() {
    glfwSetCursor(window, resizeNESWCursor);
}

void Window::useResizeNWSECursor() {
    glfwSetCursor(window, resizeNWSECursor);
}

void Window::useResizeAllCursor() {
    glfwSetCursor(window, resizeAllCursor);
}

bool Window::isKeyDown(int keyCode) {
    if (!window)
        return false;

    return glfwGetKey(window, keyCode) != 0;
}

void Window::handleKey(int key, int scancode, int action, int mods) {
    for (auto* listener : listeners) {
        listener->onKey(key, scancode, action, mods);
    }
}

void Window::keyCallback(GLFWwindow* window,
                         int key, int scancode, int action, int mods) {
    Window* gui = static_cast<Window*>(glfwGetWindowUserPointer(window));
    gui->handleKey(key, scancode, action, mods);
}

void Window::handleMouseMove(float x, float y) {
    for (GuiListener* listener : listeners) {
        listener->onMouseMove(x, height - y);
    }
}

void Window::cursorPosCallback(GLFWwindow* window,
                               double x, double y) {
    Window* gui = static_cast<Window*>(glfwGetWindowUserPointer(window));
    gui->handleMouseMove(static_cast<float>(x), static_cast<float>(y));
}

void Window::handleMouseButton(int button, int action, int mods) {
    double xDouble, yDouble;
    glfwGetCursorPos(window, &xDouble, &yDouble);
    float x = static_cast<float>(xDouble);
    float y = height - static_cast<float>(yDouble);

    if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT) {
        for (GuiListener* listener : listeners) {
            listener->onMouseDownLeft(x, y, mods);
        }
    }

    if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_RIGHT) {
        for (GuiListener* listener : listeners) {
            listener->onMouseDownRight(x, y, mods);
        }
    }

    if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_MIDDLE) {
        for (GuiListener* listener : listeners) {
            listener->onMouseDownMiddle(x, y, mods);
        }
    }

    if (action == GLFW_RELEASE && button == GLFW_MOUSE_BUTTON_LEFT) {
        for (GuiListener* listener : listeners) {
            listener->onMouseUpLeft(x, y, mods);
        }
    }

    if (action == GLFW_RELEASE && button == GLFW_MOUSE_BUTTON_RIGHT) {
        for (GuiListener* listener : listeners) {
            listener->onMouseUpRight(x, y, mods);
        }
    }

    if (action == GLFW_RELEASE && button == GLFW_MOUSE_BUTTON_MIDDLE) {
        for (GuiListener* listener : listeners) {
            listener->onMouseUpMiddle(x, y, mods);
        }
    }
}

void Window::mouseButtonCallback(GLFWwindow* window,
                                 int button, int action, int mods) {
    Window* gui = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (gui) gui->handleMouseButton(button, action, mods);
}

void Window::handleResize(int width, int height) {
    this->width = width;
    this->height = height;
    proj = glm::ortho(0.0f, width * 1.0f, 0.0f, height * 1.0f, -1.0f, 1.0f);

    shader2D->Bind();
    shader2D->SetUniformMat4f("u_Proj", proj);
    shader2D->Unbind();

    GLCall(glViewport(0, 0, width, height));
}

void Window::framebufferSizeCallback(GLFWwindow* window,
                                     int width, int height) {
    Window* gui = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (gui) gui->handleResize(width, height);

}

void Window::postToRenderThread(std::function<void()> command) {
    std::lock_guard<std::mutex> lock(cmdQueueMut);
    cmdQueue.push(std::move(command));
}
