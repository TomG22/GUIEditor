#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>

#include "VertexBufferLayout.h"

class VertexBuffer {
	private:
		unsigned int m_RendererID;
	public:
		VertexBuffer(const void* data, unsigned int size);
		~VertexBuffer();

		void Bind() const;
		void Unbind() const;

        void UpdateData(const void* data, unsigned int size, unsigned int offset = 0);
};
