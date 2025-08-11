#include <cassert>

#include "RelAttr.h"

RelAttr::RelAttr()
    //: relType(RelType::ABSOLUTE),
    : absValue(0.0f),
      sizeScale(1.0f)
{}

/*
RelType RelAttr::getRelType() const {
    return relType;
}
*/

float RelAttr::getAbsValue() const {
    return absValue;
}

/*
float RelAttr::setRelType(RelType newRelType) {
    relType = newRelType;
}
*/
