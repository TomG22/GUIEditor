#include "GLDebug.h"
#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
    GLCall(glGenBuffers(1, &m_RendererID));

    if (m_RendererID == 0) {
        throw std::runtime_error("OpenGL Error: Failed to generate vertex buffer");
    }

    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer() {
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

void VertexBuffer::Bind() const {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::Unbind() const {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void VertexBuffer::UpdateData(const void* data, unsigned int size, unsigned int offset) {
    if (!data) {
        std::cerr << "VertexBuffer ERROR]: UpdateData received null data pointer" << std::endl;
        return;
    }

    if (m_RendererID == 0) {
        std::cerr << "VertexBuffer ERROR]: UpdateData called with a buffer of id 0" << std::endl;
        return;
    }

    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
    GLCall(glBufferSubData(GL_ARRAY_BUFFER, offset, size, data));
}
