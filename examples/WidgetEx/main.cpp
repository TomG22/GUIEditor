#include <WindowManager.h>

int main() {
    WindowManager winManager = WindowManager();

    float width = 1440.0f;
    float height = 700.0f;

    // Window creation
    Window* window = winManager.createWindow(static_cast<int>(width),
                                             static_cast<int>(height));

    float xPos = winManager.screenWidth / 2.0f - width / 2.0f;
    float yPos = winManager.screenHeight / 2.0f - height / 2.0f;

    window->setPos(xPos, yPos);

    // Absolute widget creation
    Widget* absWidget = window->makeWidget();

    absWidget->bgColor = {0.5f, 0.5f, 0.5f, 1.0f};

    absWidget->setSize(300.0f, 300.0f);

    absWidget->layout->width.addRelSizeChild(&absWidget->layout->cornerRadiusWidth);
    absWidget->layout->height.addRelSizeChild(&absWidget->layout->cornerRadiusHeight);

    absWidget->setCornerRadius(0.5f);

    absWidget->showHoverTips();
    absWidget->lockZIndex = false;

    // Relative widget creation
    Widget* relWidget = window->makeWidget();
    relWidget->bgColor = {0.5f, 0.1f, 0.1f, 1.0f};
    relWidget->showHoverTips();
    relWidget->lockZIndex = false;

    // Bind the widget's position to the window's position
    relWidget->layout->bindRelTo(&window->layout, RelAttrType::POS, RelAttrType::POS);
    relWidget->setPos(0.25f, 0.25f);

    // Bind the widget's size to the window's size
    relWidget->layout->bindRelTo(&window->layout, RelAttrType::SIZE, RelAttrType::SIZE);
    relWidget->setSize(0.5f, 0.5f);

    relWidget->setCornerRadius(20.0f);

    winManager.startEventLoop();

    return 0;
}
