#include <WindowManager.h>

int main() {
    WindowManager winManager = WindowManager();

    Window* window = winManager.createWindow(1440, 700);

    Widget* widget = window->makeWidget();
    widget->bgColor = {1.0f, 0.0f, 0.0f, 0.5f};
    window->layout.width.bindRelChild(&widget->bgGeometry->width);
    window->layout.height.bindRelChild(&widget->bgGeometry->height);
    widget->setSize(0.5f, 0.5f);
    widget->showHoverTips();

    /*
    Widget* widget2 = window->makeWidget();
    widget2->bgColor = {0.0f, 1.0f, 0.0f, 0.5f};
    widget2->updatePos(0.0f, 0.5f, GUIUnit::REL_WINDOW);
    widget2->updateSize(0.5f, 0.5f, GUIUnit::REL_WINDOW);
    widget2->showHoverTips();

    Widget* widget3 = window->makeWidget();
    widget3->bgColor = {0.0f, 0.0f, 1.0f, 0.5f};
    widget3->updatePos(0.5f, 0.0f, GUIUnit::REL_WINDOW);
    widget3->updateSize(0.5f, 0.5f, GUIUnit::REL_WINDOW);
    widget3->showHoverTips();

    Widget* widget4 = window->makeWidget();
    widget4->bgColor = {0.5f, 0.5f, 0.5f, 0.5f};
    widget4->updatePos(0.5f, 0.5f, GUIUnit::REL_WINDOW);
    widget4->updateSize(0.5f, 0.5f, GUIUnit::REL_WINDOW);
    widget4->showHoverTips();


    Widget* subWidget = widget->makeSubWidget();
    subWidget->bgColor = {0.5f, 0.1f, 0.1f, 1.0f};
    subWidget->updateSize(300.0, 300.0f, GUIUnit::PIXELS);
    subWidget->updateCornerRadius(0.5f, GUIUnit::REL_SELF);
    subWidget->showHoverTips();
*/
    winManager.startEventLoop();

    return 0;
}

/*
int main() {
    WindowManager winManager = WindowManager();

    Window* window = winManager.createWindow(1440, 700);

    Widget* widget = window->makeWidget();
    widget->bgColor = {1.0f, 0.0f, 0.0f, 0.5f};
    widget->updateSize(0.5f, 0.5f, GUIUnit::REL_WINDOW);
    widget->showHoverTips();

    Widget* widget2 = window->makeWidget();
    widget2->bgColor = {0.0f, 1.0f, 0.0f, 0.5f};
    widget2->updatePos(0.0f, 0.5f, GUIUnit::REL_WINDOW);
    widget2->updateSize(0.5f, 0.5f, GUIUnit::REL_WINDOW);
    widget2->showHoverTips();

    Widget* widget3 = window->makeWidget();
    widget3->bgColor = {0.0f, 0.0f, 1.0f, 0.5f};
    widget3->updatePos(0.5f, 0.0f, GUIUnit::REL_WINDOW);
    widget3->updateSize(0.5f, 0.5f, GUIUnit::REL_WINDOW);
    widget3->showHoverTips();

    Widget* widget4 = window->makeWidget();
    widget4->bgColor = {0.5f, 0.5f, 0.5f, 0.5f};
    widget4->updatePos(0.5f, 0.5f, GUIUnit::REL_WINDOW);
    widget4->updateSize(0.5f, 0.5f, GUIUnit::REL_WINDOW);
    widget4->showHoverTips();


    Widget* subWidget = widget->makeSubWidget();
    subWidget->bgColor = {0.5f, 0.1f, 0.1f, 1.0f};
    subWidget->updateSize(300.0, 300.0f, GUIUnit::PIXELS);
    subWidget->updateCornerRadius(0.5f, GUIUnit::REL_SELF);
    subWidget->showHoverTips();

    winManager.startEventLoop();

    return 0;
}
*/
