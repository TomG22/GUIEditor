#pragma once

#include <glm/glm.hpp>

#include "GuiTypes.h"

class Rect {
public:
    glm::vec2 topLeft;
    glm::vec2 topRight;
    glm::vec2 bottomRight;
    glm::vec2 bottomLeft;

    float absRadius;
    float relRadius;
    bool relRadiusFlag;


    float hitTol;

    Rect();

    float getWidth() const;
    float getHeight() const;
    float getRadius() const;

    bool eqWithTol(float a, float b) const;

    bool inInside(float x, float y) const;
    bool inTopLeft(float x, float y) const;
    bool inTopRight(float x, float y) const;
    bool inBottomRight(float x, float y) const;
    bool inBottomLeft(float x, float y) const;
    bool inTop(float y) const;
    bool inRight(float x) const;
    bool inBottom(float y) const;
    bool inLeft(float x) const;

    void setAbsTransform(glm::vec2 newTopLeft, glm::vec2 newBottomRight);
    void setRelPos(float relXOffset, float relYOffset, int winWidth, int winHeight);
    void setRelSize(float relWidth, float relHeight, int winWidth, int winHeight);

    void setRelRadius(float radius);
    void setAbsRadius(float radius);

    void applyTransform(TransformState transformState, float x, float y, float dx, float dy);
};
