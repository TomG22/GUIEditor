#include <cstdio>
#include <cassert>

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
}

void WindowListenerEx::handleKeyDown(KeyName key, std::vector<ModKeyName> mods) {
    assert(regKeyDown &&
           "Listener Ex ERROR: key down event was fired without being registered");

    onKeyDown(key, mods);
}

void WindowListenerEx::handleKeyUp(KeyName key, std::vector<ModKeyName> mods) {
    assert(regKeyUp &&
           "Listener Ex ERROR: key up event was fired without being registered");

    onKeyUp(key, mods);
}

void WindowListenerEx::handleMouseMove(float x, float y) {
    assert(regMouseMove &&
           "Listener Ex ERROR: mouse move event was fired without being registered");

    onMouseMove(x, y);
}

void WindowListenerEx::handleMouseHover(float x, float y) {
    assert(regMouseHover &&
           "Listener Ex ERROR: mouse hover event was fired without being registered");

    onMouseHover(x, y);
}

void WindowListenerEx::handleMouseEnter() {
    assert(regMouseEnter &&
           "Listener Ex ERROR: mouse enter event was fired without being registered");

    onMouseEnter();
}

void WindowListenerEx::handleMouseLeave() {
    assert(regMouseLeave &&
           "Listener Ex ERROR: mouse leave event was fired without being registered");

    onMouseLeave();
}

void WindowListenerEx::handleMouseDown(float x, float y, MouseButtonType type) {
    assert(regMouseDown &&
           "Listener Ex ERROR: mouse down event was fired without being registered");

    onMouseDown(x, y, type);
}

void WindowListenerEx::handleMouseUp(float x, float y, MouseButtonType type) {
    assert(regMouseUp &&
           "Listener Ex ERROR: mouse up event was fired without being registered");

    onMouseUp(x, y, type);
}
