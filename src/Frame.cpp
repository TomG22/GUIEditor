#include "Frame.h"
#include "Texture.h"
#include "VertexArray.h"
#include "IndexBuffer.h"

Frame::Frame() {

}

void Frame::createBackground() {
    glm::vec2 bottomRight = {topRight.x, bottomLeft.y};
    glm::vec2 topLeft = {bottomLeft.x, topRight.y};

    Vertex2D vertices[] = {
        {bottomLeft,     bgColor},
        {bottomRight,    bgColor},
        {topRight,       bgColor},
        {topLeft,        bgColor}
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    VertexArray* va = new VertexArray;
    VertexBuffer* vb = new VertexBuffer(vertices, sizeof(vertices));

    VertexBufferLayout* layout = new VertexBufferLayout;
    layout->Push<Vertex2D>(1);
    va->AddBuffer(*vb, *layout);

    IndexBuffer* ib = new IndexBuffer(indices, 6);

    std::vector<Texture> textures;

    bgMesh = new Mesh(*va, *ib, textures);
}
