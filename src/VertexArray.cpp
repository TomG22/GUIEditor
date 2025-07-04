#include <iostream>

#include "GLDebug.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"

VertexArray::VertexArray() {
	GLCall(glGenVertexArrays(1, &m_RendererID));

    if (m_RendererID == 0) {
        throw std::runtime_error("OpenGL Error: Failed to generate vertex array");
    }
}

VertexArray::~VertexArray() {
	GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {
	Bind();
	vb.Bind();
	const std::vector<VertexBufferElement> elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++) {
		const VertexBufferElement element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
        const void* glOffset = reinterpret_cast<const void*>(static_cast<std::uintptr_t>(offset));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), glOffset));
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}

void VertexArray::Bind() const {
	GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::Unbind() const {
	GLCall(glBindVertexArray(0));
}
