#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "Widget.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Window.h"

Widget::Widget(Rect& windowLayout)
    : bgGeometry(nullptr),
      zIndex(0),
      lockZIndex(true),
      bgMesh(nullptr),
      bgShader(nullptr),
      bgColor(1.0f),
      transformState(TransformType::IDLE),
      canMove(false),
      canResizeTop(false),
      canResizeLeft(false),
      canResizeBottom(false),
      canResizeRight(false),
      hoverTips(false),
      cursorX(0), cursorY(0),
      windowLayout(windowLayout)
{
    bgGeometry = new Rect();
    bgShader = new Shader("../res/shaders/2DVertexColor.shader");

    setResizable();
    setMoveable();

    updateBackground();
}

Widget* Widget::makeSubWidget() {
    Widget* widget = new Widget(windowLayout);
    subWidgets.push_back(widget);

    return widget;
}

Widget* Widget::hitTest(const std::vector<Widget*>& widgets, float x, float y) {
    for (auto it = widgets.rbegin(); it != widgets.rend(); ++it) {
        Widget* widget = *it;

        if (!widget->subWidgets.empty()) {
            if (Widget* child = hitTest(widget->subWidgets, x, y))
                return child;
        }

        if (widget->bgGeometry->inInside(x, y)) {
            return widget;
        }
    }
    return nullptr;
}

void Widget::setPos(float x, float y) {
    bgGeometry->setPos(x, y);
    
    updateBackground();
}

void Widget::setSize(float width, float height) {
    bgGeometry->setSize(width, height);

    updateBackground();
}

void Widget::setCornerRadius(float radius) {
    bgGeometry->setCornerRadius(radius);

    updateBackground();
}

void Widget::updateBGMesh() {
    if (!glfwGetCurrentContext()) {
        return;
    }

    // Pull the latest background geometry data to update the mesh with
    float left = bgGeometry->getXPos();
    float top = bgGeometry->getYPos();
    float right = left + bgGeometry->getWidth();
    float bottom = top + bgGeometry->getHeight();

    Vertex2D vertices[4] = {
        {{left, top}, bgColor, {0.0f, 1.0f}},
        {{right, top}, bgColor, {1.0f, 1.0f}},
        {{right, bottom}, bgColor, {1.0f, 0.0f}},
        {{left, bottom}, bgColor, {0.0f, 0.0f}}
    };

    // Make sure to initialize the background mesh if it hasn't been
    if (!bgMesh) {
        unsigned int indices[6] = {0,1,2, 2,3,0};

        VertexArray* va = new VertexArray();
        VertexBuffer* vb = new VertexBuffer(vertices, sizeof(Vertex2D) * 4);

        VertexBufferLayout* bgGeometry = new VertexBufferLayout();
        bgGeometry->Push<Vertex2D>(1);

        va->Bind();
        vb->Bind();
        va->AddBuffer(*vb, *bgGeometry);

        IndexBuffer* ib = new IndexBuffer(indices, 6);

        bgMesh = new Mesh(va, vb, ib);
    } else {
        bgMesh->UpdateVertices(vertices, sizeof(Vertex2D) * 4, 0);
    }
}

void Widget::updateBGShader() {
    if (!glfwGetCurrentContext()) {
        return;
    }

    bgShader->Bind();
    bgShader->SetUniform2f("u_TopLeftPos", bgGeometry->getXPos(),
                                           bgGeometry->getYPos());
    bgShader->SetUniform2f("u_Size", bgGeometry->getWidth(),
                                     bgGeometry->getHeight());
    bgShader->SetUniform1f("u_Radius", bgGeometry->getCornerRadius());

    glm::mat4 proj = glm::ortho(0.0f,
                                windowLayout.getWidth(),
                                windowLayout.getHeight(),
                                0.0f, -1.0f, 1.0f);

    bgShader->SetUniformMat4f("u_Proj", proj);
    bgShader->Unbind();
}

void Widget::updateBackground() {
    updateBGMesh();
    updateBGShader();
    updateHoverState();

    for (Widget* subWidget : subWidgets) {
        subWidget->updateBackground();
    }
}

void Widget::setResizable() {
    canResizeLeft = true;
    canResizeRight = true;
    canResizeBottom = true;
    canResizeTop = true;
}

void Widget::setNonResizable() {
    canResizeLeft = false;
    canResizeRight = false;
    canResizeBottom = false;
    canResizeTop = false;
}

void Widget::setMoveable() {
    canMove = true;
}

void Widget::setNonMoveable() {
    canMove = false;
}

TransformType Widget::getCursorState() {
    // Corners should be checked first as edges occupy the same space
    if (bgGeometry->inTopLeft(cursorX, cursorY) &&
        canResizeTop && canResizeLeft) {
        return TransformType::RESIZE_TOP_LEFT;
    }
    else if (bgGeometry->inTopRight(cursorX, cursorY) &&
             canResizeTop && canResizeRight) {
        return TransformType::RESIZE_TOP_RIGHT;
    }
    else if (bgGeometry->inBottomRight(cursorX, cursorY) &&
             canResizeBottom && canResizeRight) {
        return TransformType::RESIZE_BOTTOM_RIGHT;
    }
    else if (bgGeometry->inBottomLeft(cursorX, cursorY) &&
             canResizeBottom && canResizeLeft) {
        return TransformType::RESIZE_BOTTOM_LEFT;
    }

    // Edges should be checked second as the inside occupies the same space
    else if (bgGeometry->inTop(cursorY) && canResizeTop) {
        return TransformType::RESIZE_TOP;
    }
    else if (bgGeometry->inRight(cursorX) && canResizeRight) {
        return TransformType::RESIZE_RIGHT;
    }
    else if (bgGeometry->inBottom(cursorY) && canResizeBottom) {
        return TransformType::RESIZE_BOTTOM;
    }
    else if (bgGeometry->inLeft(cursorX) && canResizeLeft) {
        return TransformType::RESIZE_LEFT;
    }

    // Finally, check if the cursor is even inside the rectangle
    else if (bgGeometry->inInside(cursorX, cursorY) && canMove) {
        return TransformType::MOVE;
    }
    else {
        return TransformType::IDLE;
    }

}

void Widget::setTransformStates(std::vector<TransformType> transformTypes, bool state) {
    for (TransformType transformType : transformTypes) {
        switch (transformType) {
        case MOVE:
            canMove = state;
        case RESIZE_TOP:
            canResizeTop = state;
            break;
        case RESIZE_RIGHT:
            canResizeRight = state;
            break;
        case RESIZE_BOTTOM:
            canResizeBottom = state;
            break;
        case RESIZE_LEFT:
            canResizeLeft = state;
            break;
        case RESIZE_TOP_LEFT:
            canResizeTop = state;
            canResizeLeft = state;
            break;
        case RESIZE_TOP_RIGHT:
            canResizeTop = state;
            canResizeRight = state;
            break;
        case RESIZE_BOTTOM_RIGHT:
            canResizeBottom = state;
            canResizeRight = state;
            break;
        case RESIZE_BOTTOM_LEFT:
            canResizeBottom = state;
            canResizeLeft = state;
            break;
        default:
            assert(false &&
                   "Widget ERROR: Unsupported item given to setResizableStates in resizeUnits");
            break;
        }
    }
}

void Widget::updateTransformState() {
    transformState = getCursorState();
}

void Widget::showHoverTips() {
    hoverTips = true;
    updateHoverState();
}

void Widget::hideHoverTips() {
    hoverTips = false;
    hoverState = TransformType::IDLE;
}

void Widget::updateHoverState() {
    if (!hoverTips) {
        hoverState = TransformType::IDLE;
        return;
    }

    hoverState = getCursorState();
}

void Widget::handleKeyDown(KeyName key, std::vector<ModKeyName> mods) {
    if (regKeyDown) {
        onKeyDown(key, mods);
    }
}

void Widget::handleKeyUp(KeyName key, std::vector<ModKeyName> mods) {
    if (regKeyUp) {
        onKeyUp(key, mods);
    }
}

void Widget::handleMouseMove(float x, float y) {
    assert(false &&
           "Widget ERROR: handleMouseMove is not a valid widget event");
}

void Widget::handleMouseHover(float x, float y) {
    printf("mouse hovered on widget %d at position (%f, %f)\n", id, x, y);

    float dx = x - cursorX;
    float dy = y - cursorY;

    cursorX = x;
    cursorY = y;

    bgGeometry->applyTransform(transformState, cursorX, cursorY, dx, dy);

    updateBackground();

    if (regMouseHover) {
        onMouseHover(x, y);
    }

    for (GuiListener* listener : listeners) {
        if (listener->regMouseHover) {
            listener->onMouseHover(x, y);
        }
    }
}

void Widget::handleMouseEnter() {
    printf("mouse entered widget %d\n", id);

    if (regMouseEnter) {
        onMouseEnter();
    }

    for (GuiListener* listener : listeners) {
        if (listener->regMouseEnter) {
            listener->onMouseEnter();
        }
    }
}

void Widget::handleMouseLeave() {
    printf("mouse left widget %d\n", id);

    hoverState = TransformType::IDLE;

    if (regMouseLeave) {
        onMouseLeave();
    }

    for (GuiListener* listener : listeners) {
        if (listener->regMouseLeave) {
            listener->onMouseLeave();
        }
    }
}

void Widget::handleMouseDown(float x, float y, MouseButtonType type) {
    cursorX = x;
    cursorY = y;

    switch (type) {
        case MouseButtonType::MOUSE_LEFT:
            printf("mouse left down window (%f, %f)\n", x, y);

            updateTransformState();

            break;
        case MouseButtonType::MOUSE_RIGHT:
            printf("mouse right down window (%f, %f)\n", x, y);
            break;
        default:
            assert(false && "Widget ERROR: Called handleMouseDown with an unknown type\n");
    }

    if (bgGeometry->inInside(x, y)) {
        if (regMouseDown) {
            onMouseDown(x, y, type);
        }

        for (GuiListener* listener : listeners) {
            listener->onMouseDown(x, y, type);
        }
    }
}

void Widget::handleMouseUp(float x, float y, MouseButtonType type) {
    cursorX = x;
    cursorY = y;

    switch (type) {
        case MouseButtonType::MOUSE_LEFT:
            printf("mouse up left (%f, %f)\n", x, y);
            transformState = TransformType::IDLE;
            break;
        case MouseButtonType::MOUSE_RIGHT:
            printf("mouse up right (%f, %f)\n", x, y);
            break;
        default:
            assert(false && "Widget ERROR: Called handleMouseUp with an unknown type\n");
    }

    if (regMouseUp) {
        onMouseUp(x, y, type);
    }

    for (GuiListener* listener : listeners) {
        listener->onMouseUp(x, y, type);
    }
}
