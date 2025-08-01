#include <WindowManager.h>

int main() {
    WindowManager winManager = WindowManager();

    Window* window = winManager.createWindow(1440, 700);

    Widget* absWidget = window->makeWidget();
    absWidget->bgColor = {0.5f, 0.5f, 0.5f, 1.0f};
    absWidget->setSize(300.0f, 300.0f);
    //absWidget->updateCornerRadius(0.5f, GUIUnit::REL_SELF);
    absWidget->showHoverTips();
    absWidget->lockZIndex = false;
/*
    Widget* relWidget = window->makeWidget();
    relWidget->bgColor = {0.5f, 0.1f, 0.1f, 1.0f};
    relWidget->updatePos(0.5f, 0.25f, GUIUnit::REL_WINDOW);
    relWidget->updateSize(0.5f, 0.5f, GUIUnit::REL_WINDOW);
    relWidget->updateCornerRadius(20.0f, GUIUnit::PIXELS);
    relWidget->showHoverTips();
    relWidget->lockZIndex = false;
*/
    winManager.startEventLoop();

    return 0;
}
