#include <WindowManager.h>

int main() {
    WindowManager winManager = WindowManager();

    float width = 1440.0f;
    float height = 700.0f;

    Window* window = winManager.createWindow(static_cast<int>(width),
                                             static_cast<int>(height));
    window->maximize();
    window->setBGColor({ 1.0f, 1.0f, 1.0f, 1.0f });

    float xPos = winManager.screenWidth / 2.0f - width / 2.0f;
    float yPos = winManager.screenHeight / 2.0f - height / 2.0f;

    // Create widgetA
    Widget* widgetA = window->makeWidget();
    widgetA->bgColor = {1.0f, 0.0f, 0.0f, 0.5f};

    // Bind widgetA's size to the window's size
    widgetA->bgGeometry->width.setRelSizeParent(&window->layout.width);
    widgetA->bgGeometry->height.setRelSizeParent(&window->layout.height);
    widgetA->setSize(1.0f, 0.5f);
    widgetA->showHoverTips();

    // Create subWidgetA
    Widget* subWidgetA = widgetA->makeSubWidget();
    subWidgetA->bgColor = {1.0f, 0.0f, 0.0f, 0.5f};

    // Bind subWidgetA's size to widgetA's size
    subWidgetA->bgGeometry->width.setRelSizeParent(&widgetA->bgGeometry->width);
    subWidgetA->bgGeometry->height.setRelSizeParent(&widgetA->bgGeometry->height);
    subWidgetA->setSize(1.0f, 0.5f);

    // Bind subWidgetA's pos to widgetA's pos
    subWidgetA->bgGeometry->xPos.setRelPosParent(&widgetA->bgGeometry->xPos);
    subWidgetA->bgGeometry->yPos.setRelPosParent(&widgetA->bgGeometry->yPos);
    subWidgetA->bgGeometry->width.setRelSizeParent(&widgetA->bgGeometry->width);
    subWidgetA->bgGeometry->height.setRelSizeParent(&widgetA->bgGeometry->height);
    subWidgetA->setPos(0.0f, 0.0f);
    subWidgetA->showHoverTips();

    // Create widgetB
    Widget* widgetB = widgetA->makeSubWidget();
    widgetB->bgColor = {0.0f, 0.0f, 1.0f, 0.5f};

    // Bind widgetB to widgetA's position
    widgetB->bgGeometry->xPos.setRelPosParent(&widgetA->bgGeometry->xPos);
    widgetB->bgGeometry->yPos.setRelPosParent(&widgetA->bgGeometry->yPos);
    widgetB->bgGeometry->width.setRelSizeParent(&widgetA->bgGeometry->width);
    widgetB->bgGeometry->height.setRelSizeParent(&widgetA->bgGeometry->height);

    // Bind widgetB's size to the window's size
    widgetB->bgGeometry->width.setRelSizeParent(&window->layout.width);
    widgetB->bgGeometry->height.setRelSizeParent(&window->layout.height);
    widgetB->setSize(0.5f, 1.0f);
    widgetB->showHoverTips();

    // Create subWidgetB
    Widget* subWidgetB = widgetB->makeSubWidget();
    subWidgetB->bgColor = {0.0f, 0.0f, 1.0f, 0.5f};

    // Bind subWidgetB's size to widgetB's size
    //
    subWidgetB->bgGeometry->width.setRelSizeParent(&widgetB->bgGeometry->width);
    subWidgetB->bgGeometry->height.setRelSizeParent(&widgetB->bgGeometry->height);
    subWidgetB->setSize(0.5f, 1.0f);

    // Bind subWidgetB's pos to widgetB's pos
    subWidgetB->bgGeometry->xPos.setRelPosParent(&widgetB->bgGeometry->xPos);
    subWidgetB->bgGeometry->yPos.setRelPosParent(&widgetB->bgGeometry->xPos);
    subWidgetB->bgGeometry->width.setRelSizeParent(&widgetB->bgGeometry->width);
    subWidgetB->bgGeometry->height.setRelSizeParent(&widgetB->bgGeometry->height);
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
