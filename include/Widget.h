#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <unordered_map>

#include "GuiListener.h"
#include "GuiTypes.h"
#include "Mesh.h"
#include "Rect.h"
#include "Shader.h"

class Window;

class Widget : public GuiListener {
public:
    std::vector<Widget*> subWidgets;

    Rect& windowLayout;
    Rect* layout;
    int zIndex;
    bool lockZIndex;

    Mesh* bgMesh;

    Shader* bgShader;
    glm::vec4 bgColor;

    TransformType transformState;
    bool canMove;
    bool canResizeTop;
    bool canResizeLeft;
    bool canResizeBottom;
    bool canResizeRight;

    bool hoverTips;
    TransformType hoverState;

    float cursorX, cursorY;

    Widget(Rect& windowLayout);

    // Internal event handlers
    void handleKeyDown(KeyName key, std::vector<ModKeyName> mods) override;
    void handleKeyUp(KeyName key, std::vector<ModKeyName> mods) override;

    void handleMouseMove(float x, float y) override;
    void handleMouseHover(float x, float y) override;
    void handleMouseEnter() override;
    void handleMouseLeave() override;
    void handleMouseDown(float x, float y, MouseButtonType type) override;
    void handleMouseUp(float x, float y, MouseButtonType type) override;

    Widget* makeSubWidget();

    static Widget* hitTest(const std::vector<Widget*>& widgets, float x, float y);

    // Background methods
    void setPos(float x, float y);
    void setSize(float width, float height);
    void setCornerRadius(float radius);

    void updateBGMesh();
    void updateBGShader();
    void updateBackground();

    void setResizable();
    void setNonResizable();
    void setMoveable();
    void setNonMoveable();

    TransformType getCursorState();

    void setTransformStates(std::vector<TransformType> transformTypes, bool state);
    void updateTransformState();

    void showHoverTips();
    void hideHoverTips();
    void updateHoverState();
};
