#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace check_gl {
const char *opengl_errno_name(GLenum err);
void opengl_check_error(const char *filename, int lineno, const char *expr);
}

#define CHECK_GL(x) do { \
    (x); \
    ::check_gl::opengl_check_error(__FILE__, __LINE__, #x); \
} while (0)


const char *check_gl::opengl_errno_name(GLenum err) {
    switch (err) {
#define PER_GL_ERROR(x) case GL_##x: return #x;
    PER_GL_ERROR(NO_ERROR)
    PER_GL_ERROR(INVALID_ENUM)
    PER_GL_ERROR(INVALID_VALUE)
    PER_GL_ERROR(INVALID_OPERATION)
    PER_GL_ERROR(STACK_OVERFLOW)
    PER_GL_ERROR(STACK_UNDERFLOW)
    PER_GL_ERROR(OUT_OF_MEMORY)
#undef PER_GL_ERROR
    }
    return "unknown error";
}

void check_gl::opengl_check_error(const char *filename, int lineno, const char *expr) {
    GLenum err = glad_glGetError();
    if (err != GL_NO_ERROR) {
        std::cerr << filename << ":" << lineno << ": " << expr << " failed: " << opengl_errno_name(err) << '\n';
        std::terminate();
    }
}