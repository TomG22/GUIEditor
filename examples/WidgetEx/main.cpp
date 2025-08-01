#include <WindowManager.h>

int main() {
    WindowManager winManager = WindowManager();

    float width = 1440.0f;
    float height = 700.0f;

    Window* window = winManager.createWindow(static_cast<int>(width),
                                             static_cast<int>(height));

    float xPos = winManager.screenWidth / 2.0f - width / 2.0f;
    float yPos = winManager.screenHeight / 2.0f - height / 2.0f;

    window->setPos(xPos, yPos);

    Widget* absWidget = window->makeWidget();

    absWidget->bgColor = {0.5f, 0.5f, 0.5f, 1.0f};

    absWidget->setSize(300.0f, 300.0f);

    absWidget->bgGeometry->width.bindRelChild(&absWidget->bgGeometry->cornerRadiusWidth);
    absWidget->bgGeometry->height.bindRelChild(&absWidget->bgGeometry->cornerRadiusHeight);

    absWidget->setCornerRadius(0.5f);

    absWidget->showHoverTips();
    absWidget->lockZIndex = false;

    Widget* relWidget = window->makeWidget();

    relWidget->bgColor = {0.5f, 0.1f, 0.1f, 1.0f};

    window->layout.width.bindRelChild(&relWidget->bgGeometry->xPos);
    window->layout.height.bindRelChild(&relWidget->bgGeometry->yPos);
    relWidget->setPos(0.25f, 0.25f);

    window->layout.width.bindRelChild(&relWidget->bgGeometry->width);
    window->layout.height.bindRelChild(&relWidget->bgGeometry->height);
    relWidget->setSize(0.5f, 0.5f);

    relWidget->setCornerRadius(20.0f);

    relWidget->showHoverTips();
    relWidget->lockZIndex = false;

    winManager.startEventLoop();

    return 0;
}
