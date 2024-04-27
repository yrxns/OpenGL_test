#ifndef __VBO__
#define __VBO__

#include <atomic>
#include "core.hpp"

class VBO {
public:
    VBO() {
        // 创建VBO
        CHECK_GL(glGenBuffers(1, &_vbo));
    }

    ~VBO() {
        glDeleteBuffers(1, &_vbo);
    }

    void bind() {
        CHECK_GL(glBindBuffer(GL_ARRAY_BUFFER, _vbo));
    }

    void setData(const void *vertices, GLenum usage = GL_STATIC_DRAW) {
        // 绑定VBO
        bind();

        /******************************************************
         * usage:
         * @ GL_STATIC_DRAW ：数据不会或几乎不会改变。
         * @ GL_DYNAMIC_DRAW：数据会被改变很多。
         * @ GL_STREAM_DRAW ：数据每次绘制时都会改变。
         *******************************************************/
        // 填充VBO数据
        CHECK_GL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, usage));
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