#pragma once

#include <vector>
#include "Mesh.h"

/**
 * Class description...
 */

class Container {
public:
	std::vector<Container> subContainers;

	Container(float xPos, float yPos, float width, float height);
	Mesh getBackground();

	float xPos;
	float yPos;
	float zPos = 0.0;
	float width;
	float height;
	Mesh background;

	bool isPosInBounds(float x, float y);

};
