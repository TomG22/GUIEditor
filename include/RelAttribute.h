#pragma once

#include <unordered_set>

class RelAttribute {
public:
    RelAttribute();

    bool isBound() const;

    bool recursiveSearch(RelAttribute* node) const;

    void bindRelChild(RelAttribute* node);
    void unbindRelChild(RelAttribute* node);

    float getAbsValue() const;
    float getRelValue() const;
    float getScale() const;

    void setAbsValue(float newAbsValue);
    void forceAbsValue(float newAbsValue);
    void setScale(float newScale);
    void forceScale(float newScale);

private:
    float absValue;
    float scale;
    RelAttribute* relParent;
    std::unordered_set<RelAttribute*> relChildren;
};
