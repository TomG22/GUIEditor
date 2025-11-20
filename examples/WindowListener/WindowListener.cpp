#include <cstdio>
#include <cassert>

#include "WindowListener.h"

WindowListener::WindowListener() {
    regKeyDown = true;
    regKeyUp = true;

    regMouseMove = true;
    regMouseHover = true;
    regMouseEnter = true;
    regMouseLeave = true;
    regMouseDown = true;
    regMouseUp = true;
}

void WindowListener::handleKeyDown(KeyName key, std::vector<ModKeyName> mods) {
    assert(regKeyDown &&
           "Window Listener ERROR: key down event was fired without being registered");

    onKeyDown(key, mods);
}

void WindowListener::handleKeyUp(KeyName key, std::vector<ModKeyName> mods) {
    assert(regKeyUp &&
           "Window Listener ERROR: key up event was fired without being registered");

    onKeyUp(key, mods);
}

void WindowListener::handleMouseMove(float x, float y) {
    assert(regMouseMove &&
           "Window Listener ERROR: mouse move event was fired without being registered");

    onMouseMove(x, y);
}

void WindowListener::handleMouseHover(float x, float y) {
    assert(regMouseHover &&
           "Window Listener ERROR: mouse hover event was fired without being registered");

    onMouseHover(x, y);
}

void WindowListener::handleMouseEnter() {
    assert(regMouseEnter &&
           "Window Listener ERROR: mouse enter event was fired without being registered");

    onMouseEnter();
}

void WindowListener::handleMouseLeave() {
    assert(regMouseLeave &&
           "Window Listener ERROR: mouse leave event was fired without being registered");

    onMouseLeave();
}

void WindowListener::handleMouseDown(float x, float y, MouseButtonType type) {
    assert(regMouseDown &&
           "Window Listener ERROR: mouse down event was fired without being registered");

    onMouseDown(x, y, type);
}

void WindowListener::handleMouseUp(float x, float y, MouseButtonType type) {
    assert(regMouseUp &&
           "Window Listener ERROR: mouse up event was fired without being registered");

    onMouseUp(x, y, type);
}
