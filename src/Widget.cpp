#include <iostream>

#include "Widget.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Window.h"

Widget::Widget(Window* window)
    : width(static_cast<int>(window->width / 2)),
      height(static_cast<int>(window->height / 2)),
      topLeft(0.0f),
      topRight(0.0f),
      bottomRight(0.0f),
      bottomLeft(0.0f),
      bgColor(1.0f),
      bgMesh(nullptr),
      cursorX(0.0f),
      cursorY(0.0f),
      hitTol(5.0f),
      hoverState(RectPos::None),
      hoverTips(true),
      transformState(TransformState::Idle),
      scalarTransformCache(0.0f),
      vec2TransformCache(0.0f),
      vec4TransformCache(0.0f),
      parentWindow(window),
      parentWidget(nullptr)
{
    setResizable();
    setMoveable();
}

void Widget::createBackground() {
    Vertex2D* vertices = new Vertex2D[4] {
        {bottomLeft,     bgColor},
        {bottomRight,    bgColor},
        {topRight,       bgColor},
        {topLeft,        bgColor}
    };

    unsigned int* indices = new unsigned int[6] {
        0, 1, 2,
        2, 3, 0
    };

    try {
        VertexArray* va = new VertexArray();
        VertexBuffer* vb = new VertexBuffer(vertices, sizeof(Vertex2D) * 4);

        VertexBufferLayout* layout = new VertexBufferLayout();
        layout->Push<Vertex2D>(1);

        va->Bind();
        vb->Bind();
        va->AddBuffer(*vb, *layout);

        IndexBuffer* ib = new IndexBuffer(indices, 6);

        bgMesh = new Mesh(va, vb, ib);

    } catch (const std::runtime_error& e) {
        std::cout << "Mesh ERROR: " << e.what() << std::endl;
        std::exit(1);
    }
}

Widget* Widget::makeSubWidget() {
    Widget* widget = new Widget(this->parentWindow);
    subWidgets.push_back(widget);
    return widget;
}

Widget* Widget::hitTest(std::vector<Widget*> widgets, float x, float y) {
    Widget* hitWidget = nullptr;

    for (Widget* widget : widgets) {
        if ((!hitWidget && widget->inInside(x, y)) ||
            (hitWidget && widget->inInside(x, y) &&
             widget->zIndex > hitWidget->zIndex)) {
            hitWidget = widget;
        }
    }

    if (hitWidget == nullptr) {
        return nullptr;
    }

    if (hitWidget->subWidgets.empty()) {
        return hitWidget;
    }

    return hitWidget->hitTest(hitWidget->subWidgets, x, y);
}

void Widget::setAbsTransform(glm::vec2 newBottomLeft, glm::vec2 newTopRight) {
    topLeft = {newBottomLeft.x, newTopRight.y};
    topRight = newTopRight;
    bottomRight = {newTopRight.x, newBottomLeft.y};
    bottomLeft = newBottomLeft;

    if (bgMesh != nullptr) {
        updateGeometry();
    }

    updateHoverState(cursorX, cursorY);
}

void Widget::setRelPos(float relXOffset, float relYOffset) {
    xOffset = static_cast<int>(parentWindow->width * relXOffset);
    yOffset = static_cast<int>(parentWindow->height * relYOffset);

    topLeft = {xOffset - width / 2, yOffset + height / 2};
    topRight = {xOffset + width / 2, yOffset + height / 2};
    bottomRight = {xOffset + width / 2, yOffset - height / 2};
    bottomLeft = {xOffset - width / 2, yOffset - height / 2};

    if (bgMesh != nullptr) {
        updateGeometry();
    }

    updateHoverState(cursorX, cursorY);
}

void Widget::setRelSize(float relWidth, float relHeight) {
    width = static_cast<int>(relWidth * parentWindow->width);
    height = static_cast<int>(relWidth * parentWindow->height);

    topLeft = {xOffset - width / 2, yOffset + height / 2};
    topRight = {xOffset + width / 2, yOffset + height / 2};
    bottomRight = {xOffset + width / 2, yOffset - height / 2};
    bottomLeft = {xOffset - width / 2, yOffset - height / 2};

    if (bgMesh != nullptr) {
        updateGeometry();
    }

    updateHoverState(cursorX, cursorY);
}

void Widget::updateGeometry() {
     Vertex2D* vertices = new Vertex2D[4] {
        {bottomLeft,     bgColor},
        {bottomRight,    bgColor},
        {topRight,       bgColor},
        {topLeft,        bgColor}
    };

    bgMesh->UpdateVertices(vertices, sizeof(Vertex2D) * 4, 0);
}

bool Widget::eqWithTol(float a, float b) {
    return std::abs(a - b) <= hitTol;
}

bool Widget::inInside(float x, float y) {
    return x >= bottomLeft.x - hitTol && x <= topRight.x + hitTol &&
           y >= bottomLeft.y - hitTol && y <= topRight.y + hitTol;
}

bool Widget::inTopLeft(float x, float y) {
    return eqWithTol(x, topLeft.x) && eqWithTol(y, topLeft.y);
}

bool Widget::inTopRight(float x, float y) {
    return eqWithTol(x, topRight.x) && eqWithTol(y, topRight.y);
}

bool Widget::inBottomRight(float x, float y) {
    return eqWithTol(x, bottomRight.x) && eqWithTol(y, bottomRight.y);
}

bool Widget::inBottomLeft(float x, float y) {
    return eqWithTol(x, bottomLeft.x) && eqWithTol(y, bottomLeft.y);
}

bool Widget::inTop(float x, float y) {
    return eqWithTol(y, topLeft.y);
}

bool Widget::inRight(float x, float y) {
    return eqWithTol(x, topRight.x);
}

bool Widget::inBottom(float x, float y) {
    return eqWithTol(y, bottomRight.y);
}

bool Widget::inLeft(float x, float y) {
    return eqWithTol(x, bottomLeft.x);
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



void Widget::applyTransform(float x, float y, float dx, float dy) {
    switch (transformState) {
        case TransformState::Idle:
            break;

        case TransformState::Move:
            topLeft.x += dx;
            topLeft.y += dy;
            topRight.x += dx;
            topRight.y += dy;
            bottomRight.x += dx;
            bottomRight.y += dy;
            bottomLeft.x += dx;
            bottomLeft.y += dy;
            break;

        case TransformState::ResizeTop:
            topLeft.y = y;
            topRight.y = y;
            break;
        case TransformState::ResizeRight:
            topRight.x = x;
            bottomRight.x = x;
            break;
        case TransformState::ResizeBottom:
            bottomLeft.y = y;
            bottomRight.y = y;
            break;
        case TransformState::ResizeLeft:
            topLeft.x = x;
            bottomLeft.x = x;
            break;

        case TransformState::ResizeTopLeft:
            topLeft.x = x;
            topLeft.y = y;
            bottomLeft.x = x;
            topRight.y = y;
            break;
        case TransformState::ResizeTopRight:
            topRight.x = x;
            topRight.y = y;
            topLeft.y = y;
            bottomRight.x = x;
            break;
        case TransformState::ResizeBottomRight:
            bottomRight.x = x;
            bottomRight.y = y;
            topRight.x = x;
            bottomLeft.y = y;
            break;
        case TransformState::ResizeBottomLeft:
            bottomLeft.x = x;
            bottomLeft.y = y;
            bottomRight.y = y;
            topLeft.x = x;
            break;
    }
}

void Widget::updateTransformState(float x, float y) {
    if (inTopLeft(x, y) && canResizeTop && canResizeLeft) {
        transformState = TransformState::ResizeTopLeft;
        vec2TransformCache = topLeft;
    }
    else if (inTopRight(x, y) && canResizeTop && canResizeRight) {
        transformState = TransformState::ResizeTopRight;
        vec2TransformCache = topRight;
    }
    else if (inBottomRight(x, y) && canResizeBottom && canResizeRight) {
        transformState = TransformState::ResizeBottomRight;
        vec2TransformCache = bottomRight;
    }
    else if (inBottomLeft(x, y) && canResizeBottom && canResizeLeft) {
        transformState = TransformState::ResizeBottomLeft;
        vec2TransformCache = bottomRight;
    }
    else if (inTop(x, y) && canResizeTop) {
        transformState = TransformState::ResizeTop;
        scalarTransformCache = topLeft.y;
    }
    else if (inRight(x, y) && canResizeRight) {
        transformState = TransformState::ResizeRight;
        scalarTransformCache = topRight.x;
    }
    else if (inBottom(x, y) && canResizeBottom) {
        transformState = TransformState::ResizeBottom;
        scalarTransformCache = bottomRight.y;
    }
    else if (inLeft(x, y) && canResizeLeft) {
        transformState = TransformState::ResizeLeft;
        scalarTransformCache = bottomLeft.x;
    }
    else if (inInside(x, y) && canMove) {
        transformState = TransformState::Move;
        vec4TransformCache = glm::vec4(bottomLeft.x, bottomLeft.y,
                                       topRight.x, topRight.y);
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

    if (inTopLeft(x, y) && canResizeTop && canResizeLeft) {
        hoverState = RectPos::TopLeft;
    }
    else if (inTopRight(x, y) && canResizeTop && canResizeRight) {
        hoverState = RectPos::TopRight;
    }
    else if (inBottomRight(x, y) && canResizeBottom && canResizeRight) {
        hoverState = RectPos::BottomRight;
    }
    else if (inBottomLeft(x, y) && canResizeBottom && canResizeLeft) {
        hoverState = RectPos::BottomLeft;
    }
    else if (inTop(x, y) && canResizeTop) {
        hoverState = RectPos::Top;
    }
    else if (inRight(x, y) && canResizeRight) {
        hoverState = RectPos::Right;
    }
    else if (inBottom(x, y) && canResizeBottom) {
        hoverState = RectPos::Bottom;
    }
    else if (inLeft(x, y) && canResizeLeft) {
        hoverState = RectPos::Left;
    }
    else if (inInside(x, y) && canMove) {
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

    applyTransform(x, y, dx, dy);

    updateHoverState(x, y);

    updateGeometry();

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

            if (inInside(x, y)) {
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
            printf("Unhandled mouse down\n");
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
            printf("Unhandled mouse up\n");
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
