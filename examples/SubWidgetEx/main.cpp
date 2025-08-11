#include <WindowManager.h>

int main() {
    WindowManager winManager = WindowManager();

    float width = 1440.0f;
    float height = 700.0f;

    Window* window = winManager.createWindow(static_cast<int>(width),
                                             static_cast<int>(height));

    float xPos = winManager.screenWidth / 2.0f - width / 2.0f;
    float yPos = winManager.screenHeight / 2.0f - height / 2.0f;

    Widget* widgetA = window->makeWidget();
    widgetA->bgColor = {1.0f, 0.0f, 0.0f, 0.5f};
    window->layout.width.addRelSizeChild(&widgetA->bgGeometry->width);
    window->layout.height.addRelSizeChild(&widgetA->bgGeometry->height);
    widgetA->setSize(1.0f, 0.5f);
    widgetA->showHoverTips();

    Widget* subWidgetA = widgetA->makeSubWidget();
    subWidgetA->bgColor = {1.0f, 0.0f, 0.0f, 0.5f};
    widgetA->bgGeometry->width.addRelSizeChild(&subWidgetA->bgGeometry->width);
    widgetA->bgGeometry->height.addRelSizeChild(&subWidgetA->bgGeometry->height);
    subWidgetA->setSize(1.0f, 0.5f);
    widgetA->bgGeometry->xPos.addRelPosChild(&subWidgetA->bgGeometry->xPos);
    widgetA->bgGeometry->yPos.addRelPosChild(&subWidgetA->bgGeometry->yPos);
    widgetA->bgGeometry->width.addRelPosChild(&subWidgetA->bgGeometry->xPos);
    widgetA->bgGeometry->width.addRelPosChild(&subWidgetA->bgGeometry->yPos);
    subWidgetA->setPos(0.0f, 0.0f);
    subWidgetA->showHoverTips();

    Widget* widgetB = window->makeWidget();
    widgetB->bgColor = {0.0f, 0.0f, 1.0f, 0.5f};
    window->layout.width.addRelSizeChild(&widgetB->bgGeometry->width);
    window->layout.height.addRelSizeChild(&widgetB->bgGeometry->height);
    widgetB->setSize(0.5f, 1.0f);
    widgetB->showHoverTips();

    Widget* subWidgetB = widgetB->makeSubWidget();
    subWidgetB->bgColor = {0.0f, 0.0f, 1.0f, 0.5f};
    widgetB->bgGeometry->width.addRelSizeChild(&subWidgetB->bgGeometry->width);
    widgetB->bgGeometry->height.addRelSizeChild(&subWidgetB->bgGeometry->height);
    subWidgetB->setSize(0.5f, 1.0f);
    widgetB->bgGeometry->xPos.addRelPosChild(&subWidgetB->bgGeometry->xPos);
    widgetB->bgGeometry->yPos.addRelPosChild(&subWidgetB->bgGeometry->yPos);
    widgetB->bgGeometry->width.addRelPosChild(&subWidgetB->bgGeometry->xPos);
    widgetB->bgGeometry->width.addRelPosChild(&subWidgetB->bgGeometry->yPos);
    subWidgetB->setPos(0.0f, 0.0f);
    subWidgetB->showHoverTips();

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
