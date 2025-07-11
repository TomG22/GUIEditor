#pragma once

#include <GuiListener.h>

class WindowListenerEx : public GuiListener {
public:
    WindowListenerEx();
    void onKeyUp(KeyName key, std::vector<ModKeyName> mods) override;
    void onKeyDown(KeyName key, std::vector<ModKeyName> mods) override;

    void onMouseMove(float x, float y) override;
    void onMouseHover(float x, float y) override;
    void onMouseEnter() override;
    void onMouseLeave() override;
    void onMouseDown(float x, float y, MouseButtonType type) override;
    void onMouseUp(float x, float y, MouseButtonType type) override;

    void onResize(int x, int y) override;
    void onReposition(int x, int y) override;
};
