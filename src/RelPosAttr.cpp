#include "RelPosAttr.h"
#include "RelSizeAttr.h"

RelPosAttr::RelPosAttr()
    : relPosParent(nullptr),
      relSizeParent(nullptr)
{}

bool RelPosAttr::isRelBound() const {
    return relPosParent != nullptr && relSizeParent != nullptr;
}

void RelPosAttr::setAbsValue(float newAbsValue) {
    absValue = newAbsValue;

    calcSizeScale();
    calcAbsValue();
}

void RelPosAttr::setSizeScale(float newSizeScale) {
    sizeScale = newSizeScale;

    calcAbsValue();

    for (RelPosAttr* relPosChild : relPosChildren) {
        relPosChild->calcAbsValue();
    }
}

void RelPosAttr::setRelPosParent(RelPosAttr* posAttr) {
    relPosParent = posAttr;
}

void RelPosAttr::removeRelPosParent() {
    relPosParent = nullptr;
}

void RelPosAttr::setRelSizeParent(RelSizeAttr* sizeAttr) {
    relSizeParent = sizeAttr;
}

void RelPosAttr::removeRelSizeParent() {
    relSizeParent = nullptr;
}

void RelPosAttr::addRelPosChild(RelPosAttr* posAttr) {
    posAttr->setRelPosParent(this);

    relPosChildren.insert(posAttr);
}

void RelPosAttr::removeRelPosChild(RelPosAttr* posAttr) {
    posAttr->setRelPosParent(nullptr);

    relPosChildren.erase(posAttr);
}

void RelPosAttr::calcAbsValue() {
    if (isRelBound()) {
        absValue = relPosParent->getAbsValue() + relSizeParent->getAbsValue() * sizeScale;
    }

    for (RelPosAttr* relPosChild : relPosChildren) {
        relPosChild->calcAbsValue();
    }
}

void RelPosAttr::calcSizeScale() {
    if (isRelBound() && relSizeParent->getAbsValue() != 0) {
        sizeScale = (absValue - relPosParent->getAbsValue()) / relSizeParent->getAbsValue();
    }

    for (RelPosAttr* relPosChild : relPosChildren) {
        relPosChild->calcAbsValue();
    }
}
