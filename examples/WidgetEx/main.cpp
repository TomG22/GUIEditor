#include <WindowManager.h>

int main() {
    WindowManager winManager = WindowManager();

    Window* window = winManager.createWindow();

    Widget* absWidget = window->makeWidget();
    absWidget->bgColor = {0.5f, 0.5f, 0.5f, 1.0f};
    absWidget->requestBGMeshCreation();
    absWidget->setAbsTransform({0.0f, 0.0f}, {300.0f, 300.0f});
    absWidget->setRelRadius(0.5f);
    absWidget->lockZIndex = false;

    Widget* relWidget = window->makeWidget();
    relWidget->bgColor = {0.5f, 0.1f, 0.1f, 1.0f};
    relWidget->requestBGMeshCreation();
    relWidget->setRelPos(0.5f, 0.25f);
    relWidget->setRelSize(0.5f, 0.5f);
    relWidget->setAbsRadius(20.0f);
    relWidget->lockZIndex = false;

    winManager.startEventLoop();

    return 0;
}
