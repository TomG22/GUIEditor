#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "GuiListener.h"
#include "Mesh.h"
#include "Rect.h"

class Window;

class Widget : public GuiListener {
public:
    Window* parentWindow;

    glm::vec4 bgColor;
    Mesh* bgMesh;
    int bgBevel;

    Rect* bgGeometry;

    int zIndex;

    float cursorX, cursorY;

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
    Widget* parentWidget;

    Widget(Window* window);

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

    void requestBGMeshCreation();
    void requestBGMeshUpdate();

    static Widget* hitTest(std::vector<Widget*> widgets, float x, float y);

    void setAbsTransform(glm::vec2 newBottomLeft, glm::vec2 newTopRight);
    void setRelPos(float relXOffset, float relYOffset);
    void setRelSize(float relWidth, float relHeight);

    void updateBGMesh();

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
