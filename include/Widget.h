#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "GuiListener.h"
#include "GuiTypes.h"
#include "Mesh.h"
#include "Layout.h"
#include "Shader.h"

class Window;

class Widget : public GuiListener {
public:
    std::vector<Widget*> subWidgets;

    Layout& windowLayout;
    Layout layout;
    Layout* boundParentLayout = nullptr;

    Mesh* bgMesh = nullptr;
    Shader* bgShader = nullptr;
    glm::vec4 bgColor;

    int zIndex = 0;
    bool lockZIndex = true;

    TransformType transformState = TransformType::IDLE;
    bool canMove = false;
    bool canResizeTop = false;
    bool canResizeLeft = false;
    bool canResizeBottom = false;
    bool canResizeRight = false;

    bool hoverTips = false;
    TransformType hoverState = TransformType::IDLE;

    float cursorX = 0.0f, cursorY = 0.0f;

    Widget(Layout& windowLayout);

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


    // Background methods
    void bindParentLayout(Layout* newParentLayout);
    void unbindParentLayout();
    void markChildrenDirty();

    void setXPos(float x);
    void setYPos(float y);
    void setPos(float x, float y);
    void setWidth(float w);
    void setHeight(float h);
    void setSize(float w, float h);

    void setAbsXPos(float x);
    void setAbsYPos(float y);
    void setAbsPos(float x, float y);
    void setAbsWidth(float w);
    void setAbsHeight(float h);
    void setAbsSize(float w, float h);
    //void setCornerRadii(float radius);
    static Widget* hitTest(const std::vector<Widget*>& widgets, float x, float y);
    void applyTransform(TransformType transformState, float x, float y, float dx, float dy);

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
