#include <vector>

#include "Window.h"

class WindowManager {
public:
    std::vector<Window*> windows;

    WindowManager();
    void initGLFW();
    Window* createWindow();
    void startEventLoop();
};
