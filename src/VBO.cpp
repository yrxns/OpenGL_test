#include "core.hpp"
#include "VBO.hpp"

std::atomic<int> VBO::counter(0);

VBO::VBO() {
    // 创建VBO
    (glGenBuffers(1, &_vbo));
}

VBO::~VBO() {
    glDeleteBuffers(1, &_vbo);
}

void VBO::bind() {
    CHECK_GL(glBindBuffer(GL_ARRAY_BUFFER, _vbo));
}

void VBO::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

/******************************************************
 * usage:
 * @ GL_STATIC_DRAW ：数据不会或几乎不会改变。
 * @ GL_DYNAMIC_DRAW：数据会被改变很多。
 * @ GL_STREAM_DRAW ：数据每次绘制时都会改变。
 *******************************************************/
// 填充VBO数据
void VBO::setData(const std::vector<float> vertices, GLenum usage) {
    CHECK_GL(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW));
}