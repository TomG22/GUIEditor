#include <iostream>
#include <stack>
#include <stdexcept>

#include "GLDebug.h"
#include "Window.h"
#include "Renderer.h"
#include "GLFWTypeConv.h"

Window::Window(float width, float height)
    : window(nullptr),
      cursorState(TransformType::IDLE),
      nextCursorState(TransformType::IDLE),
      focusedWidget(nullptr),
      hoveredWidget(nullptr),
      hitWidget(nullptr),
      bgColor(0.3f, 0.9f, 0.9f, 1.0f)
{
    renderer = new Renderer();

    layout.width.setAbsValue(width);
    layout.height.setAbsValue(height);

    initGLFWWindow();
}

Window::~Window() {
    glfwDestroyWindow(window);
}

void Window::setPos(float x, float y) {
    if (layout.xPos.isBound()) {
        layout.xPos.setScale(x);
    } else {
        layout.xPos.setAbsValue(x);
    }

    if (layout.yPos.isBound()) {
        layout.yPos.setScale(y);
    } else {
        layout.yPos.setAbsValue(y);
    }

    glfwSetWindowPos(window, static_cast<int>(layout.xPos.getAbsValue()),
                             static_cast<int>(layout.yPos.getAbsValue()));
}

void Window::setSize(float width, float height) {
    if (layout.width.isBound()) {
        layout.width.setScale(width);
    } else {
        layout.width.setAbsValue(width);
    }

    if (layout.height.isBound()) {
        layout.height.setScale(height);
    } else {
        layout.height.setAbsValue(height);
    }

    glfwSetWindowSize(window, static_cast<int>(layout.width.getAbsValue()),
                              static_cast<int>(layout.height.getAbsValue()));
}

Widget* Window::makeWidget() {
    Widget* widget = new Widget(layout);

    widgets.push_back(widget);
    widgetIndices[widget] = widgets.size() - 1;
    return widget;
}

void Window::addWidget(Widget* widget) {
    widgets.push_back(widget);
    widgetIndices[widget] = widgets.size() - 1;
}

void Window::removeWidget(Widget* widget) {
    auto it = widgetIndices.find(widget);
    if (it == widgetIndices.end()) return;

    size_t index = it->second;
    widgetIndices.erase(it);

    if (index != widgets.size() - 1) {
        std::swap(widgets[index], widgets.back());

        widgetIndices[widgets[index]] = index;
    }

    widgets.pop_back();
}

void Window::moveToFront(Widget* widget) {
    auto it = widgetIndices.find(widget);
    if (it == widgetIndices.end()) return;

    size_t index = it->second;

    if (index == widgets.size() - 1) return;

    widgets.erase(widgets.begin() + index);
    widgets.push_back(widget);

    for (size_t i = index; i < widgets.size(); ++i) {
        widgetIndices[widgets[i]] = i;
    }
}

void Window::moveToBack(Widget* widget) {
    auto it = widgetIndices.find(widget);
    if (it == widgetIndices.end()) return;

    size_t index = it->second;

    if (index == 0) return;

    widgets.erase(widgets.begin() + index);
    widgets.insert(widgets.begin(), widget);

    for (size_t i = 0; i < widgets.size(); ++i) {
        widgetIndices[widgets[i]] = i;
    }
}

void Window::moveForward(Widget* widget) {
    auto it = widgetIndices.find(widget);
    if (it == widgetIndices.end()) return;

    size_t index = it->second;

    if (index == widgets.size() - 1) return;

    std::swap(widgets[index], widgets[index + 1]);
    widgetIndices[widgets[index]] = index;
    widgetIndices[widgets[index + 1]] = index + 1;
}

void Window::moveBackward(Widget* widget) {
    auto it = widgetIndices.find(widget);
    if (it == widgetIndices.end()) return;

    size_t index = it->second;

    if (index == 0) return;

    std::swap(widgets[index], widgets[index - 1]);
    widgetIndices[widgets[index]] = index;
    widgetIndices[widgets[index - 1]] = index - 1;
}

void Window::initGLFWWindow() {
    glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);

    window = glfwCreateWindow(static_cast<int>(layout.width.getAbsValue()),
                              static_cast<int>(layout.height.getAbsValue()),
                              "GLFW Window", nullptr, nullptr);

    // Check if window creation errors
    if (window == nullptr) {
        glfwTerminate();
        throw std::runtime_error("GLFW window creation failed");
    }

    // Initialize the window's position
    glfwSetWindowPos(window, static_cast<int>(layout.xPos.getAbsValue()),
                             static_cast<int>(layout.yPos.getAbsValue()));

    // Set the current context to our window
    glfwMakeContextCurrent(window);

    // Set the window attributes
    glfwSwapInterval(1);

    // Save the reference of the current gui instance
    glfwSetWindowUserPointer(window, this);

    // Set the callbacks for the window
    glfwSetKeyCallback(window, keyCallback);
    glfwSetCursorPosCallback(window, cursorPosCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetWindowPosCallback(window, windowPosCallback);

    // Check if GLAD initialization errors
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        throw std::runtime_error("GLAD initialization failed");
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    arrowCursor = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
    resizeHCursor = glfwCreateStandardCursor(GLFW_HRESIZE_CURSOR);
    resizeVCursor = glfwCreateStandardCursor(GLFW_VRESIZE_CURSOR);
    resizeNESWCursor = glfwCreateStandardCursor(GLFW_RESIZE_NESW_CURSOR);
    resizeNWSECursor = glfwCreateStandardCursor(GLFW_RESIZE_NWSE_CURSOR);
    resizeAllCursor = glfwCreateStandardCursor(GLFW_RESIZE_ALL_CURSOR);

    renderer->clearColor(bgColor.r, bgColor.g, bgColor.b, bgColor.a);
}

void Window::destroyGLFWWindow() {
    assert(window &&
           "Window ERROR: Tried to destroy an uninitialized window");

    glfwDestroyWindow(window);
    window = nullptr;

    if (arrowCursor) glfwDestroyCursor(arrowCursor);
    if (resizeHCursor) glfwDestroyCursor(resizeHCursor);
    if (resizeVCursor) glfwDestroyCursor(resizeVCursor);
    if (resizeNESWCursor) glfwDestroyCursor(resizeNESWCursor);
    if (resizeNWSECursor) glfwDestroyCursor(resizeNWSECursor);
    if (resizeAllCursor) glfwDestroyCursor(resizeAllCursor);

    arrowCursor = resizeHCursor = resizeVCursor =
    resizeNESWCursor = resizeNWSECursor = resizeAllCursor = nullptr;
}

void Window::setBGColor(glm::vec4 color) {
    bgColor = color;

    if (window) {
        renderer->clearColor(bgColor.r, bgColor.g, bgColor.b, bgColor.a);
    }
}

void Window::render() {
    glfwMakeContextCurrent(window);

    renderer->Clear();


    std::stack<Widget*> stack;

    for (auto it = widgets.rbegin(); it != widgets.rend(); ++it) {
        stack.push(*it);
    }

    while (!stack.empty()) {
        Widget* current = stack.top();
        stack.pop();

        renderer->Draw(*current->bgMesh, *current->bgShader);

        for (auto it = current->subWidgets.rbegin(); it != current->subWidgets.rend(); ++it) {
            stack.push(*it);
        }
    }

    if (cursorState != nextCursorState) {
        updateCursor(nextCursorState);
        cursorState = nextCursorState;
    }

    GLCall(glfwSwapBuffers(window));
}

bool Window::shouldClose() {
    return glfwWindowShouldClose(window);
}

void Window::updateCursor(TransformType cursorState) {
    switch (cursorState) {
        case TransformType::IDLE:
            glfwSetCursor(window, arrowCursor);
            break;
        case TransformType::MOVE:
            glfwSetCursor(window, resizeAllCursor);
            break;
        case TransformType::RESIZE_TOP:
        case TransformType::RESIZE_BOTTOM:
            glfwSetCursor(window, resizeVCursor);
            break;
        case TransformType::RESIZE_LEFT:
        case TransformType::RESIZE_RIGHT:
            glfwSetCursor(window, resizeHCursor);
            break;
        case TransformType::RESIZE_TOP_LEFT:
        case TransformType::RESIZE_BOTTOM_RIGHT:
            glfwSetCursor(window, resizeNWSECursor);
            break;
        case TransformType::RESIZE_TOP_RIGHT:
        case TransformType::RESIZE_BOTTOM_LEFT:
            glfwSetCursor(window, resizeNESWCursor);
            break;
        default:
            assert(false && "Window ERROR: Unsupported cursorState in updateCursor");
            break;
    }
}

void Window::registerListener(GuiListener* listener) {
    listeners.push_back(listener);
}

void Window::handleKey(int key, int action, int mods) {
    for (auto* listener : listeners) {
        if (action == GLFW_PRESS && listener->regKeyDown) {
            listener->handleKeyDown(convGLFWKey(key), convGLFWMods(mods));
        } else if (action == GLFW_RELEASE && listener->regKeyUp) {
            listener->handleKeyUp(convGLFWKey(key), convGLFWMods(mods));
        }
    }
}

void Window::keyCallback(GLFWwindow* window,
                         int key, int scancode, int action, int mods) {
    Window* gui = static_cast<Window*>(glfwGetWindowUserPointer(window));
    gui->handleKey(key, action, mods);
}

void Window::handleMouseMove(float x, float y) {
    Widget* prevHovered = hoveredWidget;
    Widget* hovered = Widget::hitTest(widgets, x, y);

    if (focusedWidget && focusedWidget->transformState != TransformType::IDLE) {
        focusedWidget->handleMouseHover(x, y);

        hoveredWidget = focusedWidget;
    }
    else {
        if (hovered && hovered == prevHovered) {
            hovered->handleMouseHover(x, y);
        }

        if (prevHovered && prevHovered != hovered) {
            prevHovered->handleMouseLeave();
        }

        if (hovered && hovered != prevHovered) {
            hovered->handleMouseEnter();
        }

        if (hovered) {
            nextCursorState = hovered->hoverState;
        } else {
            nextCursorState = TransformType::IDLE;
        }

        hoveredWidget = hovered;
    }

    for (GuiListener* listener : listeners) {
        if (listener->regMouseMove) {
            listener->handleMouseMove(x, y);
        }
    }
}

void Window::cursorPosCallback(GLFWwindow* window,
                               double x, double y) {
    Window* gui = static_cast<Window*>(glfwGetWindowUserPointer(window));
    gui->handleMouseMove(static_cast<float>(x), static_cast<float>(y));
}

void Window::handleMouseButton(int action, MouseButtonType type) {
    double xDouble, yDouble;

    glfwGetCursorPos(window, &xDouble, &yDouble);

    float x = static_cast<float>(xDouble);
    float y = static_cast<float>(yDouble);

    Widget* prevHitWidget = hitWidget;
    Widget* hit = Widget::hitTest(widgets, x, y);

    if (action == GLFW_PRESS) {
        if (hit) {
            hit->handleMouseDown(x, y, type);
            hitWidget = hit;

            focusedWidget = hit;
            if (!focusedWidget->lockZIndex) {
                moveToFront(hitWidget);
            }
        }

        for (GuiListener* listener : listeners) {
            if (listener->regMouseDown) {
                listener->handleMouseDown(x, y, type);
            }
        }
    } else if (action == GLFW_RELEASE) {
        if (prevHitWidget) {
            prevHitWidget->handleMouseUp(x, y, type);
        }

        if (hit != hoveredWidget) {
            if (hoveredWidget) {
                hoveredWidget->handleMouseLeave();
            }
            if (hit) {
                hit->handleMouseEnter();
            }
        }

        for (GuiListener* listener : listeners) {
            if (listener->regMouseUp) {
                listener->handleMouseUp(x, y, type);
            }
        }
    }
}

void Window::mouseButtonCallback(GLFWwindow* window,
                                 int button, int action, int mods) {
    Window* gui = static_cast<Window*>(glfwGetWindowUserPointer(window));

    MouseButtonType type = convGLFWMouseType(button);

    if (gui) gui->handleMouseButton(action, type);
}

void Window::handleReposition(float x, float y) {
    layout.xPos.forceAbsValue(x);
    layout.yPos.forceAbsValue(y);
}

void Window::windowPosCallback(GLFWwindow* window,
                               int x, int y) {
    Window* gui = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (gui) gui->handleReposition(static_cast<float>(x), static_cast<float>(y));
}

void Window::handleResize(float width, float height) {
    layout.width.forceAbsValue(width);
    layout.height.forceAbsValue(height);

    GLCall(glViewport(0, 0, static_cast<int>(width), static_cast<int>(height)));
}

void Window::framebufferSizeCallback(GLFWwindow* window,
                                     int width, int height) {
    Window* gui = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (gui) gui->handleResize(static_cast<float>(width), static_cast<float>(height));
}
