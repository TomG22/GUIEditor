#pragma once

#include <glm/glm.hpp>

struct Vertex2D {
    glm::vec2 position;
    glm::vec4 color;
};

class VertexBuffer {
	private:
		unsigned int m_RendererID;
	public:
		VertexBuffer(const void* data, unsigned int size);
		~VertexBuffer();

		void Bind() const;
		void Unbind() const;
};
