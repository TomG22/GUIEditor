#include <WindowManager.h>

int main() {
    WindowManager winManager = WindowManager();

    float width = 1440.0f;
    float height = 700.0f;

    // Create a window
    Window* window = winManager.createWindow(static_cast<int>(width),
            static_cast<int>(height));
    window->maximize();
    window->setBGColor({ 0.0f, 0.0f, 0.0f, 1.0f });

    const int V_GRIDLINE_COUNT = 10;
    const int V_GRIDLINE_THICKNESS = 2;

    // Create the vertical gridlines
    Widget* gridline;
    for (int i = 0; i < V_GRIDLINE_COUNT; i++) {
        gridline = window->makeWidget();
        gridline->bgColor = {1.0f, 1.0f, 1.0f, 1.0f};

	gridline->setWidth(V_GRIDLINE_THICKNESS);
        gridline->bindParentLayout(&window->layout);
	gridline->setHeight(1.0f);

        gridline->setXPos(i * 1.0f / V_GRIDLINE_COUNT);
    }

    const int H_GRIDLINE_COUNT = 10;
    const int H_GRIDLINE_THICKNESS = 2;

    // Create the horizontal gridlines
    for (int i = 0; i < H_GRIDLINE_COUNT; i++) {
        gridline = window->makeWidget();
        gridline->bgColor = {1.0f, 1.0f, 1.0f, 1.0f};

	gridline->setHeight(H_GRIDLINE_THICKNESS);
        gridline->bindParentLayout(&window->layout);
	gridline->setWidth(1.0f);

        gridline->setYPos(i * 1.0f / H_GRIDLINE_COUNT);
    } 

    winManager.startEventLoop();

    return 0;
}
