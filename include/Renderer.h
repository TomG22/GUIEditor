#pragma once

#include "Mesh.h"
#include "Shader.h"

class Renderer {
    public:
        Renderer();
        void Clear() const;
        void clearColor(float r, float g, float b, float a) const;
        //void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
        void Draw(const Mesh& mesh, const Shader& shader) const;
};
