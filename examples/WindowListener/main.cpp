#include <string>

#include <WindowManager.h>
#include "WindowListener.h"
#include <chrono>

glm::vec3 hsvToRgb(float h, float s, float v) {
    h = glm::mod(h, 1.0f);
    float c = v * s;
    float x = c * (1 - fabsf(fmodf(h * 6, 2) - 1));
    float m = v - c;

    float r, g, b;
    if      (h < 1.0f/6.0f) { r = c; g = x; b = 0; }
    else if (h < 2.0f/6.0f) { r = x; g = c; b = 0; }
    else if (h < 3.0f/6.0f) { r = 0; g = c; b = x; }
    else if (h < 4.0f/6.0f) { r = 0; g = x; b = c; }
    else if (h < 5.0f/6.0f) { r = x; g = 0; b = c; }
    else                    { r = c; g = 0; b = x; }

    return glm::vec3(r + m, g + m, b + m);
}

struct InputState {
    bool up;
    bool down;
    bool left;
    bool right;
};

int main(int argc, char* argv[]) {
    WindowManager winManager = WindowManager();

    int winCount = 0;
    if (argc > 1) {
        winCount = std::stoi(argv[1]);
    }

    int cols = static_cast<int>(std::ceil(std::sqrt(winCount)));
    int rows = static_cast<int>(std::ceil(static_cast<float>(winCount) / cols));

    float spacing = 10;

    float winWidth = (winManager.screenWidth - (cols - 1) * spacing) / cols;
    float winHeight = (winManager.screenHeight - (rows - 1) * spacing) / rows;

    for (int i = 0; i < winCount; i++) {
        Window* window = winManager.createWindow(static_cast<int>(winWidth),
                static_cast<int>(winHeight));

        float hue = float(i) / float(winCount);
        glm::vec3 rgb = hsvToRgb(hue, 1.0f, 1.0f);
        window->setBGColor(glm::vec4(rgb, 1.0f));

        int row = i / cols;
        int col = i % cols;

        float xPos = col * (winWidth + spacing);
        float yPos = row * (winHeight + spacing);

        // Make a new window and a listener for its events
        window->setPos(xPos, yPos);
        WindowListener* listener = new WindowListener();
        window->registerListener(listener);
        int id = listener->id;


        // Make a square widget whose width is half of the height of the window
        Widget* widget = window->makeWidget();
        widget->layout->bindRelTo(&window->layout, RelAttrType::HEIGHT, RelAttrType::SIZE);
        widget->setSize(0.25, 0.25);
        widget->layout->unbindRelTo(&window->layout, RelAttrType::HEIGHT, RelAttrType::SIZE);

        widget->setPos(winWidth / 2 - widget->layout->width.getAbsValue() / 2, winHeight / 2 - widget->layout->width.getAbsValue() / 2);

        InputState* input = new InputState();

        float delta = 5.0;

        // On every frame update, move the widget based on the input state
        window->onRender = [widget, delta, input]() {
            if (input->up) {
                widget->setPos(widget->layout->xPos.getAbsValue(), widget->layout->yPos.getAbsValue() - delta);
            }
            if (input->down) {
                widget->setPos(widget->layout->xPos.getAbsValue(), widget->layout->yPos.getAbsValue() + delta);
            }
            if (input->left) {
                widget->setPos(widget->layout->xPos.getAbsValue() - delta, widget->layout->yPos.getAbsValue());
            }
            if (input->right) {
                widget->setPos(widget->layout->xPos.getAbsValue() + delta, widget->layout->yPos.getAbsValue());
            }
        };

        // On every key down event for this window, update the input state
        listener->onKeyDown = [id, input](KeyName key, std::vector<ModKeyName> mods) mutable {
            printf("Listener %d: Key down: %d\n", id, key);
            switch (key) {
                case KeyName::UP_ARROW_KEY:
                    input->up = true;
                    break;
                case KeyName::DOWN_ARROW_KEY:
                    input->down = true;
                    break;
                case KeyName::LEFT_ARROW_KEY:
                    input->left = true;
                    break;
                case KeyName::RIGHT_ARROW_KEY:
                    input->right = true;
                    break;
            }
        };

        // On every key up event for this window, update the input state
        listener->onKeyUp = [id, input](KeyName key, std::vector<ModKeyName> mods) mutable {
            printf("Listener %d: Key up: %d\n", id, key);

            switch (key) {
                case KeyName::UP_ARROW_KEY:
                    input->up = false;
                    break;
                case KeyName::DOWN_ARROW_KEY:
                    input->down = false;
                    break;
                case KeyName::LEFT_ARROW_KEY:
                    input->left = false;
                    break;
                case KeyName::RIGHT_ARROW_KEY:
                    input->right = false;
                    break;
            }
        };

        listener->onMouseMove = [id](float x, float y) {
            printf("Listener %d: Mouse moved to (%f, %f) position\n", id, x, y);
        };

        listener->onMouseHover = [id](float x, float y) {
            printf("Listener %d: Mouse hovered on (%f, %f) position\n", id, x, y);
        };

        listener->onMouseEnter = [id]() {
            printf("Listener %d: Mouse entered\n", id);
        };

        listener->onMouseLeave = [id]() {
            printf("Listener %d: Mouse left\n", id);
        };

        listener->onMouseDown = [id](float x, float y, MouseButtonType type) {
            printf("Listener %d: Mouse button %d down at (%f, %f)\n", id, type, x, y);
        };

        listener->onMouseUp = [id](float x, float y, MouseButtonType type) {
            printf("Listener %d: Mouse button %d up at (%f, %f)\n", id, type, x, y);
        };
    }

    winManager.startEventLoop();

    return 0;
}
