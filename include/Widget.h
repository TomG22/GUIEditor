#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "GuiListener.h"
#include "Mesh.h"

class Window;

class Widget : public GuiListener {
public:
    int width;
    int height;

    int xOffset;
    int yOffset;

    glm::vec2 topLeft;
    glm::vec2 topRight;
    glm::vec2 bottomRight;
    glm::vec2 bottomLeft;

    glm::vec4 bgColor;
    Mesh* bgMesh;
    int bgBevel;

    int zIndex;

    float cursorX, cursorY;
    float hitTol;

    bool canMove;
    bool canResizeLeft;
    bool canResizeRight;
    bool canResizeBottom;
    bool canResizeTop;

    TransformState transformState;
    RectPos hoverState;
    bool hoverTips;

    float scalarTransformCache;
    glm::vec2 vec2TransformCache;
    glm::vec4 vec4TransformCache;

    std::vector<Widget*> subWidgets;
    Window* parentWindow;
    Widget* parentWidget;

    Widget(Window* window);

    bool eqWithTol(float a, float b);
    bool inInside(float x, float y);
    bool inTopLeft(float x, float y);
    bool inTopRight(float x, float y);
    bool inBottomRight(float x, float y);
    bool inBottomLeft(float x, float y);
    bool inTop(float x, float y);
    bool inRight(float x, float y);
    bool inBottom(float x, float y);
    bool inLeft(float x, float y);

    void setResizable();
    void setResizable(std::vector<RectPos> exclusions);
    void setNotResizable();
    void setNotResizable(std::vector<RectPos> exclusions);

    void setMoveable();
    void setNotMoveable();

    void showHoverTips();
    void hideHoverTips();
    void updateHoverState(float x, float y);

    void updateTransformState(float x, float y);

    void applyTransform(float x, float y, float dx, float dy);

    void createBackground();

    static Widget* hitTest(std::vector<Widget*> widgets, float x, float y);

    void setAbsTransform(glm::vec2 newBottomLeft, glm::vec2 newTopRight);
    void setRelPos(float relXOffset, float relYOffset);
    void setRelSize(float relWidth, float relHeight);

    void updateGeometry();

    Widget* makeSubWidget();

    void onKeyUp(KeyName key, std::vector<ModKeyName> mods) override;
    void onKeyDown(KeyName key, std::vector<ModKeyName> mods) override;

    void onMouseMove(float x, float y) override {};
    void onMouseHover(float x, float y) override;
    void onMouseEnter() override;
    void onMouseLeave() override;
    void onMouseDown(float x, float y, MouseButtonType type) override;
    void onMouseUp(float x, float y, MouseButtonType type) override;

    void onResize(int width, int height) override;
};
