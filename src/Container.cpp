#include "Container.h"
#include <iostream>
#include <glm/glm.hpp>
#include <vector>

Container::Container(xPos, yPos, width, height)
	: xPos(xPos), yPos(yPos), zPos(0),
	  width(width), height(height) {
	float positions[] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f
    };

	unsigned int indices = {
        0, 1, 2,
        2, 3, 0
    };

	background = Mesh(vertices, indices, 0);

	std::vector<Container> subContainers = std::vector<Container>();

	bool isPosInBounds(float x, float y) { return (xPos <= x && x <= xPos + width && yPos <= yPos && y <= yPos + height) };

	bool onHover() {
		return true;
	}

	bool Draw() {
		background.Draw();
	}
};