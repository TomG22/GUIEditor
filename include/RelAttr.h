#pragma once

#include <unordered_set>

#include "GuiTypes.h"

class RelAttr {
public:
    RelAttr();

    virtual bool isRelBound() const = 0;
    virtual void setAbsValue(float newAbsValue) = 0;
    virtual void setSizeScale(float newAbsValue) = 0;

    float getAbsValue() const;

protected:
    float absValue;
    float sizeScale;

    virtual void calcAbsValue() = 0;
    virtual void calcSizeScale() = 0;
};
