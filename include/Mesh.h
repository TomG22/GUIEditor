#pragma once

#include <string>

#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Camera.h"
#include "Texture.h"

class Mesh {
public:
	VertexArray& va;
	IndexBuffer& ib;
	std::vector<Texture>& textures;

	Mesh(VertexArray& va, IndexBuffer& ib, std::vector<Texture>& textures);

	void Draw(
		Shader& shader,
		Camera& camera,
		glm::mat4 uMatrix = glm::mat4(1.0f),
		glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
		glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f)
	);
};