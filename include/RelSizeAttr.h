#pragma once

#include "RelAttr.h"

class RelPosAttr;

class RelSizeAttr : public RelAttr {
public:
    RelSizeAttr();

    bool isRelBound() const override;

    void setAbsValue(float newAbsValue) override;
    void setSizeScale(float newSizeScale) override; 

    void setRelSizeParent(RelSizeAttr* sizeAttr);
    void removeRelSizeParent();

    void addRelPosChild(RelPosAttr* posAttr);
    void removeRelPosChild(RelPosAttr* posAttr);

    void addRelSizeChild(RelSizeAttr* sizeAttr);
    void removeRelSizeChild(RelSizeAttr* sizeAttr);

private:
    void calcAbsValue() override;
    void calcSizeScale() override;

    RelSizeAttr* relSizeParent;

    std::unordered_set<RelPosAttr*> relPosChildren;
    std::unordered_set<RelSizeAttr*> relSizeChildren;
};
