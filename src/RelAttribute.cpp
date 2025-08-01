#include <cassert>

#include "RelAttribute.h"

RelAttribute::RelAttribute()
    : absValue(0.0f),
      scale(0.0f),
      relParent(nullptr)
{}

bool RelAttribute::isBound() const {
    return relParent != nullptr;
}

bool RelAttribute::recursiveSearch(RelAttribute* node) const {
    if (relChildren.empty()) {
        return false;
    }

    for (RelAttribute* childNode : relChildren) {
        if (childNode == node) {
            return true;
        }

        if (recursiveSearch(childNode)) {
            return true;
        }
    }

    return false;
}

void RelAttribute::bindRelChild(RelAttribute* node) {
    assert(!relChildren.contains(node) &&
           "RelAttribute ERROR: Tried to bind a child that is already bound to this node");

    assert(!node->recursiveSearch(this) &&
           "RelAttribute ERROR: Tried to bind a child that would create a dependency cycle");

    assert(!node->relParent &&
           "RelAttribute ERROR: Tried to bind a child that is already bound to a different node");

    node->relParent = this;

    relChildren.insert(node);
}

void RelAttribute::unbindRelChild(RelAttribute* node) {
    assert(relChildren.contains(node) &&
           "RelAttribute ERROR: Tried to unbind a child that hasn't been bound");

    node->relParent = nullptr;

    relChildren.erase(node);
}

float RelAttribute::getAbsValue() const {
    return absValue;
}

float RelAttribute::getRelValue() const {
    return relParent->getAbsValue();
}

float RelAttribute::getScale() const {
    return scale;
}

void RelAttribute::recursiveUpdate() {
    absValue = scale * relParent->getAbsValue();
}

void RelAttribute::setAbsValue(float newAbsValue) {
    assert(!relParent &&
           "RelAttribute ERROR: Tried to set the absolute value of a node that is relatively bound");

    absValue = newAbsValue;

    for (RelAttribute* child : relChildren) {
        child->recursiveUpdate();
    }
}

void RelAttribute::forceAbsValue(float newAbsValue) {
    absValue = newAbsValue;

    if (relParent) {
        scale = absValue / relParent->getAbsValue();
    }

    for (RelAttribute* child : relChildren) {
        child->recursiveUpdate();
    }
}

void RelAttribute::setScale(float newScale) {
    assert(relParent &&
           "RelAttribute ERROR: Tried to set the scale of a node that is not relatively bound");

    scale = newScale;
    absValue = scale * relParent->getAbsValue();

    for (RelAttribute* child : relChildren) {
        child->recursiveUpdate();
    }
}

void RelAttribute::forceScale(float newScale) {
    scale = newScale;

    if (relParent) {
        absValue = scale * relParent->getAbsValue();
    }

    for (RelAttribute* child : relChildren) {
        child->recursiveUpdate();
    }
}
