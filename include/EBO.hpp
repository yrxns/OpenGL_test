#ifndef __EBO__
#define __EBO__

#include <atomic>
#include "core.hpp"

class EBO {
public:
    EBO() {
        // 创建EBO
        CHECK_GL(glGenBuffers(1, &_ebo));
    }

    ~EBO() {
        glDeleteBuffers(1, &_ebo);
    }

    void bind() {
        CHECK_GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo));
    }

    void setData(const void *indices, GLenum usage = GL_STATIC_DRAW) {
        // 绑定EBO
        bind();

        /******************************************************
         * usage:
         * @ GL_STATIC_DRAW ：数据不会或几乎不会改变。
         * @ GL_DYNAMIC_DRAW：数据会被改变很多。
         * @ GL_STREAM_DRAW ：数据每次绘制时都会改变。
         *******************************************************/
        // 填充EBO数据
        CHECK_GL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, usage));
    }

    operator GLuint() {
        return _ebo;
    }

public:
    GLuint _ebo = 0;

    /*统计已创建的EBO对象的个数, 目前没有使用*/
    static std::atomic<int> counter;
};

std::atomic<int> EBO::counter(0);


#endif