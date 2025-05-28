#pragma once

// Interface
class GuiListener {
public:
    virtual void OnKey(int key, int scancode, int action, int mods) = 0;
    virtual ~GuiListener() = default;
};

