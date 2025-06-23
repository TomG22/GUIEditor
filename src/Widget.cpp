#include <iostream>

#include "Widget.h"
#include "VertexArray.h"
#include "IndexBuffer.h"

bool eqWithTol(float a, float b) {
    return std::abs(a - b) <= 5.0f;
}

bool Widget::onInside(float x, float y) {
    return x >= bottomLeft.x && x <= topRight.x &&
           y >= bottomLeft.y && y <= topRight.y;
}

bool Widget::onTopLeft(float x, float y) {
    return eqWithTol(x, topLeft.x) && eqWithTol(y, topLeft.y);
}

bool Widget::onTopRight(float x, float y) {
    return eqWithTol(x, topRight.x) && eqWithTol(y, topRight.y);
}

bool Widget::onBottomRight(float x, float y) {
    return eqWithTol(x, bottomRight.x) && eqWithTol(y, bottomRight.y);
}

bool Widget::onBottomLeft(float x, float y) {
    return eqWithTol(x, bottomLeft.x) && eqWithTol(y, bottomLeft.y);
}

bool Widget::onTop(float x, float y) {
    return eqWithTol(y, topLeft.y);
}

bool Widget::onRight(float x, float y) {
    return eqWithTol(x, topRight.x);
}

bool Widget::onBottom(float x, float y) {
    return eqWithTol(y, bottomRight.y);
}

bool Widget::onLeft(float x, float y) {
    return eqWithTol(x, bottomLeft.x);
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
    if (onTopLeft(x, y)) {
        transformState = TransformState::ResizeTopLeft;
        vec2TransformCache = topLeft;
    }
    else if (onTopRight(x, y)) {
        transformState = TransformState::ResizeTopRight;
        vec2TransformCache = topRight;
    }
    else if (onBottomRight(x, y)) {
        transformState = TransformState::ResizeBottomRight;
        vec2TransformCache = bottomRight;
    }
    else if (onBottomLeft(x, y)) {
        transformState = TransformState::ResizeBottomLeft;
        vec2TransformCache = bottomRight;
    }
    else if (onTop(x, y)) {
        transformState = TransformState::ResizeTop;
        scalarTransformCache = topLeft.y;
    }
    else if (onRight(x, y)) {
        transformState = TransformState::ResizeRight;
        scalarTransformCache = topRight.x;
    }
    else if (onBottom(x, y)) {
        transformState = TransformState::ResizeBottom;
        scalarTransformCache = bottomRight.y;
    }
    else if (onLeft(x, y)) {
        transformState = TransformState::ResizeLeft;
        scalarTransformCache = bottomLeft.x;
    }
    else if (onInside(x, y)) {
        transformState = TransformState::Move;
        vec4TransformCache = glm::vec4(bottomLeft.x, bottomLeft.y,
                                       topRight.x, topRight.y);
    }
}

void Widget::updateHoverState(float x, float y) {
    HoverState prevHoverState = hoverState;

    if (onTopLeft(x, y)) {
        hoverState = HoverState::TopLeft;
    }
    else if (onTopRight(x, y)) {
        hoverState = HoverState::TopRight;
    }
    else if (onBottomRight(x, y)) {
        hoverState = HoverState::BottomRight;
    }
    else if (onBottomLeft(x, y)) {
        hoverState = HoverState::BottomLeft;
    }
    else if (onTop(x, y)) {
        hoverState = HoverState::Top;
    }
    else if (onRight(x, y)) {
        hoverState = HoverState::Right;
    }
    else if (onBottom(x, y)) {
        hoverState = HoverState::Bottom;
    }
    else if (onLeft(x, y)) {
        hoverState = HoverState::Left;
    }
    else if (onInside(x, y)) {
        hoverState = HoverState::Inside;
    }
    else {
        hoverState = HoverState::None;
    }

    if (prevHoverState == HoverState::None && hoverState != HoverState::None) {
        onMouseEnter();
    }
    else if (prevHoverState != HoverState::None &&
             hoverState == HoverState::None) {
        onMouseLeave();
    }

}


Widget::Widget()
    : topLeft(0.0f),
      topRight(0.0f),
      bottomRight(0.0f),
      bottomLeft(0.0f),
      bgColor(1.0f),
      bgMesh(nullptr),
      cursorX(0.0f),
      cursorY(0.0f),
      canMove(true),
      canResizeLeft(true),
      canResizeRight(true),
      canResizeBottom(true),
      canResizeTop(true),
      transformState(TransformState::Idle),
      scalarTransformCache(0.0f),
      vec2TransformCache(0.0f),
      vec4TransformCache(0.0f)
{}

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
        // Allocate all objects on heap so they survive
        VertexArray* va = new VertexArray();
        VertexBuffer* vb = new VertexBuffer(vertices, sizeof(Vertex2D) * 4);

        VertexBufferLayout* layout = new VertexBufferLayout();
        layout->Push<Vertex2D>(1);  // or whatever your layout needs

        va->Bind();
        vb->Bind();
        va->AddBuffer(*vb, *layout);

        IndexBuffer* ib = new IndexBuffer(indices, 6);

        // Leak them for now — you're just checking GL state integrity
        bgMesh = new Mesh(va, vb, ib);

    } catch (const std::runtime_error& e) {
        std::cout << "Mesh ERROR: " << e.what() << std::endl;
        std::exit(1);
    }
}

void Widget::addSubWidget(Widget* widget) {
    subWidgets.push_back(widget);
    listeners.push_back(widget);
}

void Widget::setSize(glm::vec2 newBottomLeft, glm::vec2 newTopRight) {
    topLeft = {newBottomLeft.x, newTopRight.y};
    topRight = newTopRight;
    bottomRight = {newTopRight.x, newBottomLeft.y};
    bottomLeft = newBottomLeft;

    if (bgMesh != nullptr) {
        updateGeometry();
    }
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

void Widget::onKey(int key, int scancode, int action, int mods) {
    /*
    for (GuiListener* listener : listeners) {
        listener->onKey(key, scancode, action, mods);
    }
    */
}

void Widget::onMouseMove(float x, float y) {
    printf("moved on window (%f, %f)\n", x, y);
    float dx = x - cursorX;
    float dy = y - cursorY;

    applyTransform(x, y, dx, dy);

    updateHoverState(x, y);

    updateGeometry();

    // If not hovering, send the signal to the widget's children
    if (hoverState == HoverState::None) {
        for (GuiListener* listener : listeners) {
            listener->onMouseMove(x, y);
        }
    }

    cursorX = x;
    cursorY = y;
}

void Widget::onMouseEnter() {
    printf("mouse ENTERED widget\n");

    for (GuiListener* listener : listeners) {
            listener->onMouseEnter();
    }
}

void Widget::onMouseLeave() {
    printf("mouse LEFT widget\n");

    for (GuiListener* listener : listeners) {
            listener->onMouseLeave();
    }
}

void Widget::onMouseDownLeft(float x, float y, int mods) {
    printf("mouse down window (%f, %f)\n", x, y);

    updateTransformState(x, y);

    if (onInside(x, y)) {
        for (GuiListener* listener : listeners) {
            listener->onMouseDownLeft(x, y, mods);
        }
    }

    cursorX = x;
    cursorY = y;
}

void Widget::onMouseUpLeft(float x, float y, int mods) {
    printf("mouse up window (%f, %f)\n", x, y);
    transformState = TransformState::Idle;

    for (GuiListener* listener : listeners) {
        listener->onMouseUpRight(x, y, mods);
    }

    cursorX = x;
    cursorY = y;
}

void Widget::onMouseDownRight(float x, float y, int mods) {}
void Widget::onMouseUpRight(float x, float y, int mods) {}

void Widget::onMouseDownMiddle(float x, float y, int mods) {}
void Widget::onMouseUpMiddle(float x, float y, int mods) {}
