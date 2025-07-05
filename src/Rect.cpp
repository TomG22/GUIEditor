#pragma once

#include "Rect.h"

Rect::Rect(int width, int height)
    : width(width),
      height(height),
      xOffset(0),
      yOffset(0),
      topLeft(0.0f),
      topRight(0.0f),
      bottomRight(0.0f),
      bottomLeft(0.0f),
      hitTol(5.0f)
{

}

bool Rect::eqWithTol(float a, float b) {
    return std::abs(a - b) <= hitTol;
}

bool Rect::inInside(float x, float y) {
    return x >= topLeft.x - hitTol && x <= bottomRight.x + hitTol &&
           y >= topLeft.y - hitTol && y <= bottomRight.y + hitTol;
}

bool Rect::inTopLeft(float x, float y) {
    return eqWithTol(x, topLeft.x) && eqWithTol(y, topLeft.y);
}

bool Rect::inTopRight(float x, float y) {
    return eqWithTol(x, topRight.x) && eqWithTol(y, topRight.y);
}

bool Rect::inBottomRight(float x, float y) {
    return eqWithTol(x, bottomRight.x) && eqWithTol(y, bottomRight.y);
}

bool Rect::inBottomLeft(float x, float y) {
    return eqWithTol(x, bottomLeft.x) && eqWithTol(y, bottomLeft.y);
}

bool Rect::inTop(float y) {
    return eqWithTol(y, topLeft.y);
}

bool Rect::inRight(float x) {
    return eqWithTol(x, topRight.x);
}

bool Rect::inBottom(float y) {
    return eqWithTol(y, bottomRight.y);
}

bool Rect::inLeft(float x) {
    return eqWithTol(x, bottomLeft.x);
}

void Rect::setAbsTransform(glm::vec2 newTopLeft, glm::vec2 newBottomRight) {
    topLeft = newTopLeft;
    topRight = { newBottomRight.x, newTopLeft.y };
    bottomRight = newBottomRight;
    bottomLeft = { newTopLeft.x, newBottomRight.y };
}

void Rect::setRelPos(float relXOffset, float relYOffset, int winWidth, int winHeight) {
    xOffset = static_cast<int>(winWidth * relXOffset);
    yOffset = static_cast<int>(winHeight * relYOffset);

    topLeft = { xOffset - width / 2, yOffset - height / 2 };
    topRight = { xOffset + width / 2, yOffset - height / 2 };
    bottomRight = { xOffset + width / 2, yOffset + height / 2 };
    bottomLeft = { xOffset - width / 2, yOffset + height / 2 };
}

void Rect::setRelSize(float relWidth, float relHeight, int winWidth, int winHeight) {
    width = static_cast<int>(relWidth * winWidth);
    height = static_cast<int>(relHeight * winHeight);

    assert(width > 0 && height > 0);

    topLeft = { xOffset - width / 2, yOffset - height / 2 };
    topRight = { xOffset + width / 2, yOffset - height / 2 };
    bottomRight = { xOffset + width / 2, yOffset + height / 2 };
    bottomLeft = { xOffset - width / 2, yOffset + height / 2 };
}

void Rect::applyTransform(TransformState transformState, float x, float y, float dx, float dy) {
    switch (transformState) {
        case TransformState::Idle:
            break;

        case TransformState::Move:
            topLeft.x += dx;
            topLeft.y += dy;
            topRight.x += dx;
            topRight.y += dy;
            bottomRight.x += dx;
            bottomRight.y += dy;
            bottomLeft.x += dx;
            bottomLeft.y += dy;
            break;

        case TransformState::ResizeTop:
            topLeft.y = y;
            topRight.y = y;
            break;
        case TransformState::ResizeRight:
            topRight.x = x;
            bottomRight.x = x;
            break;
        case TransformState::ResizeBottom:
            bottomLeft.y = y;
            bottomRight.y = y;
            break;
        case TransformState::ResizeLeft:
            topLeft.x = x;
            bottomLeft.x = x;
            break;

        case TransformState::ResizeTopLeft:
            topLeft.x = x;
            topLeft.y = y;
            bottomLeft.x = x;
            topRight.y = y;
            break;
        case TransformState::ResizeTopRight:
            topRight.x = x;
            topRight.y = y;
            topLeft.y = y;
            bottomRight.x = x;
            break;
        case TransformState::ResizeBottomRight:
            bottomRight.x = x;
            bottomRight.y = y;
            topRight.x = x;
            bottomLeft.y = y;
            break;
        case TransformState::ResizeBottomLeft:
            bottomLeft.x = x;
            bottomLeft.y = y;
            bottomRight.y = y;
            topLeft.x = x;
            break;
    }
}

