#pragma once

#include "Mesh.h"

class Frame {
public:
    glm::vec2 bottomLeft;
    glm::vec2 topRight;
    glm::vec4 bgColor;
    Mesh* bgMesh;

    Frame();
    void createBackground();
};
