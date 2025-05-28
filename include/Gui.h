#pragma once

/**
 * Class description...
 */

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "GuiListener.h"
#include <thread>
#include <vector>

class Gui {
public:
	GLFWwindow* window;
    std::vector<GuiListener*> listeners;

	Gui();

    void RegisterListener(GuiListener*);
	int startGuiLoop();
    bool isKeyDown(int keyCode);
    void handleKey(int key, int scancode, int action, int mods);

private:
    static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
};
