#include <cassert>

#include "RelAttr.h"

RelAttr::RelAttr()
    : absValue(0.0f),
      sizeScale(0.0f)
{}

float RelAttr::getAbsValue() const {
    return absValue;
}

bool RelAttr::isBindable(RelAttrType parentAttrType, RelAttrType childAttrType) {
    if (parentAttrType == childAttrType) {
        return true;
    }

    // General position child attribute is bound to a specific parent attribute is a specific position attribute
    if ((childAttrType == RelAttrType::POS || childAttrType == RelAttrType::X_POS || childAttrType == RelAttrType::Y_POS) &&
        (parentAttrType == RelAttrType::X_POS || parentAttrType == RelAttrType::Y_POS)) {
        return true;
    }

    // Parent is any size attribute and child is a specific size attribute
    if ((childAttrType == RelAttrType::SIZE || childAttrType == RelAttrType::WIDTH || childAttrType == RelAttrType::HEIGHT) &&
        (parentAttrType == RelAttrType::WIDTH || parentAttrType == RelAttrType::HEIGHT)) {
        return true;
    }

    return false;
}
