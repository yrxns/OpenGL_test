#include "core.hpp"
#include "EBO.hpp"

std::atomic<int> EBO::counter(0);

EBO::EBO() {
    // 创建EBO
    CHECK_GL(glGenBuffers(1, &_ebo));
}

EBO::~EBO() {
    glDeleteBuffers(1, &_ebo);
}

void EBO::bind() {
    CHECK_GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo));
}

/******************************************************
 * usage:
 * @ GL_STATIC_DRAW ：数据不会或几乎不会改变。
 * @ GL_DYNAMIC_DRAW：数据会被改变很多。
 * @ GL_STREAM_DRAW ：数据每次绘制时都会改变。
 *******************************************************/
// 填充EBO数据
void EBO::setData(const std::vector<int> indices, GLenum usage) {
    CHECK_GL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices.size(), indices.data(), usage));
}