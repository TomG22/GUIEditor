#pragma once

#include <vector>

#include "GuiTypes.h"

class GuiListener {
public:
    GuiListener()
        : id(nextId++),
          regKeyDown(false), regKeyUp(false),
          regMouseMove(false), regMouseHover(false),
          regMouseEnter(false), regMouseLeave(false),
          regMouseDown(false), regMouseUp(false),
          regResize(false) {}

    virtual ~GuiListener() = default;

    void addListener(GuiListener* listener) {
        listeners.push_back(listener);
    }

    virtual void onKeyUp(KeyName key, std::vector<ModKeyName> mods) = 0;
    virtual void onKeyDown(KeyName key, std::vector<ModKeyName> mods) = 0;

    virtual void onMouseMove(float x, float y) = 0;
    virtual void onMouseHover(float x, float y) = 0;
    virtual void onMouseEnter() = 0;
    virtual void onMouseLeave() = 0;
    virtual void onMouseDown(float x, float y, MouseButtonType type) = 0;
    virtual void onMouseUp(float x, float y, MouseButtonType type) = 0;

    virtual void onResize(int width, int height) = 0;

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

    bool regResize;


    std::vector<GuiListener*> listeners;    // Sub-listeners

private:
    inline static int nextId = 0;
};
