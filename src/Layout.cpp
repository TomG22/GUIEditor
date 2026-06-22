#include <stdexcept>
#include <algorithm>
#include "Layout.h"

Layout::Layout(LayoutType type) : layoutType(type) {}

LayoutType Layout::getLayoutType() const { return layoutType; }

float Layout::clampMinSize(float v) const {
    return std::max(MIN_SIZE, v);
}

bool Layout::eqWithTol(float a, float b) const {
    return std::abs(a - b) <= HIT_TOL;
}

bool Layout::inRangeWithTol(float p, float low, float high) const {
    return p >= low - HIT_TOL && p <= high + HIT_TOL;
}

bool Layout::inInside(float x, float y) const {
    return inRangeWithTol(x, absXPos, absXPos + absWidth) &&
           inRangeWithTol(y, absYPos, absYPos + absHeight);
}

bool Layout::inTop(float y) const {
    return eqWithTol(y, absYPos);
}

bool Layout::inRight(float x) const {
    return eqWithTol(x, absXPos + absWidth);
}

bool Layout::inBottom(float y) const {
    return eqWithTol(y, absYPos + absHeight);
}

bool Layout::inLeft(float x) const {
    return eqWithTol(x, absXPos);
}

bool Layout::inTopLeft(float x, float y) const {
    return eqWithTol(x, getAbsXPos()) && eqWithTol(y, getAbsYPos());
}

bool Layout::inTopRight(float x, float y) const {
    return eqWithTol(x, absXPos + absWidth) && eqWithTol(y, absYPos);
}

bool Layout::inBottomLeft(float x, float y) const {
    return eqWithTol(x, absXPos) && eqWithTol(y, absYPos + absHeight);
}

bool Layout::inBottomRight(float x, float y) const {
    return eqWithTol(x, absXPos + absWidth) && eqWithTol(y, absYPos + absHeight);
}

float Layout::getAbsXPos() const { return absXPos; }
float Layout::getAbsYPos() const { return absYPos; }
float Layout::getAbsWidth() const { return absWidth; }
float Layout::getAbsHeight() const { return absHeight; }

float Layout::getRelXPos() const { return relXPos; }
float Layout::getRelYPos() const { return relYPos; }
float Layout::getRelWidth() const { return relWidth; }
float Layout::getRelHeight() const { return relHeight; }

void Layout::setAbsXPos(float x) {
    absXPos = x;
    dirty = true;
}

void Layout::setAbsYPos(float y) {
    absYPos = y;
    dirty = true;
}

void Layout::setAbsPos(float x, float y) {
    absXPos = x;
    absYPos = y;
    dirty = true;
}

void Layout::setAbsWidth(float w) {
    absWidth = clampMinSize(w);
    dirty = true;
}

void Layout::setAbsHeight(float h) {
    absHeight = clampMinSize(h);
    dirty = true;
}

void Layout::setAbsSize(float w, float h) {
    absWidth = clampMinSize(w);
    absHeight = clampMinSize(h);
    dirty = true;
}

void Layout::setRelXPos(float x) {
    relXPos = x;
    dirty = true;
}

void Layout::setRelYPos(float y) {
    relYPos = y;
    dirty = true;
}

void Layout::setRelPos(float x, float y) {
    relXPos = x;
    relYPos = y;
    dirty = true;
}

void Layout::setRelWidth(float w) {
    relWidth = w;
    dirty = true;
}

void Layout::setRelHeight(float h) {
    relHeight = h;
    dirty = true;
}

void Layout::setRelSize(float w, float h) {
    relWidth = w;
    relHeight = h;
    dirty = true;
}

void Layout::recompute(Layout* boundParent) {
    if (boundParent == nullptr)
        return;

    if (boundParent->getLayoutType() == LayoutType::WIDGET) {
        absXPos = relXPos * boundParent->getAbsWidth() + boundParent->getAbsXPos();
        absYPos = relYPos * boundParent->getAbsHeight() + boundParent->getAbsYPos();

        absWidth  = clampMinSize(relWidth * boundParent->getAbsWidth());
        absHeight = clampMinSize(relHeight * boundParent->getAbsHeight());

    } else if (boundParent->getLayoutType() == LayoutType::WINDOW) {
        absXPos = relXPos * boundParent->getAbsWidth();
        absYPos = relYPos * boundParent->getAbsHeight();

        absWidth  = clampMinSize(relWidth * boundParent->getAbsWidth());
        absHeight = clampMinSize(relHeight * boundParent->getAbsHeight());
    }

    dirty = false;
}
