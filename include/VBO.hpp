#ifndef __VBO__
#define __VBO__

#include "core.hpp"
#include <atomic>
#include <vector>

typedef unsigned int GLenum;

class VBO {
public:
    VBO() {
        // 创建VBO
        glGenBuffers(1, &_vbo);
    }

    ~VBO() {
        glDeleteBuffers(1, &_vbo);
    }

    // 绑定VBO
    void bind() {
        CHECK_GL(glBindBuffer(GL_ARRAY_BUFFER, _vbo));
    }

    void unbind() {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    /******************************************************
     * usage:
     * @ GL_STATIC_DRAW ：数据不会或几乎不会改变。
     * @ GL_DYNAMIC_DRAW：数据会被改变很多。
     * @ GL_STREAM_DRAW ：数据每次绘制时都会改变。
     *******************************************************/
    // 填充VBO数据
    void setData(const std::vector<float> vertices, GLenum usage) {
        CHECK_GL(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW));
    }

    operator GLuint() {
        return _vbo;
    }

public:
    GLuint _vbo = 0;

    /*统计已创建的VBO对象的个数, 目前没有使用*/
    static std::atomic<int> counter;
};

std::atomic<int> VBO::counter(0);

#endif