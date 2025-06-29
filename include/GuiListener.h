#pragma once

#include <vector>

#include "GuiTypes.h"

class GuiListener {
public:
    GuiListener() : id(nextId++) {}
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
    bool regKeyDown = false;
    bool regKeyUp = false;

    bool regMouseMove = false;
    bool regMouseHover = false;
    bool regMouseEnter = false;
    bool regMouseLeave = false;
    bool regMouseDown = false;
    bool regMouseUp = false;

    bool regResize = false;


    std::vector<GuiListener*> listeners;    // Sub-listeners

private:
    inline static int nextId = 0;
};
