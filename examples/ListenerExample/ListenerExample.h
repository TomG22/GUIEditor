#pragma once

#include <WindowListener.h>

class ListenerExample : public WindowListener {
public:
    ListenerExample();
    void OnKey(int key, int scancode, int action, int mods) override;
};
