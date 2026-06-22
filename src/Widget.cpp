#include <stdexcept>
#include <vector>

#include "Widget.h"
#include "Layout.h"

Widget::Widget(Layout& windowLayout)
    : windowLayout(windowLayout),
      layout(LayoutType::WIDGET),
      bgColor(1.0f)
{
    // TODO want this to be single shader object later
    std::string shaderFile = "res\\shaders\\2DVertexColor.shader";
    bgShader = new Shader(shaderFile);

    float left = layout.getAbsXPos();
    float right = left + layout.getAbsWidth();
    float top = layout.getAbsYPos();
    float bottom = top + layout.getAbsHeight();

    Vertex2D vertices[4] = {
        {{left, top}, bgColor, {0.0f, 1.0f}},
        {{right, top}, bgColor, {1.0f, 1.0f}},
        {{right, bottom}, bgColor, {1.0f, 0.0f}},
        {{left, bottom}, bgColor, {0.0f, 0.0f}}
    };

    unsigned int indices[6] = {0,1,2, 2,3,0};

    VertexArray* va = new VertexArray();
    VertexBuffer* vb = new VertexBuffer(vertices, sizeof(Vertex2D) * 4);

    VertexBufferLayout* layout = new VertexBufferLayout();
    layout->Push<Vertex2D>(1);

    va->Bind();
    vb->Bind();
    va->AddBuffer(*vb, *layout);

    IndexBuffer* ib = new IndexBuffer(indices, 6);

    bgMesh = new Mesh(va, vb, ib);

    updateBGShader();
    setResizable();
    setMoveable();
}

Widget* Widget::makeSubWidget() {
    Widget* widget = new Widget(windowLayout);
    subWidgets.push_back(widget);

    return widget;
}

void Widget::bindParentLayout(Layout* newParentLayout) {
    if (newParentLayout == nullptr)
        throw std::runtime_error("Widget ERROR: Attempted to call bindParentLayout with a null new parent layout");

    boundParentLayout = newParentLayout;

    if (boundParentLayout->getLayoutType() == LayoutType::WIDGET) {
        layout.setRelXPos((layout.getAbsXPos() - boundParentLayout->getAbsXPos()) / boundParentLayout->getAbsWidth());
        layout.setRelYPos((layout.getAbsYPos() - boundParentLayout->getAbsYPos()) / boundParentLayout->getAbsHeight());
        layout.setRelWidth(layout.getAbsWidth() / boundParentLayout->getAbsWidth());
        layout.setRelHeight(layout.getAbsHeight() / boundParentLayout->getAbsHeight());
    } else if (boundParentLayout->getLayoutType() == LayoutType::WINDOW) {
        layout.setRelXPos(layout.getAbsXPos() / boundParentLayout->getAbsWidth()); 
        layout.setRelYPos(layout.getAbsYPos() / boundParentLayout->getAbsHeight()); 
        layout.setRelWidth(layout.getAbsWidth() / boundParentLayout->getAbsWidth());
        layout.setRelHeight(layout.getAbsHeight() / boundParentLayout->getAbsHeight());
    }
}

void Widget::unbindParentLayout() {
    if (boundParentLayout == nullptr)
        throw std::runtime_error("Widget ERROR: Attempted to call unbindParentLayout on an unbound layout");

    if (boundParentLayout->getLayoutType() == LayoutType::WIDGET) {
        layout.setAbsXPos(layout.getRelXPos() * boundParentLayout->getAbsWidth() + boundParentLayout->getAbsXPos());
        layout.setAbsYPos(layout.getRelYPos() * boundParentLayout->getAbsHeight() + boundParentLayout->getAbsYPos());
        layout.setAbsWidth(layout.getRelWidth() * boundParentLayout->getAbsWidth());
        layout.setAbsHeight(layout.getRelHeight() * boundParentLayout->getAbsHeight());
    } else if (boundParentLayout->getLayoutType() == LayoutType::WINDOW) {
        layout.setAbsXPos(layout.getRelXPos() * boundParentLayout->getAbsWidth());
        layout.setAbsYPos(layout.getRelYPos() * boundParentLayout->getAbsHeight());
        layout.setAbsWidth(layout.getRelWidth() * boundParentLayout->getAbsWidth());
        layout.setAbsHeight(layout.getRelHeight() * boundParentLayout->getAbsHeight());
    }

    boundParentLayout = nullptr;
}

void Widget::markChildrenDirty() {
    for (Widget* widget : subWidgets) {
        widget->layout.dirty = true;
        widget->markChildrenDirty();
    }
}

void Widget::setAbsXPos(float x) {
    layout.setAbsXPos(x);

    markChildrenDirty();

    if (boundParentLayout == nullptr)
        return;
    else if (boundParentLayout->getLayoutType() == LayoutType::WIDGET)
        layout.setRelXPos((x - boundParentLayout->getAbsXPos()) / boundParentLayout->getAbsWidth());
    else if (boundParentLayout->getLayoutType() == LayoutType::WINDOW)
        layout.setRelXPos(x / boundParentLayout->getAbsWidth()); 
}

void Widget::setAbsYPos(float y) {
    layout.setAbsYPos(y);

    markChildrenDirty();

    if (boundParentLayout == nullptr)
        return;
    else if (boundParentLayout->getLayoutType() == LayoutType::WIDGET)
        layout.setRelYPos((y - boundParentLayout->getAbsYPos()) / boundParentLayout->getAbsHeight());
    else if (boundParentLayout->getLayoutType() == LayoutType::WINDOW)
        layout.setRelYPos(y / boundParentLayout->getAbsHeight());
}

void Widget::setAbsPos(float x, float y) {
    layout.setAbsXPos(x);
    layout.setAbsYPos(y);

    markChildrenDirty();

    if (boundParentLayout == nullptr)
        return;
    if (boundParentLayout->getLayoutType() == LayoutType::WIDGET) {
        layout.setRelXPos((x - boundParentLayout->getAbsXPos()) / boundParentLayout->getAbsWidth());
        layout.setRelYPos((y - boundParentLayout->getAbsYPos()) / boundParentLayout->getAbsHeight());
    } else if (boundParentLayout->getLayoutType() == LayoutType::WINDOW) {
        layout.setRelXPos(x / boundParentLayout->getAbsWidth()); 
        layout.setRelYPos(y / boundParentLayout->getAbsHeight()); 
    }
}

void Widget::setAbsWidth(float w) {
    layout.setAbsWidth(w);

    markChildrenDirty();

    if (boundParentLayout == nullptr)
        return;
    if (boundParentLayout->getLayoutType() == LayoutType::WIDGET ||
        boundParentLayout->getLayoutType() == LayoutType::WINDOW) {
        layout.setRelWidth(w / boundParentLayout->getAbsWidth());
    }
}

void Widget::setAbsHeight(float h) {
    layout.setAbsHeight(h);

    markChildrenDirty();

    if (boundParentLayout == nullptr)
        return;
    if (boundParentLayout->getLayoutType() == LayoutType::WIDGET ||
        boundParentLayout->getLayoutType() == LayoutType::WINDOW) {
        layout.setRelHeight(h / boundParentLayout->getAbsHeight());
    }
}

void Widget::setAbsSize(float w, float h) {
    layout.setAbsWidth(w);
    layout.setAbsHeight(h);

    markChildrenDirty();

    if (boundParentLayout == nullptr)
        return;
    if (boundParentLayout->getLayoutType() == LayoutType::WIDGET ||
        boundParentLayout->getLayoutType() == LayoutType::WINDOW) {
        layout.setRelWidth(w / boundParentLayout->getAbsWidth());
        layout.setRelHeight(h / boundParentLayout->getAbsHeight());
    }
}

void Widget::setXPos(float x) {
    if (boundParentLayout == nullptr)
        layout.setAbsXPos(x);
    else
        layout.setRelXPos(x);

    markChildrenDirty();
}

void Widget::setYPos(float y) {
    if (boundParentLayout == nullptr)
        layout.setAbsYPos(y);
    else
        layout.setRelYPos(y);

    markChildrenDirty();
}

void Widget::setPos(float x, float y) {
    if (boundParentLayout == nullptr)
        layout.setAbsPos(x, y);
    else
        layout.setRelPos(x, y);

    markChildrenDirty();
}

void Widget::setWidth(float w) {
    if (boundParentLayout == nullptr)
        layout.setAbsWidth(w);
    else
        layout.setRelWidth(w);

    markChildrenDirty();
}

void Widget::setHeight(float h) {
    if (boundParentLayout == nullptr)
        layout.setAbsHeight(h);
    else
        layout.setRelHeight(h);

    markChildrenDirty();
}

void Widget::setSize(float w, float h) {
    if (boundParentLayout == nullptr)
        layout.setAbsSize(w, h);
    else
        layout.setRelSize(w, h);

    markChildrenDirty();
}

Widget* Widget::hitTest(const std::vector<Widget*>& widgets, float x, float y) {
    for (auto it = widgets.rbegin(); it != widgets.rend(); ++it) {
        Widget* widget = *it;

        if (!widget->subWidgets.empty()) {
            if (Widget* child = hitTest(widget->subWidgets, x, y))
                return child;
        }

        if (widget->layout.inInside(x, y)) {
            return widget;
        }
    }
    return nullptr;
}

void Widget::applyTransform(TransformType transformState, float x, float y, float dx, float dy) {
    switch (transformState) {
        case TransformType::IDLE:
            break;

        case TransformType::MOVE:
            setAbsXPos(layout.getAbsXPos() + dx);
            setAbsYPos(layout.getAbsYPos() + dy);
            break;

        case TransformType::RESIZE_TOP:
            setAbsHeight(layout.getAbsHeight() + layout.getAbsYPos() - y);
            setAbsYPos(y);
            break;
        case TransformType::RESIZE_RIGHT:
            setAbsWidth(x - layout.getAbsXPos());
            break;
        case TransformType::RESIZE_BOTTOM:
            setAbsHeight(y - layout.getAbsYPos());
            break;
        case TransformType::RESIZE_LEFT:
            setAbsWidth(layout.getAbsWidth() + layout.getAbsXPos() - x);
            setAbsXPos(x);
            break;

        case TransformType::RESIZE_TOP_LEFT:
            setAbsHeight(layout.getAbsHeight() + layout.getAbsYPos() - y);
            setAbsYPos(y);
            setAbsWidth(layout.getAbsWidth() + layout.getAbsXPos() - x);
            setAbsXPos(x);
            break;
        case TransformType::RESIZE_TOP_RIGHT:
            setAbsHeight(layout.getAbsHeight() + layout.getAbsYPos() - y);
            setAbsYPos(y);
            setAbsWidth(x - layout.getAbsXPos());
            break;
        case TransformType::RESIZE_BOTTOM_RIGHT:
            setAbsWidth(x - layout.getAbsXPos());
            setAbsHeight(y - layout.getAbsYPos());
            break;
        case TransformType::RESIZE_BOTTOM_LEFT:
            setAbsHeight(y - layout.getAbsYPos());
            setAbsWidth(layout.getAbsWidth() + layout.getAbsXPos() - x);
            setAbsXPos(x);
            break;

        default:
            throw std::runtime_error("Widget ERROR: Attempted to call applyTransform with unknown transform type");
    }
}

void Widget::updateBGMesh() {
    if (!glfwGetCurrentContext()) {
        return;
    }

    float left = layout.getAbsXPos();
    float right = left + layout.getAbsWidth();
    float top = layout.getAbsYPos();
    float bottom = top + layout.getAbsHeight();

    Vertex2D vertices[4] = {
        {{left, top}, bgColor, {0.0f, 1.0f}},
        {{right, top}, bgColor, {1.0f, 1.0f}},
        {{right, bottom}, bgColor, {1.0f, 0.0f}},
        {{left, bottom}, bgColor, {0.0f, 0.0f}}
    };

    bgMesh->UpdateVertices(vertices, sizeof(Vertex2D) * 4, 0);
}

void Widget::updateBGShader() {
    if (!glfwGetCurrentContext()) {
        return;
    }

    bgShader->Bind();
    bgShader->SetUniform2f("u_TopLeftPos", layout.getAbsXPos(),
                                           layout.getAbsYPos());
    bgShader->SetUniform2f("u_Size", layout.getAbsWidth(),
                                     layout.getAbsHeight());
    // bgShader->SetUniform1f("u_Radius", layout.getCornerRadius());

    glm::mat4 proj = glm::ortho(0.0f,
                                windowLayout.getAbsWidth(),
                                windowLayout.getAbsHeight(),
                                0.0f, -1.0f, 1.0f);

    bgShader->SetUniformMat4f("u_Proj", proj);
    bgShader->Unbind();
}

void Widget::updateBackground() {
    updateBGMesh();
    updateBGShader();

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
    if (layout.inTopLeft(cursorX, cursorY) &&
        canResizeTop && canResizeLeft)
        return TransformType::RESIZE_TOP_LEFT;

    if (layout.inTopRight(cursorX, cursorY) &&
             canResizeTop && canResizeRight)
        return TransformType::RESIZE_TOP_RIGHT;

    if (layout.inBottomRight(cursorX, cursorY) &&
             canResizeBottom && canResizeRight)
        return TransformType::RESIZE_BOTTOM_RIGHT;

    if (layout.inBottomLeft(cursorX, cursorY) &&
             canResizeBottom && canResizeLeft)
        return TransformType::RESIZE_BOTTOM_LEFT;

    // Edges should be checked second as the inside occupies the same space
    if (layout.inTop(cursorY) && canResizeTop)
        return TransformType::RESIZE_TOP;

    if (layout.inRight(cursorX) && canResizeRight)
        return TransformType::RESIZE_RIGHT;

    if (layout.inBottom(cursorY) && canResizeBottom)
        return TransformType::RESIZE_BOTTOM;

    if (layout.inLeft(cursorX) && canResizeLeft)
        return TransformType::RESIZE_LEFT;

    // Finally, check if the cursor is even inside the rectangle
    if (layout.inInside(cursorX, cursorY) && canMove)
        return TransformType::MOVE;


    // The cursor didn't affect the rectangle
    return TransformType::IDLE;
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
                       "Widget ERROR: Called setTransformStates with an unrecognized transformType");
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

    applyTransform(transformState, cursorX, cursorY, dx, dy);
    updateHoverState();

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

    updateHoverState();

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
    updateHoverState();

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

    if (layout.inInside(x, y)) {
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
