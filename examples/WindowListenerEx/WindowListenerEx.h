#pragma once

#include <GuiListener.h>

class WindowListenerEx : public GuiListener {
public:
    WindowListenerEx();
    void handleKeyDown(KeyName key, std::vector<ModKeyName> mods) override;
    void handleKeyUp(KeyName key, std::vector<ModKeyName> mods) override;

    void handleMouseMove(float x, float y) override;
    void handleMouseHover(float x, float y) override;
    void handleMouseEnter() override;
    void handleMouseLeave() override;
    void handleMouseDown(float x, float y, MouseButtonType type) override;
    void handleMouseUp(float x, float y, MouseButtonType type) override;
};
