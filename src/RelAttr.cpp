#include <cassert>

#include "RelAttr.h"

RelAttr::RelAttr()
    : absValue(0.0f),
      sizeScale(0.0f)
{}

float RelAttr::getAbsValue() const {
    return absValue;
}

