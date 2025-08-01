#pragma once

#include <functional>
#include <vector>

#include "GuiTypes.h"

class GuiListener {
public:
    GuiListener()
        : id(nextId++),
          regKeyDown(false), regKeyUp(false),
          regMouseMove(false), regMouseHover(false),
          regMouseEnter(false), regMouseLeave(false),
          regMouseDown(false), regMouseUp(false)
    {}

    // Internal event functions
    virtual void handleKeyDown(KeyName key, std::vector<ModKeyName> mods) = 0;
    virtual void handleKeyUp(KeyName key, std::vector<ModKeyName> mods) = 0;

    virtual void handleMouseMove(float x, float y) = 0;
    virtual void handleMouseHover(float x, float y) = 0;
    virtual void handleMouseEnter() = 0;
    virtual void handleMouseLeave() = 0;
    virtual void handleMouseDown(float x, float y, MouseButtonType type) = 0;
    virtual void handleMouseUp(float x, float y, MouseButtonType type) = 0;

    void addListener(GuiListener* listener) {
        listeners.push_back(listener);
    }

    // External user-defined events
    std::function<void(KeyName key, std::vector<ModKeyName> mods)> onKeyDown;
    std::function<void(KeyName key, std::vector<ModKeyName> mods)> onKeyUp;

    std::function<void(float x, float y)> onMouseMove;
    std::function<void(float x, float y)> onMouseHover;
    std::function<void()> onMouseEnter;
    std::function<void()> onMouseLeave;
    std::function<void(float x, float y, MouseButtonType type)> onMouseDown;
    std::function<void(float x, float y, MouseButtonType type)> onMouseUp;

    std::function<void(float x, float y)> onReposition;
    std::function<void(float width, float height)> onResize;

    int id;

    // Flags for if events are registered for listening
    bool regKeyDown;
    bool regKeyUp;

    bool regMouseMove;
    bool regMouseHover;
    bool regMouseEnter;
    bool regMouseLeave;
    bool regMouseDown;
    bool regMouseUp;

    std::vector<GuiListener*> listeners;    // Sub-listeners

private:
    inline static int nextId = 0;
};
