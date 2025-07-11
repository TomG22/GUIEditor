#include <cstdio>

#include "WindowListenerEx.h"

WindowListenerEx::WindowListenerEx() {
    regKeyDown = true;
    regKeyUp = true;

    regMouseMove = true;
    regMouseHover = true;
    regMouseEnter = true;
    regMouseLeave = true;
    regMouseDown = true;
    regMouseUp = true;

    regResize = true;
    regReposition = true;
}

void WindowListenerEx::onKeyUp(KeyName key, std::vector<ModKeyName> mods) {
    printf("Listener %d: Key up: %d\n", id, key);
}

void WindowListenerEx::onKeyDown(KeyName key, std::vector<ModKeyName> mods) {
    printf("Listener %d: Key down: %d\n", id, key);
}

void WindowListenerEx::onMouseMove(float x, float y) {
    printf("Listener %d: Mouse moved to (%f, %f) position\n", id, x, y);
}

void WindowListenerEx::onMouseHover(float x, float y) {
    printf("Listener %d: Mouse hovered on (%f, %f) position\n", id, x, y);
}

void WindowListenerEx::onMouseEnter() {
    printf("Listener %d: Mouse entered\n", id);
}

void WindowListenerEx::onMouseLeave() {
    printf("Listener %d: Mouse left\n", id);
}

void WindowListenerEx::onMouseDown(float x, float y, MouseButtonType type) {
    printf("Listener %d: Mouse button %d down at (%f, %f)\n", id, type, x, y);
}

void WindowListenerEx::onMouseUp(float x, float y, MouseButtonType type) {
    printf("Listener %d: Mouse button %d up at (%f, %f)\n", id, type, x, y);
}

void WindowListenerEx::onResize(int width, int height) {
    printf("Listener %d: Parent resized to %d x %d\n", id, width, height);
}

void WindowListenerEx::onReposition(int x, int y) {
    printf("Listener %d: Parent repositioned to (%d, %d)\n", id, x, y);
}
