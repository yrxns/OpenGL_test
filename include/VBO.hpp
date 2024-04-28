#ifndef __VBO__
#define __VBO__

#include <atomic>
#include <vector>

typedef unsigned int GLenum;

class VBO {
public:
    VBO();

    ~VBO();

    // 绑定VBO
    void bind();

    /******************************************************
     * usage:
     * @ GL_STATIC_DRAW ：数据不会或几乎不会改变。
     * @ GL_DYNAMIC_DRAW：数据会被改变很多。
     * @ GL_STREAM_DRAW ：数据每次绘制时都会改变。
     *******************************************************/
    // 填充VBO数据
    void setData(const std::vector<float> vertices, GLenum usage);

    operator GLuint() {
        return _vbo;
    }

public:
    GLuint _vbo = 0;

    /*统计已创建的VBO对象的个数, 目前没有使用*/
    static std::atomic<int> counter;
};

#endif