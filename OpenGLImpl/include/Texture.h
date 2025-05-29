#pragma once

#include <glad/glad.h>
#include <stb/stb_image.h>

#include "Renderer.h"

class Texture {
public:
	GLuint ID;
	const char* type;
	GLuint unit;

	Texture(const char* image, const char* texType, GLuint slot);
	~Texture();

	void bindTexUnit(Shader& shader, const std::string& uniform, GLuint unit);
	void Bind();
	void Unbind();
};