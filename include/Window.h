#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <unordered_map>
#include <vector>

#include <functional>
#include <queue>
#include <mutex>
#include <utility>

#include "Rect.h"
#include "GuiListener.h"
#include "Renderer.h"
#include "Shader.h"
#include "Widget.h"

class Window {
public:
    GLFWwindow* window;
    GLFWcursor* arrowCursor, *resizeAllCursor;
    GLFWcursor* resizeHCursor, *resizeVCursor;
    GLFWcursor* resizeNESWCursor, *resizeNWSECursor;

    bool visible;
    bool decorated;

    TransformType cursorState;
    TransformType nextCursorState;

    Widget* focusedWidget;
    Widget* hitWidget;
    Widget* hoveredWidget;

    Renderer* renderer;

    Rect layout;

    glm::vec4 bgColor;

    std::vector<GuiListener*> listeners;

    std::vector<Widget*> widgets;
    std::unordered_map<Widget*, size_t> widgetIndices;

    Window(float width, float height);
    ~Window();

    void show();
    void hide();

    void setPos(float x, float y);
    void setSize(float width, float height);

    void showDecorations();
    void hideDecorations();

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
