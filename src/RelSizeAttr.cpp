#include "RelPosAttr.h"
#include "RelSizeAttr.h"

RelSizeAttr::RelSizeAttr() : relSizeParent(nullptr) {}

bool RelSizeAttr::isRelBound() const {
    return relSizeParent != nullptr;
}

void RelSizeAttr::setAbsValue(float newAbsValue) {
    absValue = newAbsValue;

    calcSizeScale();
    calcAbsValue();
}

void RelSizeAttr::setSizeScale(float newSizeScale) {
    sizeScale = newSizeScale;

    calcAbsValue();
}

void RelSizeAttr::setRelSizeParent(RelSizeAttr* sizeAttr) {
    relSizeParent = sizeAttr;
}

void RelSizeAttr::removeRelSizeParent() {
    relSizeParent = nullptr;
}

void RelSizeAttr::addRelSizeChild(RelSizeAttr* sizeAttr) {
    sizeAttr->setRelSizeParent(this);

    relSizeChildren.insert(sizeAttr);
}

void RelSizeAttr::removeRelSizeChild(RelSizeAttr* sizeAttr) {
    sizeAttr->setRelSizeParent(nullptr);

    relSizeChildren.erase(sizeAttr);
}

void RelSizeAttr::addRelPosChild(RelPosAttr* posAttr) {
    posAttr->setRelSizeParent(this);

    relPosChildren.insert(posAttr);
}

void RelSizeAttr::removeRelPosChild(RelPosAttr* posAttr) {
    posAttr->setRelSizeParent(nullptr);

    relPosChildren.erase(posAttr);
}

void RelSizeAttr::calcAbsValue() {
    if (isRelBound()) {
        absValue = relSizeParent->getAbsValue() * sizeScale;
    }

    for (RelPosAttr* relPosChild : relPosChildren) {
        relPosChild->calcAbsValue();
    }

    for (RelSizeAttr* relSizeChild : relSizeChildren) {
        relSizeChild->calcAbsValue();
    }
}

void RelSizeAttr::calcSizeScale() {
    if (isRelBound() && relSizeParent->getAbsValue() != 0) {
        sizeScale = absValue / relSizeParent->getAbsValue();
    }
}
