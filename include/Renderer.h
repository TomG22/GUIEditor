#pragma once

#include <glad/glad.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

/*Error Checks*/
#define ASSERT(x) if (!(x))(printf("ASSERT failed\n"));
#define GLCall(x) GLClearError();/*Wrappable error check function*/\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__));

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer {
    public:
        void Clear() const;
        void clearColor(float r, float g, float b, float a) const;
        void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};