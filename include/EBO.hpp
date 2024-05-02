#ifndef __EBO__
#define __EBO__

#include <atomic>
#include <vector>

typedef unsigned int GLenum;

class EBO {
public:
    EBO();

    ~EBO();

    // 绑定EBO
    void bind();

    void unbind();

    /******************************************************
     * usage:
     * @ GL_STATIC_DRAW ：数据不会或几乎不会改变。
     * @ GL_DYNAMIC_DRAW：数据会被改变很多。
     * @ GL_STREAM_DRAW ：数据每次绘制时都会改变。
     *******************************************************/
    // 填充EBO数据
    void setData(const std::vector<int> indices, GLenum usage);

    operator GLuint() {
        return _ebo;
    }

public:
    GLuint _ebo = 0;

    /*统计已创建的EBO对象的个数, 目前没有使用*/
    static std::atomic<int> counter;
};

#endif