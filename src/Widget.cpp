#include <iostream>
#include <stdexcept>
#include <vector>

#include "Widget.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Window.h"

Widget::Widget(Window* window)
    : parentWindow(window),
      bgColor(1.0f),
      bgMesh(nullptr),
      cursorX(0.0f),
      cursorY(0.0f),
      hoverState(RectPos::None),
      hoverTips(true),
      lockZIndex(true),
      transformState(TransformState::Idle),
      scalarTransformCache(0.0f),
      vec2TransformCache(0.0f),
      vec4TransformCache(0.0f),
      parentWidget(nullptr)
{
    setResizable();
    setMoveable();

    assert(parentWindow != nullptr);
    bgGeometry = new Rect(parentWindow->width, parentWindow->height);
}

void Widget::requestBGMeshCreation() {
    Window* window = parentWindow;
    Widget* self = this;

    window->postToRenderThread([window, self]() {
        window->createMeshForWidget(self);
    });
}

void Widget::requestBGMeshUpdate() {
    Window* window = parentWindow;
    Widget* self = this;

    window->postToRenderThread([window, self]() {
        window->updateMeshForWidget(self);
    });
}

void Widget::setAbsTransform(glm::vec2 newBottomLeft, glm::vec2 newTopRight) {
    bgGeometry->setAbsTransform(newBottomLeft, newTopRight);

    requestBGMeshUpdate();

    if (bgMesh != nullptr) {
        requestBGMeshUpdate();
    }

    updateHoverState(cursorX, cursorY);
}

void Widget::setRelPos(float relXOffset, float relYOffset) {
    bgGeometry->setRelPos(relXOffset, relYOffset, parentWindow->width, parentWindow->height);

    if (bgMesh != nullptr) {
        requestBGMeshUpdate();
    }

    updateHoverState(cursorX, cursorY);
}

void Widget::setRelSize(float relWidth, float relHeight) {
    bgGeometry->setRelSize(relWidth, relHeight, parentWindow->width, parentWindow->height);

    if (bgMesh != nullptr) {
        requestBGMeshUpdate();
    }

    updateHoverState(cursorX, cursorY);
}

void Widget::setResizable() {
    regMouseHover = true;
    regMouseEnter = true;
    regMouseLeave = true;
    regMouseDown = true;
    regMouseUp = true;

    canResizeLeft = true;
    canResizeRight = true;
    canResizeBottom = true;
    canResizeTop = true;
}

void Widget::setResizable(std::vector<RectPos> exclusions) {
    regMouseHover = true;
    regMouseEnter = true;
    regMouseLeave = true;
    regMouseDown = true;
    regMouseUp = true;

    for (RectPos exclusion : exclusions) {
        switch (exclusion) {
            case None:
                break;
            case Inside:
                break;
            case TopLeft:
                canResizeTop = false;
                canResizeLeft = false;
                break;
            case TopRight:
                canResizeTop = false;
                canResizeRight = false;
                break;
            case BottomRight:
                canResizeBottom = false;
                canResizeRight = false;
                break;
            case BottomLeft:
                canResizeBottom = false;
                canResizeLeft = false;
                break;
            case Top:
                canResizeTop = false;
                break;
            case Right:
                canResizeRight = false;
                break;
            case Bottom:
                canResizeBottom = false;
                break;
            case Left:
                canResizeLeft = false;
                break;
        }
    }
}

void Widget::setNotResizable() {
    regMouseHover = false;
    regMouseEnter = false;
    regMouseLeave = false;
    regMouseDown = false;
    regMouseUp = false;

    canResizeLeft = false;
    canResizeRight = false;
    canResizeBottom = false;
    canResizeTop = false;
}

void Widget::setNotResizable(std::vector<RectPos> exclusions) {
    if (exclusions.empty()) {
        regMouseHover = false;
        regMouseEnter = false;
        regMouseLeave = false;
        regMouseDown = false;
        regMouseUp = false;
    }

    for (RectPos exclusion : exclusions) {
        switch (exclusion) {
            case None:
                break;
            case Inside:
                break;
            case TopLeft:
                canResizeTop = true;
                canResizeLeft = true;
                break;
            case TopRight:
                canResizeTop = true;
                canResizeRight = true;
                break;
            case BottomRight:
                canResizeBottom = true;
                canResizeRight = true;
                break;
            case BottomLeft:
                canResizeBottom = true;
                canResizeLeft = true;
                break;
            case Top:
                canResizeTop = true;
                break;
            case Right:
                canResizeRight = true;
                break;
            case Bottom:
                canResizeBottom = true;
                break;
            case Left:
                canResizeLeft = true;
                break;
        }
    }
}

void Widget::setMoveable() {
    regMouseHover = true;
    regMouseEnter = true;
    regMouseLeave = true;
    regMouseDown = true;
    regMouseUp = true;

    canMove = true;
}

void Widget::setNotMoveable() {
    if (!canResizeTop && !canResizeLeft && !canResizeRight && !canResizeBottom) {
        regMouseHover = false;
        regMouseEnter = false;
        regMouseLeave = false;
        regMouseDown = false;
        regMouseUp = false;
    }

    canMove = false;
}


void Widget::updateTransformState(float x, float y) {
    if (bgGeometry->inTopLeft(x, y) && canResizeTop && canResizeLeft) {
        transformState = TransformState::ResizeTopLeft;
        vec2TransformCache = bgGeometry->topLeft;
    }
    else if (bgGeometry->inTopRight(x, y) && canResizeTop && canResizeRight) {
        transformState = TransformState::ResizeTopRight;
        vec2TransformCache = bgGeometry->topRight;
    }
    else if (bgGeometry->inBottomRight(x, y) && canResizeBottom && canResizeRight) {
        transformState = TransformState::ResizeBottomRight;

        vec2TransformCache = bgGeometry->bottomRight;
    }
    else if (bgGeometry->inBottomLeft(x, y) && canResizeBottom && canResizeLeft) {
        transformState = TransformState::ResizeBottomLeft;
        vec2TransformCache = bgGeometry->bottomLeft;
    }
    else if (bgGeometry->inTop(y) && canResizeTop) {
        transformState = TransformState::ResizeTop;
        scalarTransformCache = bgGeometry->topLeft.y;
    }
    else if (bgGeometry->inRight(x) && canResizeRight) {
        transformState = TransformState::ResizeRight;
        scalarTransformCache = bgGeometry->topRight.x;
    }
    else if (bgGeometry->inBottom(y) && canResizeBottom) {
        transformState = TransformState::ResizeBottom;
        scalarTransformCache = bgGeometry->bottomRight.y;
    }
    else if (bgGeometry->inLeft(x) && canResizeLeft) {
        transformState = TransformState::ResizeLeft;
        scalarTransformCache = bgGeometry->bottomLeft.x;
    }
    else if (bgGeometry->inInside(x, y) && canMove) {
        transformState = TransformState::Move;
        vec4TransformCache = glm::vec4(bgGeometry->bottomLeft.x,
                                       bgGeometry->bottomLeft.y,
                                       bgGeometry->topRight.x,
                                       bgGeometry->topRight.y);
    } else {
        transformState = TransformState::Idle;
    }
}

void Widget::showHoverTips() {
    hoverTips = true;
    updateHoverState(cursorX, cursorY);
}

void Widget::hideHoverTips() {
    hoverTips = false;
    updateHoverState(cursorX, cursorY);
}

void Widget::updateHoverState(float x, float y) {
    RectPos prevRectPos = hoverState;

    if (!hoverTips) {
        return;
    }

    if (bgGeometry->inTopLeft(x, y) && canResizeTop && canResizeLeft) {
        hoverState = RectPos::TopLeft;
    }
    else if (bgGeometry->inTopRight(x, y) && canResizeTop && canResizeRight) {
        hoverState = RectPos::TopRight;
    }
    else if (bgGeometry->inBottomRight(x, y) && canResizeBottom && canResizeRight) {
        hoverState = RectPos::BottomRight;
    }
    else if (bgGeometry->inBottomLeft(x, y) && canResizeBottom && canResizeLeft) {
        hoverState = RectPos::BottomLeft;
    }
    else if (bgGeometry->inTop(y) && canResizeTop) {
        hoverState = RectPos::Top;
    }
    else if (bgGeometry->inRight(x) && canResizeRight) {
        hoverState = RectPos::Right;
    }
    else if (bgGeometry->inBottom(y) && canResizeBottom) {
        hoverState = RectPos::Bottom;
    }
    else if (bgGeometry->inLeft(x) && canResizeLeft) {
        hoverState = RectPos::Left;
    }
    else if (bgGeometry->inInside(x, y) && canMove) {
        hoverState = RectPos::Inside;
    }
    else {
        hoverState = RectPos::None;
    }
}

void Widget::onKeyUp(KeyName key, std::vector<ModKeyName> mods) {}
void Widget::onKeyDown(KeyName key, std::vector<ModKeyName> mods) {}

void Widget::onMouseHover(float x, float y) {
    printf("mouse hovered on widget\n");

    float dx = x - cursorX;
    float dy = y - cursorY;

    bgGeometry->applyTransform(transformState, x, y, dx, dy);

    updateHoverState(x, y);

    requestBGMeshUpdate();

    for (GuiListener* listener : listeners) {
        if (listener->regMouseHover) {
            listener->onMouseHover(x, y);
        }
    }

    cursorX = x;
    cursorY = y;
}

void Widget::onMouseEnter() {
    printf("mouse entered widget\n");

    for (GuiListener* listener : listeners) {
        if (listener->regMouseEnter) {
            listener->onMouseEnter();
        }
    }
}

void Widget::onMouseLeave() {
    printf("mouse left widget\n");

    hoverState = RectPos::None;

    for (GuiListener* listener : listeners) {
        if (listener->regMouseLeave) {
            listener->onMouseLeave();
        }
    }
}

void Widget::onMouseDown(float x, float y, MouseButtonType type) {
    switch (type) {
        case MouseButtonType::MouseLeft:
            printf("mouse left down window (%f, %f)\n", x, y);

            updateTransformState(x, y);

            if (bgGeometry->inInside(x, y)) {
                for (GuiListener* listener : listeners) {
                    listener->onMouseDown(x, y, type);
                }
            }
            break;
        case MouseButtonType::MouseRight:
            printf("mouse right down window (%f, %f)\n", x, y);

            for (GuiListener* listener : listeners) {
                listener->onMouseDown(x, y, type);
            }
            break;
        default:
            printf("unhandled mouse down\n");
    }

    // save the mouse-down target somewhere for later use in mouse up

    cursorX = x;
    cursorY = y;
}

void Widget::onMouseUp(float x, float y, MouseButtonType type) {
    switch (type) {
        case MouseButtonType::MouseLeft:
            printf("mouse up left (%f, %f)\n", x, y);

            transformState = TransformState::Idle;

            for (GuiListener* listener : listeners) {
                listener->onMouseUp(x, y, type);
            }
            break;
        case MouseButtonType::MouseRight:
            printf("mouse up right (%f, %f)\n", x, y);

            for (GuiListener* listener : listeners) {
                listener->onMouseUp(x, y, type);
            }
            break;
        default:
            printf("unhandled mouse up\n");
    }

    cursorX = x;
    cursorY = y;
}

void Widget::onResize(int width, int height) {
    for (GuiListener* listener : listeners) {
        if (listener->regResize) {
            listener->onResize(width, height);
        }
    }
}

Widget* Widget::makeSubWidget() {
    Widget* widget = new Widget(this->parentWindow);
    subWidgets.push_back(widget);
    return widget;
}

Widget* Widget::hitTest(const std::vector<Widget*>& widgets, float x, float y) {
    for (auto it = widgets.rbegin(); it != widgets.rend(); ++it) {
        Widget* widget = *it;
        if (widget->bgGeometry->inInside(x, y)) {
            if (widget->subWidgets.empty()) {
                return widget;
            } else {
                Widget* hitChild = widget->hitTest(widget->subWidgets, x, y);
                if (hitChild) {
                    return hitChild;
                } else {
                    return widget;
                }
            }
        }
    }
    return nullptr;
}
