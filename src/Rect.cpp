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

float Rect::getCornerRadius() const {
    return std::min(cornerRadiusWidth.getAbsValue(),
                    cornerRadiusHeight.getAbsValue());
}

void Rect::applyTransform(TransformType transformState, float x, float y, float dx, float dy) {
    switch (transformState) {
        case TransformType::IDLE:
            break;

        case TransformType::MOVE:
            xPos.forceAbsValue(xPos.getAbsValue() + dx);
            yPos.forceAbsValue(yPos.getAbsValue() + dy);
            break;

        case TransformType::RESIZE_TOP:
            height.forceAbsValue(height.getAbsValue() + yPos.getAbsValue() - y);
            yPos.forceAbsValue(y);
            break;
        case TransformType::RESIZE_RIGHT:
            width.forceAbsValue(x - xPos.getAbsValue());
            break;
        case TransformType::RESIZE_BOTTOM:
            height.forceAbsValue(y - yPos.getAbsValue());
            break;
        case TransformType::RESIZE_LEFT:
            width.forceAbsValue(width.getAbsValue() + xPos.getAbsValue() - x);
            xPos.forceAbsValue(x);
            break;

        case TransformType::RESIZE_TOP_LEFT:
            height.forceAbsValue(height.getAbsValue() + yPos.getAbsValue() - y);
            yPos.forceAbsValue(y);
            width.forceAbsValue(width.getAbsValue() + xPos.getAbsValue() - x);
            xPos.forceAbsValue(x);
            break;
        case TransformType::RESIZE_TOP_RIGHT:
            height.forceAbsValue(height.getAbsValue() + yPos.getAbsValue() - y);
            yPos.forceAbsValue(y);
            width.forceAbsValue(x - xPos.getAbsValue());
            break;
        case TransformType::RESIZE_BOTTOM_RIGHT:
            width.forceAbsValue(x - xPos.getAbsValue());
            height.forceAbsValue(y - yPos.getAbsValue());
            break;
        case TransformType::RESIZE_BOTTOM_LEFT:
            height.forceAbsValue(y - yPos.getAbsValue());
            width.forceAbsValue(width.getAbsValue() + xPos.getAbsValue() - x);
            xPos.forceAbsValue(x);
            break;
    }
}
