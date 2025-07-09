#include "ListenerExample.h"
#include <cstdio>

ListenerExample::ListenerExample() {
    regKeyDown = true;
    regKeyUp = true;

    regMouseMove = true;
    regMouseHover = true;
    regMouseEnter = true;
    regMouseLeave = true;
    regMouseDown = true;
    regMouseUp = true;

    regResize = true;
}

void ListenerExample::onKeyUp(KeyName key, std::vector<ModKeyName> mods) {
    printf("Listener: Key up: %d\n", key);
}

void ListenerExample::onKeyDown(KeyName key, std::vector<ModKeyName> mods) {
    printf("Listener: Key down: %d\n", key);
}

void ListenerExample::onMouseMove(float x, float y) {
    printf("Listener: Mouse moved to (%f, %f) position\n", x, y);
}

void ListenerExample::onMouseHover(float x, float y) {
    printf("Listener: Mouse hovered on (%f, %f) position\n", x, y);
}

void ListenerExample::onMouseEnter() {
    printf("Listener: Mouse entered\n");
}

void ListenerExample::onMouseLeave() {
    printf("Listener: Mouse left\n");
}

void ListenerExample::onMouseDown(float x, float y, MouseButtonType type) {
    printf("Listener: Mouse button %d down at (%f, %f)\n", type, x, y);
}

void ListenerExample::onMouseUp(float x, float y, MouseButtonType type) {
    printf("Listener: Mouse button %d up at (%f, %f)\n", type, x, y);
}

void ListenerExample::onResize(int width, int height) {
    printf("Listener: Window resized to %d x %d\n", width, height);
}
