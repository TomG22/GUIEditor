#pragma once

#include <algorithm>

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

void Rect::bindRelTo(Rect* parentRect, RelAttrType parentAttrType, RelAttrType childAttrType) {
    if (parentRect == nullptr) {
        return;
    }

    if (parentAttrType == RelAttrType::POS) {
        if (childAttrType == RelAttrType::POS) {
            parentRect->xPos.addRelPosChild(&xPos);
            parentRect->yPos.addRelPosChild(&yPos);
            parentRect->width.addRelPosChild(&xPos);
            parentRect->height.addRelPosChild(&yPos);
        } else if (childAttrType == RelAttrType::X_POS) {
            parentRect->xPos.addRelPosChild(&xPos);
            parentRect->width.addRelPosChild(&xPos);
        } else if (childAttrType == RelAttrType::Y_POS) {
            parentRect->yPos.addRelPosChild(&yPos);
            parentRect->height.addRelPosChild(&yPos);
        }
    }

    if (parentAttrType == RelAttrType::SIZE) {
        if (childAttrType == RelAttrType::SIZE) {
            parentRect->width.addRelSizeChild(&width);
            parentRect->height.addRelSizeChild(&height);
        } else if (childAttrType == RelAttrType::WIDTH) {
            parentRect->width.addRelSizeChild(&width);
        } else if (childAttrType == RelAttrType::HEIGHT) {
            parentRect->height.addRelSizeChild(&height);
        }
    }

    if (parentAttrType == RelAttrType::RADIUS) {
        if (childAttrType == RelAttrType::RADIUS) {
            parentRect->cornerRadiusWidth.addRelSizeChild(&cornerRadiusWidth);
            parentRect->cornerRadiusHeight.addRelSizeChild(&cornerRadiusHeight);
        }
    }
}
