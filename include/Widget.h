#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "Transform.h"
#include "Mesh.h"
#include "GuiListener.h"

class Widget : public GuiListener {
public:
    glm::vec2 topLeft;
    glm::vec2 topRight;
    glm::vec2 bottomRight;
    glm::vec2 bottomLeft;

    glm::vec4 bgColor;
    Mesh* bgMesh;

    float cursorX, cursorY;

    bool isHovering;
    bool isResizable;
    bool isDraggable;
    TransformState transformState;
    float scalarTransformCache;
    glm::vec2 vec2TransformCache;
    glm::vec4 vec4TransformCache;

    std::vector<Widget*> subWidgets;

    Widget();

    void setSize(glm::vec2 bottomLeft, glm::vec2 topRight);

    void createBackground();

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
