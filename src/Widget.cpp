#include <iostream>

#include "Widget.h"
#include "VertexArray.h"
#include "IndexBuffer.h"

Widget::Widget()
    : topLeft(0.0f),
      topRight(0.0f),
      bottomRight(0.0f),
      bottomLeft(0.0f),
      bgColor(1.0f),
      bgMesh(nullptr),
      cursorX(0.0f),
      cursorY(0.0f),
      isHovering(false),
      isResizable(true),
      isDraggable(true),
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

    printf("isHovering: %d, (%f, %f)\n", isHovering, x, y);
    if (isHovering == false && x >= bottomLeft.x && x <= topRight.x &&
        y >= bottomLeft.y && y <= topRight.y) {
        onMouseEnter();

    } else if (isHovering == true && !(x >= bottomLeft.x && x <= topRight.x &&
        y >= bottomLeft.y && y <= topRight.y)) {
        onMouseLeave();
    }

    for (GuiListener* listener : listeners) {
        listener->onMouseMove(x, y);
    }

    updateGeometry();

    cursorX = x;
    cursorY = y;
}

void Widget::onMouseEnter() {
    printf("mouse ENTERED window\n");
    isHovering = true;

    for (GuiListener* listener : listeners) {
            listener->onMouseEnter();
    }
}

void Widget::onMouseLeave() {
    printf("mouse LEFT window\n");
    isHovering = false;

    for (GuiListener* listener : listeners) {
            listener->onMouseLeave();
    }
}

bool eqWithTol(float a, float b, float tolerance) {
    return std::abs(a - b) <= tolerance;
}

void Widget::onMouseDownLeft(float x, float y, int mods) {
    printf("mouse down window (%f, %f)\n", x, y);

    if (x > bottomLeft.x && x < topRight.x &&
        y > bottomLeft.y && y < topRight.y) {
        if (isDraggable) {
            transformState = TransformState::Move;
            vec4TransformCache = glm::vec4(bottomLeft.x, bottomLeft.y, topRight.x, topRight.y);
        }

        for (GuiListener* listener : listeners) {
            listener->onMouseDownRight(x, y, mods);
        }
    }

    cursorX = x;
    cursorY = y;

    if (isResizable && eqWithTol(x, topLeft.x, 5.0f) && eqWithTol(y, topLeft.y, 5.0f)) {
        transformState = TransformState::ResizeTopLeft;
        vec2TransformCache = topLeft;
        return;
    }

    if (isResizable && x == topRight.x && y == topRight.y) {
        transformState = TransformState::ResizeTopRight;
        vec2TransformCache = topRight;
        return;
    }

    if (isResizable && x == bottomRight.x && y == bottomRight.y) {
        transformState = TransformState::ResizeBottomRight;
        vec2TransformCache = bottomRight;
        return;
    }

    if (isResizable && x == bottomLeft.x && y == bottomLeft.y) {
        transformState = TransformState::ResizeBottomLeft;
        vec2TransformCache = bottomRight;
        return;
    }

    if (isResizable && y == topLeft.y) {
        transformState = TransformState::ResizeTop;
        scalarTransformCache = topLeft.y;
        return;
    }

    if (isResizable && x == topRight.x) {
        transformState = TransformState::ResizeRight;
        scalarTransformCache = topRight.x;
        return;
    }

    if (isResizable && y == bottomRight.y) {
        transformState = TransformState::ResizeBottom;
        scalarTransformCache = bottomRight.y;
        return;
    }

    if (isResizable && x == bottomLeft.x) {
        transformState = TransformState::ResizeLeft;
        scalarTransformCache = bottomLeft.x;
        return;
    }
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
