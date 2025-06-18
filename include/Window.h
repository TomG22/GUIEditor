#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <thread>
#include <vector>

#include <functional>
#include <queue>
#include <mutex>
#include <utility>

#include "Frame.h"
#include "WindowListener.h"

class Window {
private:
    static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
    static void cursorPosCallback(GLFWwindow* window, double x, double y);
    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);

public:
    int width, height;
    GLFWwindow* window;
    Shader* shader2D;

    glm::mat4 proj;

    std::vector<Frame> frames;

    std::mutex cmdQueueMut;
    std::queue<std::function<void()>> cmdQueue;

    std::vector<WindowListener*> listeners;

    Window();

    void RegisterListener(WindowListener* listener);
    void initGLFW();
    void startWindowLoop();
    bool isKeyDown(int keyCode);
    void handleMouseMove(double x, double y);
    void handleKey(int key, int scancode, int action, int mods);
    void handleResize(int width, int height);

    void addFrame(Frame frame);

    void postToRenderThread(std::function<void()> command);
};
