#pragma once

#include <vector>

#include "GuiTypes.h"

enum LayoutType {
    WIDGET,
    WINDOW
};

class Layout {
public:
    explicit Layout(LayoutType type);

    // Getter for the type of layout
    LayoutType getLayoutType() const;

    // Clamps the minimum size to >= MIN_SIZE
    float clampMinSize(float v) const;

    // Two points a and b are equal ± HIT_TOL
    bool eqWithTol(float a, float b) const;

    // Point p is in between points low and high ± HIT_TOL
    bool inRangeWithTol(float p, float low, float high) const;

    // Position (x, y) is inside of the layout ± HIT_TOL
    bool inInside(float x, float y) const;

    // Coordinate x or y is on the corresponding edge of the layout ± HIT_TOL
    bool inTop(float y) const;
    bool inBottom(float y) const;
    bool inRight(float x) const;
    bool inLeft(float x) const;

    // Position (x, y) is on the corresponding vertex of the layout ± HIT_TOL
    bool inTopLeft(float x, float y) const;
    bool inTopRight(float x, float y) const;
    bool inBottomLeft(float x, float y) const;
    bool inBottomRight(float x, float y) const;

    // Get the absolute attribute value of the given layout attribute in pixels
    float getAbsXPos() const;
    float getAbsYPos() const;
    float getAbsWidth() const;
    float getAbsHeight() const;

    // Get the relative attribute value of the given layout attribute
    float getRelXPos() const;
    float getRelYPos() const;
    float getRelWidth() const;
    float getRelHeight() const;

    // Set the absolute value of the particular attribute to the given value
    void setAbsXPos(float x);
    void setAbsYPos(float y);
    void setAbsPos(float x, float y);
    void setAbsWidth(float w);
    void setAbsHeight(float h);
    void setAbsSize(float w, float h);

    // Set the relative value of the particular attribute to the given value
    void setRelXPos(float x);
    void setRelYPos(float y);
    void setRelPos(float x, float y);
    void setRelWidth(float w);
    void setRelHeight(float h);
    void setRelSize(float w, float h);

    // Apply transforms to the layout
    void applyTransform(TransformType transformState, float x, float y, float dx, float dy);

    // Recompute the absolute values of the layout based on the bind
    void recompute(Layout* boundParent);

    // Dirty flag for if recomputation is necessary at the render pass
    bool dirty = false;

private:
    // Absolute attributes of the layout in pixels
    float absXPos = 0.0f, absYPos = 0.0f;
    float absWidth = 100.0f, absHeight = 100.0f;

    // Relative attributes of the layout
    float relXPos = 0.0f, relYPos = 0.0f;
    float relWidth = 1.0f, relHeight = 1.0f;

    // Hit tolerance of the layout for cursor events
    const float HIT_TOL = 3.0f;

    // Minimum size that layouts can evaluate to
    const float MIN_SIZE = 1.0f;

    // Type of the layout (screen, screen, widget)
    const LayoutType layoutType;
};
