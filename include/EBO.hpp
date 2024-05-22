#ifndef __EBO__
#define __EBO__

#include "core.hpp"
#include <atomic>
#include <vector>

class EBO {
public:
    EBO() {
        // 创建EBO
        CHECK_GL(glGenBuffers(1, &_ebo));
    }

    ~EBO() {
        glDeleteBuffers(1, &_ebo);
    }

    // 绑定EBO
    void bind() {
        CHECK_GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo));
    }

    void unbind() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    /******************************************************
     * usage:
     * @ GL_STATIC_DRAW ：数据不会或几乎不会改变。
     * @ GL_DYNAMIC_DRAW：数据会被改变很多。
     * @ GL_STREAM_DRAW ：数据每次绘制时都会改变。
     *******************************************************/
    // 填充EBO数据
    void setData(const std::vector<int> indices, GLenum usage) {
        CHECK_GL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices.size(), indices.data(), usage));
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