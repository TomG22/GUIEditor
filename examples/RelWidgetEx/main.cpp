#include <WindowManager.h>

int main() {
    WindowManager winManager = WindowManager();

    float width = 1440.0f;
    float height = 700.0f;

    Window* window = winManager.createWindow(static_cast<int>(width),
            static_cast<int>(height));
    window->maximize();

    float xPos = winManager.screenWidth / 2.0f - width / 2.0f;
    float yPos = winManager.screenHeight / 2.0f - height / 2.0f;

    // Create widgetA
    Widget* widgetA = window->makeWidget();
    widgetA->bgColor = {1.0f, 0.0f, 0.0f, 1.0f};
    widgetA->showHoverTips();

    // Bind widgetA's size to the window's size
    window->layout.width.addRelSizeChild(&widgetA->bgGeometry->width);
    window->layout.height.addRelSizeChild(&widgetA->bgGeometry->height);

    widgetA->setSize(0.5f, 0.5f);

    winManager.startEventLoop();

    return 0;
}
