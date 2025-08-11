#pragma once

#include "RelAttr.h"

class RelSizeAttr;

class RelPosAttr : public RelAttr {
    friend class RelSizeAttr;
public:
    RelPosAttr();

    bool isRelBound() const override;

    void setAbsValue(float newAbsValue) override;
    void setSizeScale(float newSizeScale) override; 

    void setRelPosParent(RelPosAttr* posAttr);
    void removeRelPosParent();

    void setRelSizeParent(RelSizeAttr* sizeAttr);
    void removeRelSizeParent();

    void addRelPosChild(RelPosAttr* posAttr);
    void removeRelPosChild(RelPosAttr* posAttr);

private:
    void calcAbsValue() override;
    void calcSizeScale() override;

    RelPosAttr* relPosParent;
    RelSizeAttr* relSizeParent;

    std::unordered_set<RelPosAttr*> relPosChildren;
};
