#pragma once

#include <glm/glm.hpp>
#include <stdexcept>

#include <vector>
#include "Renderer.h"
#include "VertexBuffer.h"

struct VertexBufferElement {
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int GetSizeOfType(unsigned int type) {
        switch (type) {
            case GL_FLOAT:          return 4;
            case GL_UNSIGNED_INT:   return 4;
            case GL_UNSIGNED_BYTE:  return 1;
        }
        throw std::runtime_error("Unknown OpenGL type");
    }
};

class VertexBufferLayout {
private:
    std::vector<VertexBufferElement> m_Elements;
    unsigned int m_Stride;

public:
    VertexBufferLayout() : m_Stride(0) {}

    // Templated member function for general case
    template<typename T>
    void Push(unsigned int count) {
        static_assert(sizeof(T) == 0, "Unsupported type for VertexBufferLayout::Push");
    }

    const std::vector<VertexBufferElement>& GetElements() const { return m_Elements; }
    unsigned int GetStride() const { return m_Stride; }
};

// Specialization definitions outside of the class definition
template<>
inline void VertexBufferLayout::Push<float>(unsigned int count) {
    m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
    m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
}

template<>
inline void VertexBufferLayout::Push<unsigned int>(unsigned int count) {
    m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
    m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
}

template<>
inline void VertexBufferLayout::Push<unsigned char>(unsigned int count) {
    m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
    m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
}

template<>
inline void VertexBufferLayout::Push<glm::vec2>(unsigned int count) {
    m_Elements.push_back({ GL_FLOAT, count * 2, GL_FALSE });
    m_Stride += count * 2 * VertexBufferElement::GetSizeOfType(GL_FLOAT);
}

template<>
inline void VertexBufferLayout::Push<glm::vec3>(unsigned int count) {
    m_Elements.push_back({ GL_FLOAT, count * 3, GL_FALSE });
    m_Stride += count * 3 * VertexBufferElement::GetSizeOfType(GL_FLOAT);
}

template<>
inline void VertexBufferLayout::Push<glm::vec4>(unsigned int count) {
    m_Elements.push_back({ GL_FLOAT, count * 4, GL_FALSE });
    m_Stride += count * 4 * VertexBufferElement::GetSizeOfType(GL_FLOAT);
}

template<>
inline void VertexBufferLayout::Push<Vertex2D>(unsigned int count) {
    for (unsigned int i = 0; i < count; i++) {
        Push<glm::vec2>(1); // (x, y) position
        Push<glm::vec4>(1); // (r, g, b, a) color
    }
}
