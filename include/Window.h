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

#include "GuiListener.h"
#include "Renderer.h"
#include "Shader.h"
#include "Widget.h"

class Window {
public:
    GLFWwindow* window;
    GLFWcursor* arrowCursor;
    GLFWcursor* hResizeCursor;
    GLFWcursor* vResizeCursor;
    GLFWcursor* resizeNESWCursor;
    GLFWcursor* resizeNWSECursor;
    GLFWcursor* resizeAllCursor;

    RectPos hoverState;
    RectPos nextHoverState;
    Widget* focusedWidget;
    Widget* hitWidget;
    Widget* hoveredWidget;

    Renderer* renderer;
    Shader* shader2D;

    int width, height;

    glm::mat4 proj;

    std::vector<GuiListener*> listeners;

    std::unordered_map<Widget*, Mesh*> meshMap;

    std::vector<Widget*> widgets;
    std::unordered_map<Widget*, size_t> widgetIndices;

    Window();
    ~Window();

    void RegisterListener(GuiListener* listener);

    Widget* makeWidget();
    void removeWidget(Widget* widget);
    void moveToFront(Widget* widget);
    void moveToBack(Widget* widget);
    void moveForward(Widget* widget);
    void moveBackward(Widget* widget);

    void createMeshForWidget(Widget* widget);
    void updateMeshForWidget(Widget* widget);

    void initGLFWWindow();
    bool shouldClose();
    void render();

    void useArrowCursor();
    void useHResizeCursor();
    void useVResizeCursor();
    void useResizeNESWCursor();
    void useResizeNWSECursor();
    void useResizeAllCursor();

    void updateCursor(RectPos hoverState);

    void handleKey(int key, int action, int mods);
    void handleMouseMove(float x, float y);
    void handleMouseButton(int action, MouseButtonType type);
    void handleResize(int width, int height);
    void handleReposition(int x, int y);

    void addWidget(Widget* widget);

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
