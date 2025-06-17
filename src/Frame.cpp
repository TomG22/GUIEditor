#include "Frame.h"
#include "Texture.h"
#include "VertexArray.h"
#include "IndexBuffer.h"

Frame::Frame() {
    float positions[] = {
        -1.0f, -1.0f,   1.0f, 0.0f, 0.0f, 1.0f,
         1.0f, -1.0f,   0.0f, 1.0f, 0.0f, 1.0f,
         1.0f,  1.0f,   0.0f, 0.0f, 1.0f, 1.0f,
        -1.0f,  1.0f,   1.0f, 1.0f, 1.0f, 1.0f
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    VertexArray* va = new VertexArray;
    VertexBuffer* vb = new VertexBuffer(positions, 4 * 6 * sizeof(float));

    VertexBufferLayout* layout = new VertexBufferLayout;
    layout->Push<float>(2);
    layout->Push<float>(4);
    va->AddBuffer(*vb, *layout);

    IndexBuffer* ib = new IndexBuffer(indices, 6);

    std::vector<Texture> textures;

    background = new Mesh(*va, *ib, textures);
}
