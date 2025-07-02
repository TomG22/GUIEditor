#pragma once

#include <glm/glm.hpp>

#include "GuiTypes.h"

class Rect {
public:
    int width;
    int height;

    int xOffset;
    int yOffset;

    glm::vec2 topLeft;
    glm::vec2 topRight;
    glm::vec2 bottomRight;
    glm::vec2 bottomLeft;

    float hitTol;

    Rect(int width, int height);

    bool eqWithTol(float a, float b);

    bool inInside(float x, float y);
    bool inTopLeft(float x, float y);
    bool inTopRight(float x, float y);
    bool inBottomRight(float x, float y);
    bool inBottomLeft(float x, float y);
    bool inTop(float y);
    bool inRight(float x);
    bool inBottom(float y);
    bool inLeft(float x);

    void setAbsTransform(glm::vec2 newTopLeft, glm::vec2 newBottomRight);
    void setRelPos(float relXOffset, float relYOffset, int winWidth, int winHeight);
    void setRelSize(float relWidth, float relHeight, int winWidth, int winHeight);
    void applyTransform(TransformState transformState, float x, float y, float dx, float dy);
};
