#pragma once

#include <glm/glm.hpp>

#include "GuiTypes.h"
#include "RelPosAttr.h"
#include "RelSizeAttr.h"

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

    float getXPos() const;
    float getYPos() const;
    float getWidth() const;
    float getHeight() const;
    float getCornerRadius() const;

    void setPos(float newXPos, float newYPos);
    void setSize(float newWidth, float newHeight);
    void setCornerRadius(float newCornerRadius);

    void applyTransform(TransformType transformState, float x, float y, float dx, float dy);

    void setRelTo(Rect* parentRect, RelAttrType parentAttrType, RelAttrType childAttrType);

//private:
    RelPosAttr xPos, yPos;
    RelSizeAttr width, height;
    RelSizeAttr cornerRadiusWidth, cornerRadiusHeight;

    float hitTol;
};
