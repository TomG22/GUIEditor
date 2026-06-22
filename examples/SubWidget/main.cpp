#include <WindowManager.h>

int main() {
    WindowManager winManager = WindowManager();

    float width = 1440.0f;
    float height = 700.0f;

    // Create a window
    Window* window = winManager.createWindow(static_cast<int>(width),
            static_cast<int>(height));
    window->maximize();
    window->setBGColor({ 1.0f, 1.0f, 1.0f, 1.0f });

    // Create widgetA
    Widget* widgetA = window->makeWidget();
    widgetA->bgColor = {1.0f, 0.0f, 0.0f, 0.5f};

    // Bind widgetA to the window 
    widgetA->bindParentLayout(&window->layout);
    widgetA->setSize(1.0f, 0.5f);
    widgetA->showHoverTips();

    // Create subWidgetA
    Widget* subWidgetA = widgetA->makeSubWidget();
    subWidgetA->bgColor = {1.0f, 0.0f, 0.0f, 0.5f};
    subWidgetA->showHoverTips();

    // Bind subWidgetA size to widgetA
    subWidgetA->bindParentLayout(&widgetA->layout);
    subWidgetA->setSize(1.0f, 0.5f);
    subWidgetA->setPos(0.0f, 0.0f);

    // Create widgetB
    Widget* widgetB = widgetA->makeSubWidget();
    widgetB->bgColor = {0.0f, 0.0f, 1.0f, 0.5f};
    widgetB->showHoverTips();

    // Bind widgetB to widgetA 
    widgetB->bindParentLayout(&widgetA->layout);
    widgetB->setSize(0.5f, 1.0f);

    // Create subWidgetB
    Widget* subWidgetB = widgetB->makeSubWidget();
    subWidgetB->bgColor = {0.0f, 0.0f, 1.0f, 0.5f};
    subWidgetB->showHoverTips();

    // Bind subWidgetB's size to widgetB
    subWidgetB->bindParentLayout(&widgetB->layout);
    subWidgetB->setSize(0.5f, 1.0f);

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
