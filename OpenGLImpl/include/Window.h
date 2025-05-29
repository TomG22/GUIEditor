#pragma once

/**
 * Class description...
 */

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "WindowListener.h"
#include <thread>
#include <vector>

class Window {
public:
	GLFWwindow* window;
    std::vector<WindowListener*> listeners;

	Window();

    void RegisterListener(WindowListener* listener);
	int startWindowLoop();
    bool isKeyDown(int keyCode);
    void handleKey(int key, int scancode, int action, int mods);

private:
    static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
};
