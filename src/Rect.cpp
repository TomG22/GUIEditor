#pragma once

#include <algorithm>
#include <stdexcept>

#include "Rect.h"

Rect::Rect()
    : xPos(), yPos(),
    width(), height(),
    cornerRadiusWidth(), cornerRadiusHeight(),
    hitTol(3.0f)
{}

bool Rect::eqWithTol(float a, float b) const {
    return std::abs(a - b) <= hitTol;
}

bool Rect::inInside(float x, float y) const {
    float absXPos = xPos.getAbsValue();
    float absYPos = yPos.getAbsValue();
    float absWidth = width.getAbsValue();
    float absHeight = height.getAbsValue();

    return x >= absXPos - hitTol && x <= absXPos + absWidth + hitTol &&
        y >= absYPos - hitTol && y <= absYPos + absHeight + hitTol;
}

bool Rect::inTopLeft(float x, float y) const {
    float absXPos = xPos.getAbsValue();
    float absYPos = yPos.getAbsValue();

    return eqWithTol(x, absXPos) && eqWithTol(y, absYPos);
}

bool Rect::inTopRight(float x, float y) const {
    float absXPos = xPos.getAbsValue();
    float absYPos = yPos.getAbsValue();
    float absWidth = width.getAbsValue();

    return eqWithTol(x, absXPos + absWidth) && eqWithTol(y, absYPos);
}

bool Rect::inBottomRight(float x, float y) const {
    float absXPos = xPos.getAbsValue();
    float absYPos = yPos.getAbsValue();
    float absWidth = width.getAbsValue();
    float absHeight = height.getAbsValue();

    return eqWithTol(x, absXPos + absWidth) && eqWithTol(y, absYPos + absHeight);
}

bool Rect::inBottomLeft(float x, float y) const {
    float absXPos = xPos.getAbsValue();
    float absYPos = yPos.getAbsValue();
    float absHeight = height.getAbsValue();

    return eqWithTol(x, absXPos) && eqWithTol(y, absYPos + absHeight);
}

bool Rect::inTop(float y) const {
    float absYPos = yPos.getAbsValue();

    return eqWithTol(y, absYPos);
}

bool Rect::inRight(float x) const {
    float absXPos = xPos.getAbsValue();
    float absWidth = width.getAbsValue();

    return eqWithTol(x, absXPos + absWidth);
}

bool Rect::inBottom(float y) const {
    float absYPos = yPos.getAbsValue();
    float absHeight = height.getAbsValue();

    return eqWithTol(y, absYPos + absHeight);
}

bool Rect::inLeft(float x) const {
    float absXPos = xPos.getAbsValue();

    return eqWithTol(x, absXPos);
}

float Rect::getXPos() const {
    return xPos.getAbsValue();
}

float Rect::getYPos() const {
    return yPos.getAbsValue();
}

float Rect::getWidth() const {
    return width.getAbsValue();
}

float Rect::getHeight() const {
    return height.getAbsValue();
}

float Rect::getCornerRadius() const {
    return std::min(cornerRadiusWidth.getAbsValue(),
            cornerRadiusHeight.getAbsValue());
}

void Rect::setPos(float newXPos, float newYPos) {
    if (xPos.isRelBound()) {
        xPos.setSizeScale(newXPos);
    } else {
        xPos.setAbsValue(newXPos);
    }

    if (yPos.isRelBound()) {
        yPos.setSizeScale(newYPos);
    } else {
        yPos.setAbsValue(newYPos);
    }
}

void Rect::setSize(float newWidth, float newHeight) {
    if (width.isRelBound()) {
        width.setSizeScale(newWidth);
    } else {
        width.setAbsValue(newWidth);
    }

    if (height.isRelBound()) {
        height.setSizeScale(newHeight);
    } else {
        height.setAbsValue(newHeight);
    }
}

void Rect::setCornerRadius(float newCornerRadius) {
    if (cornerRadiusWidth.isRelBound()) {
        cornerRadiusWidth.setSizeScale(newCornerRadius);
    } else {
        cornerRadiusWidth.setAbsValue(newCornerRadius);
    }

    if (cornerRadiusHeight.isRelBound()) {
        cornerRadiusHeight.setSizeScale(newCornerRadius);
    } else {
        cornerRadiusHeight.setAbsValue(newCornerRadius);
    }
}

void Rect::applyTransform(TransformType transformState, float x, float y, float dx, float dy) {
    switch (transformState) {
        case TransformType::IDLE:
            break;

        case TransformType::MOVE:
            xPos.setAbsValue(xPos.getAbsValue() + dx);
            yPos.setAbsValue(yPos.getAbsValue() + dy);
            break;

        case TransformType::RESIZE_TOP:
            height.setAbsValue(height.getAbsValue() + yPos.getAbsValue() - y);
            yPos.setAbsValue(y);
            break;
        case TransformType::RESIZE_RIGHT:
            width.setAbsValue(x - xPos.getAbsValue());
            break;
        case TransformType::RESIZE_BOTTOM:
            height.setAbsValue(y - yPos.getAbsValue());
            break;
        case TransformType::RESIZE_LEFT:
            width.setAbsValue(width.getAbsValue() + xPos.getAbsValue() - x);
            xPos.setAbsValue(x);
            break;

        case TransformType::RESIZE_TOP_LEFT:
            height.setAbsValue(height.getAbsValue() + yPos.getAbsValue() - y);
            yPos.setAbsValue(y);
            width.setAbsValue(width.getAbsValue() + xPos.getAbsValue() - x);
            xPos.setAbsValue(x);
            break;
        case TransformType::RESIZE_TOP_RIGHT:
            height.setAbsValue(height.getAbsValue() + yPos.getAbsValue() - y);
            yPos.setAbsValue(y);
            width.setAbsValue(x - xPos.getAbsValue());
            break;
        case TransformType::RESIZE_BOTTOM_RIGHT:
            width.setAbsValue(x - xPos.getAbsValue());
            height.setAbsValue(y - yPos.getAbsValue());
            break;
        case TransformType::RESIZE_BOTTOM_LEFT:
            height.setAbsValue(y - yPos.getAbsValue());
            width.setAbsValue(width.getAbsValue() + xPos.getAbsValue() - x);
            xPos.setAbsValue(x);
            break;
    }
}

/*
void Rect::bindRelPosTo(Rect* parentRect, RelAttrType parentAttrType, RelAttrType childAttrType) {

}
*/

void Rect::bindRelTo(Rect* parentRect, RelAttrType parentAttrType, RelAttrType childAttrType) {
    if (!parentRect) return;

    if (!RelAttr::isBindable(parentAttrType, childAttrType)) {
        throw std::runtime_error("Rect ERROR: Attempted to bind an invalid combination of attributes");
    }

    // Position Attributes

    // Child's general position attribute bound to parent's general position attribute
    if (childAttrType == RelAttrType::POS && parentAttrType == RelAttrType::POS) {
        parentRect->xPos.addRelPosChild(&xPos);
        parentRect->width.addRelPosChild(&xPos);
        parentRect->yPos.addRelPosChild(&yPos);
        parentRect->height.addRelPosChild(&yPos);
        return;
    }

    // Child's specific position attribute bound to parent's specific position attribute
    if (childAttrType == RelAttrType::X_POS && parentAttrType == RelAttrType::X_POS) {
        parentRect->xPos.addRelPosChild(&xPos);
        parentRect->width.addRelPosChild(&xPos);
        return;
    }

    if (childAttrType == RelAttrType::Y_POS && parentAttrType == RelAttrType::Y_POS) {
        parentRect->yPos.addRelPosChild(&yPos);
        parentRect->height.addRelPosChild(&yPos);
        return;
    }

    // Child's specific position attribute bound to inverted parent's specific position attribute
    if (childAttrType == RelAttrType::X_POS && parentAttrType == RelAttrType::Y_POS) {
        parentRect->yPos.addRelPosChild(&xPos);
        parentRect->height.addRelPosChild(&xPos);
        return;
    }

    if (childAttrType == RelAttrType::Y_POS && parentAttrType == RelAttrType::X_POS) {
        parentRect->xPos.addRelPosChild(&yPos);
        parentRect->width.addRelPosChild(&yPos);
        return;
    }

    // Child's general position attribute bound to parent's specific position attribute
    if (childAttrType == RelAttrType::POS && parentAttrType == RelAttrType::X_POS) {
        parentRect->xPos.addRelPosChild(&xPos);
        parentRect->width.addRelPosChild(&xPos);
        parentRect->yPos.addRelPosChild(&yPos);
        parentRect->height.addRelPosChild(&yPos);
    } else if (childAttrType == RelAttrType::POS && parentAttrType == RelAttrType::Y_POS) {
        parentRect->yPos.addRelPosChild(&xPos);
        parentRect->height.addRelPosChild(&xPos);
        parentRect->yPos.addRelPosChild(&yPos);
        parentRect->height.addRelPosChild(&yPos);
    }

    // Size Attributes

    // Child's general position attribute bound to parent's general position attribute
    if (childAttrType == RelAttrType::SIZE && parentAttrType == RelAttrType::SIZE) {
        parentRect->width.addRelSizeChild(&width);
        parentRect->height.addRelSizeChild(&height);
        return;
    }

    // Child's specific position attribute bound to parent's specific position attribute
    if (childAttrType == RelAttrType::WIDTH && parentAttrType == RelAttrType::WIDTH) {
        parentRect->width.addRelSizeChild(&width);
        return;
    }

    if (childAttrType == RelAttrType::HEIGHT && parentAttrType == RelAttrType::HEIGHT) {
        parentRect->height.addRelSizeChild(&height);
        return;
    }

    // Child's specific position attribute bound to inverted parent's specific position attribute
    if (childAttrType == RelAttrType::WIDTH && parentAttrType == RelAttrType::HEIGHT) {
        parentRect->height.addRelSizeChild(&width);
        return;
    }

    if (childAttrType == RelAttrType::HEIGHT && parentAttrType == RelAttrType::WIDTH) {
        parentRect->width.addRelSizeChild(&height);
        return;
    }

    // Child's general position attribute bound to parent's specific position attribute
    if (childAttrType == RelAttrType::SIZE && parentAttrType == RelAttrType::WIDTH) {
        parentRect->width.addRelSizeChild(&width);
        parentRect->width.addRelSizeChild(&height);
    } else if (childAttrType == RelAttrType::SIZE && parentAttrType == RelAttrType::HEIGHT) {
        parentRect->height.addRelSizeChild(&width);
        parentRect->height.addRelSizeChild(&height);
    }


    // Radius Attributes

    // Child's general radius attribute bound to parent's general radius attribute
    if (parentAttrType == RelAttrType::RADIUS && childAttrType == RelAttrType::RADIUS) {
        parentRect->cornerRadiusWidth.addRelSizeChild(&cornerRadiusWidth);
        parentRect->cornerRadiusHeight.addRelSizeChild(&cornerRadiusHeight);
        return;
    }
}

void Rect::unbindRelTo(Rect* parentRect, RelAttrType parentAttrType, RelAttrType childAttrType) {
    if (!parentRect) return;

    if (!RelAttr::isBindable(parentAttrType, childAttrType)) {
        throw std::runtime_error("Rect ERROR: Attempted to unbind an invalid combination of attributes");
    }

    // Position Attributes

    // Child's general position attribute bound to parent's general position attribute
    if (childAttrType == RelAttrType::POS && parentAttrType == RelAttrType::POS) {
        parentRect->xPos.removeRelPosChild(&xPos);
        parentRect->width.removeRelPosChild(&xPos);
        parentRect->yPos.removeRelPosChild(&yPos);
        parentRect->height.removeRelPosChild(&yPos);
        return;
    }

    // Child's specific position attribute bound to parent's specific position attribute
    if (childAttrType == RelAttrType::X_POS && parentAttrType == RelAttrType::X_POS) {
        parentRect->xPos.removeRelPosChild(&xPos);
        parentRect->width.removeRelPosChild(&xPos);
        return;
    }

    if (childAttrType == RelAttrType::Y_POS && parentAttrType == RelAttrType::Y_POS) {
        parentRect->yPos.removeRelPosChild(&yPos);
        parentRect->height.removeRelPosChild(&yPos);
        return;
    }

    // Child's specific position attribute bound to inverted parent's specific position attribute
    if (childAttrType == RelAttrType::X_POS && parentAttrType == RelAttrType::Y_POS) {
        parentRect->yPos.removeRelPosChild(&xPos);
        parentRect->height.removeRelPosChild(&xPos);
        return;
    }

    if (childAttrType == RelAttrType::Y_POS && parentAttrType == RelAttrType::X_POS) {
        parentRect->xPos.removeRelPosChild(&yPos);
        parentRect->width.removeRelPosChild(&yPos);
        return;
    }

    // Child's general position attribute bound to parent's specific position attribute
    if (childAttrType == RelAttrType::POS && parentAttrType == RelAttrType::X_POS) {
        parentRect->xPos.removeRelPosChild(&xPos);
        parentRect->width.removeRelPosChild(&xPos);
        parentRect->yPos.removeRelPosChild(&yPos);
        parentRect->height.removeRelPosChild(&yPos);
    } else if (childAttrType == RelAttrType::POS && parentAttrType == RelAttrType::Y_POS) {
        parentRect->yPos.removeRelPosChild(&xPos);
        parentRect->height.removeRelPosChild(&xPos);
        parentRect->yPos.removeRelPosChild(&yPos);
        parentRect->height.removeRelPosChild(&yPos);
    }

    // Size Attributes

    // Child's general position attribute bound to parent's general position attribute
    if (childAttrType == RelAttrType::SIZE && parentAttrType == RelAttrType::SIZE) {
        parentRect->width.removeRelSizeChild(&width);
        parentRect->height.removeRelSizeChild(&height);
        return;
    }

    // Child's specific position attribute bound to parent's specific position attribute
    if (childAttrType == RelAttrType::WIDTH && parentAttrType == RelAttrType::WIDTH) {
        parentRect->width.removeRelSizeChild(&width);
        return;
    }

    if (childAttrType == RelAttrType::HEIGHT && parentAttrType == RelAttrType::HEIGHT) {
        parentRect->height.removeRelSizeChild(&height);
        return;
    }

    // Child's specific position attribute bound to inverted parent's specific position attribute
    if (childAttrType == RelAttrType::WIDTH && parentAttrType == RelAttrType::HEIGHT) {
        parentRect->height.removeRelSizeChild(&width);
        return;
    }

    if (childAttrType == RelAttrType::HEIGHT && parentAttrType == RelAttrType::WIDTH) {
        parentRect->width.removeRelSizeChild(&height);
        return;
    }

    // Child's general position attribute bound to parent's specific position attribute
    if (childAttrType == RelAttrType::SIZE && parentAttrType == RelAttrType::WIDTH) {
        parentRect->width.removeRelSizeChild(&width);
        parentRect->width.removeRelSizeChild(&height);
    } else if (childAttrType == RelAttrType::SIZE && parentAttrType == RelAttrType::HEIGHT) {
        parentRect->height.removeRelSizeChild(&width);
        parentRect->height.removeRelSizeChild(&height);
    }


    // Radius Attributes

    // Child's general radius attribute bound to parent's general radius attribute
    if (parentAttrType == RelAttrType::RADIUS && childAttrType == RelAttrType::RADIUS) {
        parentRect->cornerRadiusWidth.removeRelSizeChild(&cornerRadiusWidth);
        parentRect->cornerRadiusHeight.removeRelSizeChild(&cornerRadiusHeight);
        return;
    }
}
