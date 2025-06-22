#include "GLDebug.h"

void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}

void printGLError(GLenum error) {
    switch (error) {
        case GL_INVALID_ENUM:
            std::cerr << "GL_INVALID_ENUM";
            break;
        case GL_INVALID_VALUE:
            std::cerr << "GL_INVALID_VALUE";
            break;
        case GL_INVALID_OPERATION:
            std::cerr << "GL_INVALID_OPERATION";
            break;
        case GL_OUT_OF_MEMORY:
            std::cerr << "GL_OUT_OF_MEMORY";
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            std::cerr << "GL_INVALID_FRAMEBUFFER_OPERATION";
            break;
        default:
            std::cerr << "Unknown Error Code: " << error;
            break;
    }
}

bool GLLogCall(const char* function, const char* file, int line) {
    while (GLenum error = glGetError()) {
        std::cout << "OpenGL ERROR: ";
        printGLError(error);
        std::cout << " in function " << function << " in file " << file << " on line " << line << std::endl;
        return false;
    }
    return true;
}

bool GLLogCall() {
    while (GLenum error = glGetError()) {
        std::cout << "OpenGL ERROR: ";

        printGLError(error);

        std::cout << std::endl;
        return false;
    }
    return true;
}
