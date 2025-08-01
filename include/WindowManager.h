#include <vector>

#include "Window.h"

class WindowManager {
public:
    std::vector<Window*> windows;

    int screenWidth, screenHeight;

    WindowManager();
    void initGLFW();
    Window* createWindow(int width, int height);
    void startEventLoop();
    void handleMonitorEvent(GLFWmonitor* monitor, int event);
};
