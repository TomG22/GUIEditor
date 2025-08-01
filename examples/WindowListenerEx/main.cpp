#include <string>

#include <WindowManager.h>
#include "WindowListenerEx.h"

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
        window->hideDecorations();

        float hue = float(i) / float(winCount);
        glm::vec3 rgb = hsvToRgb(hue, 1.0f, 1.0f);
        window->setBGColor(glm::vec4(rgb, 1.0f));

        int row = i / cols;
        int col = i % cols;

        float xPos = col * (winWidth + spacing);
        float yPos = row * (winHeight + spacing);

        window->setPos(xPos, yPos);
        WindowListenerEx* listener = new WindowListenerEx();
        window->registerListener(listener);

        window->show();

        int id = listener->id;

        listener->onKeyDown = [id](KeyName key, std::vector<ModKeyName> mods) {
            printf("Listener %d: Key down: %d\n", id, key);
        };

        listener->onKeyUp = [id](KeyName key, std::vector<ModKeyName> mods) {
            printf("Listener %d: Key up: %d\n", id, key);
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

        listener->onResize = [id](float width, float height) {
            printf("Listener %d: Parent resized to %f x %f\n", id, width, height);
        };

        listener->onReposition = [id](float x, float y) {
            printf("Listener %d: Parent repositioned to (%f, %f)\n", id, x, y);
        };
    }

    winManager.startEventLoop();

    return 0;
}
