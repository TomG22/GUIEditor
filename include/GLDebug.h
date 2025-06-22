#include <iostream>
#include <glad/glad.h>

#define ASSERT(x) if (!(x))(printf("GLCall ASSERT failed\n"));
#define GLCall(x) x; ASSERT(GLLogCall(#x, __FILE__, __LINE__));

void GLClearError();

void printGLError(GLenum error);

bool GLLogCall();

bool GLLogCall(const char* function, const char* file, int line);
