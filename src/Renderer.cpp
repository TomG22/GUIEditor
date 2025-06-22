#include <iostream>

#include "GLDebug.h"
#include "Renderer.h"

Renderer::Renderer() {
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "Renderer ERROR: OpenGL Error detected: ";
        printGLError(err);
        std::cerr << std::endl;
    }
}

/*
void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const {
    shader.Bind();
    va.Bind();
    ib.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}
*/

void Renderer::Draw(const Mesh& mesh, const Shader& shader) const {
    shader.Bind();
    mesh.va->Bind();
    mesh.ib->Bind();
    GLCall(glDrawElements(GL_TRIANGLES, mesh.ib->GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear() const{
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::clearColor(float r, float g, float b, float a) const{
    GLCall(glClearColor(r, g, b, a));
}
