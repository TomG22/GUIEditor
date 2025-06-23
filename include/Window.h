#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <thread>
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
private:
    static void keyCallback(GLFWwindow *window,
                            int key, int scancode, int action, int mods);

    static void cursorPosCallback(GLFWwindow* window,
                                  double x, double y);

    static void mouseButtonCallback(GLFWwindow* window,
                                    int button, int action, int mods);

    static void framebufferSizeCallback(GLFWwindow* window,
                                        int width, int height);

public:
    GLFWwindow* window;
    GLFWcursor* arrowCursor;
    GLFWcursor* hResizeCursor;
    GLFWcursor* vResizeCursor;
    GLFWcursor* resizeNESWCursor;
    GLFWcursor* resizeNWSECursor;
    GLFWcursor* resizeAllCursor;

    HoverState hoverState;

    Renderer* renderer;
    Shader* shader2D;

    int width, height;

    glm::mat4 proj;

    std::vector<GuiListener*> listeners;
    std::vector<Widget*> widgets;

    std::mutex cmdQueueMut;
    std::queue<std::function<void()>> cmdQueue;


    Window();

    void RegisterListener(GuiListener* listener);
    Widget* makeWidget();
    void initGLFW();
    void startWindowLoop();

    void useArrowCursor();
    void useHResizeCursor();
    void useVResizeCursor();
    void useResizeNESWCursor();
    void useResizeNWSECursor();
    void useResizeAllCursor();

    void updateCursor(Widget* widget);

    bool isKeyDown(int keyCode);
    void handleKey(int key, int scancode, int action, int mods);
    void handleMouseMove(float x, float y);
    void handleMouseButton(int button, int action, int mods);
    void handleResize(int width, int height);

    void addWidget(Widget* widget);

    void postToRenderThread(std::function<void()> command);
};
