#pragma once

#include "Mesh.h"

struct Vec2 {
    float x;
    float y;
};

class Frame {
private:
    Vec2 bottomLeft;
    Vec2 topRight;

public:
    Frame();

    Mesh* background;
};
