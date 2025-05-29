#pragma once

class WindowListener {
public:
    virtual ~WindowListener() = default;

    virtual void OnKey(int key, int scancode, int action, int mods) = 0;
};
