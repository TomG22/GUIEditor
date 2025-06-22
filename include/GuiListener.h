#include <vector>

#pragma once

class GuiListener {
public:
    virtual ~GuiListener() = default;

    std::vector<GuiListener*> listeners;    // Child listeners

    void registerListener(GuiListener* listener) {
        listeners.push_back(listener);
    }

    virtual void onKey(int key, int scancode, int action, int mods) = 0;

    virtual void onMouseMove(float x, float y) = 0;
    virtual void onMouseEnter() = 0;
    virtual void onMouseLeave() = 0;
    virtual void onMouseDownLeft(float x, float y, int mods) = 0;
    virtual void onMouseUpLeft(float x, float y, int mods) = 0;
    virtual void onMouseDownRight(float x, float y, int mods) = 0;
    virtual void onMouseUpRight(float x, float y, int mods) = 0;
    virtual void onMouseDownMiddle(float x, float y, int mods) = 0;
    virtual void onMouseUpMiddle(float x, float y, int mods) = 0;
};
