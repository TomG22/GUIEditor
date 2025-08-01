#pragma once

#include <glm/glm.hpp>

#include "GuiTypes.h"
#include "RelAttribute.h"

class Rect {
public:
    Rect();

    bool eqWithTol(float a, float b) const;

    bool inInside(float x, float y) const;
    bool inTop(float y) const;
    bool inRight(float x) const;
    bool inBottom(float y) const;
    bool inLeft(float x) const;
    bool inTopLeft(float x, float y) const;
    bool inTopRight(float x, float y) const;
    bool inBottomRight(float x, float y) const;
    bool inBottomLeft(float x, float y) const;

    float getCornerRadius() const;
    void setCornerRadius(float radius);
    void setCornerRadiusScale(float scale);

    void applyTransform(TransformType transformState, float x, float y, float dx, float dy);

    RelAttribute xPos, yPos;
    RelAttribute width, height;
    RelAttribute cornerRadiusWidth, cornerRadiusHeight;


    float hitTol;
};
