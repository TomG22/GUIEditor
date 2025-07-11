#include <iostream>
#include <stdexcept>

#include "GLDebug.h"
#include "Window.h"
#include "Renderer.h"
#include "GLFWTypeConv.h"

Window::Window()
    : window(nullptr),
      shader2D(nullptr),
      hoverState(RectPos::None),
      nextHoverState(RectPos::None),
      focusedWidget(nullptr),
      hoveredWidget(nullptr),
      hitWidget(nullptr),
      width(1440),
      height(700),
      renderer(nullptr)
{
    initGLFWWindow();
}

Window::~Window() {
    glfwDestroyWindow(window);
}

void Window::RegisterListener(GuiListener* listener) {
    listeners.push_back(listener);
}

Widget* Window::makeWidget() {
    Widget* widget = new Widget(this);
    widgets.push_back(widget);
    widgetIndices[widget] = widgets.size() - 1;
    return widget;
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

void Window::createMeshForWidget(Widget* widget) {
    assert(widget && widget->bgGeometry && !meshMap.contains(widget));

    // Create vertices
    Vertex2D vertices[4] = {
        {widget->bgGeometry->topLeft, widget->bgColor, {0.0, 0.0}},
        {widget->bgGeometry->topRight, widget->bgColor, {0.0, 1.0}},
        {widget->bgGeometry->bottomRight, widget->bgColor, {1.0, 0.0}},
        {widget->bgGeometry->bottomLeft, widget->bgColor, {1.0, 0.0}}
    };

    unsigned int indices[6] = {0,1,2, 2,3,0};

    try {
        VertexArray* va = new VertexArray();
        VertexBuffer* vb = new VertexBuffer(vertices, sizeof(Vertex2D)*4);

        VertexBufferLayout* layout = new VertexBufferLayout();
        layout->Push<Vertex2D>(1);

        va->Bind();
        vb->Bind();
        va->AddBuffer(*vb, *layout);

        IndexBuffer* ib = new IndexBuffer(indices, 6);

        Mesh* mesh = new Mesh(va, vb, ib);

        meshMap[widget] = mesh;

    } catch (const std::runtime_error& e) {
        std::cerr << "Mesh creation error: " << e.what() << std::endl;
        std::exit(1);
    }
}

void Window::updateMeshForWidget(Widget* widget) {
    assert(widget && widget->bgGeometry && meshMap.contains(widget));

    Mesh* mesh = meshMap[widget];

    Vertex2D vertices[4] = {
        {widget->bgGeometry->topLeft, widget->bgColor, {0.0, 1.0}},
        {widget->bgGeometry->topRight, widget->bgColor, {1.0, 1.0}},
        {widget->bgGeometry->bottomRight, widget->bgColor, {1.0, 0.0}},
        {widget->bgGeometry->bottomLeft, widget->bgColor, {0.0, 0.0}}
    };

    mesh->UpdateVertices(vertices, sizeof(Vertex2D)*4, 0);
}

void Window::updateCursor(RectPos hoverState) {
    switch (hoverState) {
        case RectPos::Inside:
            useResizeAllCursor();
            break;
        case RectPos::TopLeft:
            useResizeNWSECursor();
            break;
        case RectPos::TopRight:
            useResizeNESWCursor();
            break;
        case RectPos::BottomRight:
            useResizeNWSECursor();
            break;
        case RectPos::BottomLeft:
            useResizeNESWCursor();
            break;
        case RectPos::Top:
            useVResizeCursor();
            break;
        case RectPos::Right:
            useHResizeCursor();
            break;
        case RectPos::Bottom:
            useVResizeCursor();
            break;
        case RectPos::Left:
            useHResizeCursor();
            break;
        default:
            useArrowCursor();
    }
}

void Window::initGLFWWindow() {
    window = glfwCreateWindow(width, height, "GLFW Window", nullptr, nullptr);

    // Check if window creation errors
    if (window == nullptr) {
        glfwTerminate();
        throw std::runtime_error("GLFW window creation failed");
    }

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
    hResizeCursor = glfwCreateStandardCursor(GLFW_HRESIZE_CURSOR);
    vResizeCursor = glfwCreateStandardCursor(GLFW_VRESIZE_CURSOR);
    resizeNESWCursor = glfwCreateStandardCursor(GLFW_RESIZE_NESW_CURSOR);
    resizeNWSECursor = glfwCreateStandardCursor(GLFW_RESIZE_NWSE_CURSOR);
    resizeAllCursor = glfwCreateStandardCursor(GLFW_RESIZE_ALL_CURSOR);

    useArrowCursor();

    proj = glm::ortho(0.0f, width * 1.0f, height * 1.0f, 0.0f, -1.0f, 1.0f);

    shader2D = new Shader("../res/shaders/2DVertexColor.shader");
    shader2D->Bind();
    shader2D->SetUniformMat4f("u_Proj", proj);
    shader2D->Unbind();

    renderer = new Renderer();
    renderer->clearColor(0.3f, 0.9f, 0.9f, 1.0f);
}

bool Window::shouldClose() {
    return glfwWindowShouldClose(window);
}

void Window::render() {
    glfwMakeContextCurrent(window);

    renderer->Clear();

    for (Widget* widget : widgets) {
        if (meshMap[widget]) {
            shader2D->Bind();
            shader2D->SetUniform2f("u_TopLeftPos", widget->bgGeometry->topLeft.x, widget->bgGeometry->topLeft.y);
            shader2D->SetUniform2f("u_Size", widget->bgGeometry->getAbsWidth(), widget->bgGeometry->getAbsHeight());
            shader2D->SetUniform1f("u_Radius", widget->bgGeometry->getAbsRadius());
            renderer->Draw(*meshMap[widget], *shader2D);
        }
    }

    if (hoverState != nextHoverState) {
        updateCursor(nextHoverState);
        hoverState = nextHoverState;
    }

    GLCall(glfwSwapBuffers(window));
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

void Window::handleKey(int key, int action, int mods) {
    for (auto* listener : listeners) {
        if (action == GLFW_PRESS && listener->regKeyDown) {
            listener->onKeyDown(convGLFWKey(key), convGLFWMods(mods));
        } else if (action == GLFW_RELEASE && listener->regKeyUp) {
            listener->onKeyUp(convGLFWKey(key), convGLFWMods(mods));
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

    if (focusedWidget && focusedWidget->regMouseHover &&
        focusedWidget->transformState != TransformState::Idle) {
        focusedWidget->onMouseHover(x, y);

        hoveredWidget = focusedWidget;
    }
    else {
        if (hovered && hovered->regMouseHover && hovered == prevHovered) {
            hovered->onMouseHover(x, y);
        }

        if (prevHovered && prevHovered->regMouseLeave && prevHovered != hovered) {
            prevHovered->onMouseLeave();
        }

        if (hovered && hovered->regMouseEnter && hovered != prevHovered) {
            hovered->onMouseEnter();
        }

        if (hovered) {
            nextHoverState = hovered->hoverState;
        } else {
            nextHoverState = RectPos::None;
        }

        hoveredWidget = hovered;
    }

    for (GuiListener* listener : listeners) {
        if (listener->regMouseMove) {
            listener->onMouseMove(x, y);
        }
    }
}

void Window::cursorPosCallback(GLFWwindow* window,
                               double x, double y) {
    Window* gui = static_cast<Window*>(glfwGetWindowUserPointer(window));
    gui->handleMouseMove(static_cast<float>(x), static_cast<float>(y));
}

void Window::handleMouseButton(int action, MouseButtonType type) {
    Widget* prevHitWidget = hitWidget;

    double xDouble, yDouble;
    glfwGetCursorPos(window, &xDouble, &yDouble);
    float x = static_cast<float>(xDouble);
    float y = static_cast<float>(yDouble);
    Widget* hit = Widget::hitTest(widgets, x, y);

    if (action == GLFW_PRESS) {
        if (hit && hit->regMouseDown) {
            hit->onMouseDown(x, y, type);
            hitWidget = hit;

            focusedWidget = hit;
            if (!focusedWidget->lockZIndex) {
                moveToFront(hitWidget);
            }

        }

        for (GuiListener* listener : listeners) {
            if (listener->regMouseDown) {
                listener->onMouseDown(x, y, type);
            }
        }
    } else if (action == GLFW_RELEASE) {
        if (prevHitWidget && prevHitWidget->regMouseUp) {
            prevHitWidget->onMouseUp(x, y, type);
        }

        if (hit != hoveredWidget) {
            if (hoveredWidget) {
                hoveredWidget->onMouseLeave();
            }
            if (hit) {
                hit->onMouseEnter();
            }
        }

        for (GuiListener* listener : listeners) {
            if (listener->regMouseUp) {
                listener->onMouseUp(x, y, type);
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

void Window::handleResize(int width, int height) {
    this->width = width;
    this->height = height;

    proj = glm::ortho(0.0f, width * 1.0f, height * 1.0f, 0.0f, -1.0f, 1.0f);

    shader2D->Bind();
    shader2D->SetUniformMat4f("u_Proj", proj);
    shader2D->Unbind();

    GLCall(glViewport(0, 0, width, height));

    for (GuiListener* listener : listeners) {
        if (listener->regResize) {
            listener->onResize(width, height);
        }
    }

}

void Window::framebufferSizeCallback(GLFWwindow* window,
                                     int width, int height) {
    Window* gui = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (gui) gui->handleResize(width, height);
}

void Window::handleReposition(int x, int y) {
    for (GuiListener* listener : listeners) {
        if (listener->regReposition) {
            listener->onReposition(x, y);
        }
    }
}

void Window::windowPosCallback(GLFWwindow* window,
                               int x, int y) {
    Window* gui = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (gui) gui->handleReposition(x, y);
}
