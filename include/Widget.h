#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "GuiListener.h"
#include "GuiState.h"
#include "Mesh.h"

class Widget : public GuiListener {
public:
    glm::vec2 topLeft;
    glm::vec2 topRight;
    glm::vec2 bottomRight;
    glm::vec2 bottomLeft;

    glm::vec4 bgColor;
    Mesh* bgMesh;

    float cursorX, cursorY;


    bool canMove;
    bool canResizeLeft;
    bool canResizeRight;
    bool canResizeBottom;
    bool canResizeTop;

    TransformState transformState;
    bool mouseDown;
    HoverState hoverState;

    float scalarTransformCache;
    glm::vec2 vec2TransformCache;
    glm::vec4 vec4TransformCache;

    std::vector<Widget*> subWidgets;

    Widget();

    bool onInside(float x, float y);
    bool onTopLeft(float x, float y);
    bool onTopRight(float x, float y);
    bool onBottomRight(float x, float y);
    bool onBottomLeft(float x, float y);
    bool onTop(float x, float y);
    bool onRight(float x, float y);
    bool onBottom(float x, float y);
    bool onLeft(float x, float y);

    void updateHoverState(float x, float y);

    void updateTransformState(float x, float y);

    void applyTransform(float x, float y, float dx, float dy);

    void createBackground();

    void setSize(glm::vec2 newBottomLeft, glm::vec2 newTopRight);

    void updateGeometry();

    void addSubWidget(Widget* widget);

    void onKey(int key, int scancode, int action, int mods) override;

    void onMouseMove(float x, float y) override;

    void onMouseEnter() override;
    void onMouseLeave() override;

    void onMouseDownRight(float x, float y, int mods) override;
    void onMouseUpRight(float x,float y, int mods) override;

    void onMouseDownLeft(float x, float y, int mods) override;
    void onMouseUpLeft(float x, float y, int mods) override;

    void onMouseDownMiddle(float x, float y, int mods) override;
    void onMouseUpMiddle(float x, float y, int mods) override;
};
