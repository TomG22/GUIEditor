#pragma once

#include <algorithm>

#include "Rect.h"

Rect::Rect()
    : topLeft(0.0f),
      topRight(0.0f),
      bottomRight(0.0f),
      bottomLeft(0.0f),
      hitTol(5.0f),
      absRadius(0.0f),
      relRadius(0.0f),
      relRadiusFlag(true)
{}

float Rect::getWidth() const {
    return topRight.x - topLeft.x;
}

float Rect::getHeight() const {
    return bottomLeft.y - topLeft.y;
}

bool Rect::eqWithTol(float a, float b) const {
    return std::abs(a - b) <= hitTol;
}

bool Rect::inInside(float x, float y) const {
    return x >= topLeft.x - hitTol && x <= bottomRight.x + hitTol &&
           y >= topLeft.y - hitTol && y <= bottomRight.y + hitTol;
}

bool Rect::inTopLeft(float x, float y) const {
    return eqWithTol(x, topLeft.x) && eqWithTol(y, topLeft.y);
}

bool Rect::inTopRight(float x, float y) const {
    return eqWithTol(x, topRight.x) && eqWithTol(y, topRight.y);
}

bool Rect::inBottomRight(float x, float y) const {
    return eqWithTol(x, bottomRight.x) && eqWithTol(y, bottomRight.y);
}

bool Rect::inBottomLeft(float x, float y) const {
    return eqWithTol(x, bottomLeft.x) && eqWithTol(y, bottomLeft.y);
}

bool Rect::inTop(float y) const {
    return eqWithTol(y, topLeft.y);
}

bool Rect::inRight(float x) const {
    return eqWithTol(x, topRight.x);
}

bool Rect::inBottom(float y) const {
    return eqWithTol(y, bottomRight.y);
}

bool Rect::inLeft(float x) const {
    return eqWithTol(x, bottomLeft.x);
}

void Rect::setAbsTransform(glm::vec2 newTopLeft, glm::vec2 newBottomRight) {
    topLeft = newTopLeft;

    topRight = {newBottomRight.x, newTopLeft.y};
    bottomRight = newBottomRight;
    bottomLeft = {newTopLeft.x, newBottomRight.y};
}

void Rect::setRelPos(float relXOffset, float relYOffset, int winWidth, int winHeight) {
    float width = getWidth();
    float height = getHeight();

    topLeft.x = (winWidth * relXOffset) / 2;
    topLeft.y = (winHeight * relYOffset) / 2;

    topRight = {topLeft.x + width, topLeft.y};
    bottomRight = {topLeft.x + width, topLeft.y + height};
    bottomLeft = {topLeft.x, topLeft.y + height};
}

void Rect::setRelSize(float relWidth, float relHeight, int winWidth, int winHeight) {
    float width = relWidth * winWidth;
    float height = relHeight * winHeight;

    assert(width > 0 && height > 0);

    topRight = {topLeft.x + width, topLeft.y};
    bottomRight = {topLeft.x + width, topLeft.y + height};
    bottomLeft = {topLeft.x, topLeft.y + height};
}

void Rect::setRelRadius(float radius) {
    relRadius = radius;
    relRadiusFlag = true;

    absRadius = relRadius * std::min(getWidth(), getHeight());
}

void Rect::setAbsRadius(float radius) {
    absRadius = radius;
    relRadiusFlag = false;
}


void Rect::applyTransform(TransformState transformState, float x, float y, float dx, float dy) {
    switch (transformState) {
        case TransformState::Idle:
            break;

        case TransformState::Move: {
            topLeft.x += dx;
            topLeft.y += dy;
            bottomRight.x += dx;
            bottomRight.y += dy;
            break;
        }

        case TransformState::ResizeTop:
            topLeft.y = y;
            break;

        case TransformState::ResizeRight:
            bottomRight.x = x;
            break;

        case TransformState::ResizeBottom:
            bottomRight.y = y;
            break;

        case TransformState::ResizeLeft:
            topLeft.x = x;
            break;

        case TransformState::ResizeTopLeft:
            topLeft.x = x;
            topLeft.y = y;
            break;

        case TransformState::ResizeTopRight:
            bottomRight.x = x;
            topLeft.y = y;
            break;

        case TransformState::ResizeBottomRight:
            bottomRight.x = x;
            bottomRight.y = y;
            break;

        case TransformState::ResizeBottomLeft:
            topLeft.x = x;
            bottomRight.y = y;
            break;
    }

    topRight = { bottomRight.x, topLeft.y };
    bottomLeft = { topLeft.x, bottomRight.y };

    if (relRadiusFlag) {
        absRadius = relRadius * std::min(getWidth(), getHeight());
    }
}
