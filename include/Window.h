#pragma once

#include <glm/glm.hpp>
#include <unordered_map>
#include <vector>

#include <functional>

#include "GuiTypes.h"
#include "Layout.h"
#include "GuiListener.h"
#include "Renderer.h"
#include "Widget.h"

class Window {
public:
    GLFWwindow* window = nullptr;
    GLFWcursor* arrowCursor = nullptr, *resizeAllCursor = nullptr;
    GLFWcursor* resizeHCursor = nullptr, *resizeVCursor = nullptr;
    GLFWcursor* resizeNESWCursor = nullptr, *resizeNWSECursor = nullptr;

    TransformType cursorState = TransformType::IDLE;
    TransformType nextCursorState = TransformType::IDLE;

    Widget* focusedWidget = nullptr;
    Widget* hitWidget = nullptr;
    Widget* hoveredWidget = nullptr;

    Renderer* renderer = nullptr;

    Layout layout;

    glm::vec4 bgColor;

    std::vector<GuiListener*> listeners;

    std::vector<Widget*> widgets;
    std::unordered_map<Widget*, size_t> widgetIndices;

    Window(float width, float height);
    ~Window();

    void markWidgetsDirty();

    void setXPos(float x);
    void setYPos(float y);
    void setPos(float x, float y);
    void setWidth(float w);
    void setHeight(float h);
    void setSize(float w, float h);

    Widget* makeWidget();
    void addWidget(Widget* widget);
    void removeWidget(Widget* widget);
    void moveToFront(Widget* widget);
    void moveToBack(Widget* widget);
    void moveForward(Widget* widget);
    void moveBackward(Widget* widget);

    void initGLFWWindow();
    void destroyGLFWWindow();
    void setBGColor(glm::vec4 color);
    void maximize();
    void render();
    bool shouldClose();

    void updateCursor(TransformType transformType);

    void registerListener(GuiListener* listener);

    // Internal event handlers
    void handleKey(int key, int action, int mods);
    void handleMouseMove(float x, float y);
    void handleMouseButton(int action, MouseButtonType type);
    void handleResize(float width, float height);
    void handleReposition(float x, float y);

    // User-defined render callback
    std::function<void()> onRender;
private:
    static void keyCallback(GLFWwindow *window,
                            int key, int scancode, int action, int mods);

    static void cursorPosCallback(GLFWwindow* window,
                                  double x, double y);

    static void mouseButtonCallback(GLFWwindow* window,
                                    int button, int action, int mods);

    static void framebufferSizeCallback(GLFWwindow* window,
                                        int width, int height);

    static void windowPosCallback(GLFWwindow* window,
                                        int x, int y);
};
