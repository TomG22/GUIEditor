#pragma once

#include <string>

#include "VertexArray.h"
#include "IndexBuffer.h"
//#include "Texture.h"

class Mesh {
public:
    VertexArray* va;
    VertexBuffer* vb;
    IndexBuffer* ib;

    Mesh(VertexArray* va, VertexBuffer* vb, IndexBuffer* ib);
    //std::vector<Texture>* textures;

    //Mesh(VertexArray&& va, VertexBuffer&& vb, IndexBuffer&& ib);

    void UpdateVertices(const void* data, unsigned int size, unsigned int offset);

    /*void Draw(Shader& shader,
              Camera& camera,
              glm::mat4 uMatrix = glm::mat4(1.0f),
              glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f),
              glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
              glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f));
    */

    /*
    const VertexArray& GetVertexArray() const;
    const IndexBuffer& GetIndexBuffer() const;
    */
};
