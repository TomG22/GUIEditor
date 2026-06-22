#include <cassert>

#include "RelAttr.h"

RelAttr::RelAttr() : absValue(0.0f), sizeScale(0.0f) {}

float RelAttr::getAbsValue() const {
    return absValue;
}

bool RelAttr::isBindable(RelAttrType parentAttrType, RelAttrType childAttrType) {
    if (parentAttrType == childAttrType) {
        return true;
    }

    // Any child position attribute can bind to any specific parent position attribute
    if ((childAttrType == RelAttrType::POS || childAttrType == RelAttrType::X_POS || childAttrType == RelAttrType::Y_POS) &&
        (parentAttrType == RelAttrType::X_POS || parentAttrType == RelAttrType::Y_POS)) {
        return true;
    }

    // Any child size attribute can bind to any specific parent size attribute
    if ((childAttrType == RelAttrType::SIZE || childAttrType == RelAttrType::WIDTH || childAttrType == RelAttrType::HEIGHT) &&
        (parentAttrType == RelAttrType::WIDTH || parentAttrType == RelAttrType::HEIGHT)) {
        return true;
    }

    return false;
}
