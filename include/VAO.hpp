#ifndef __VAO__
#define __VAO__

#include <atomic>

class VAO {
public:
    VAO();
    ~VAO();

    // 绑定VAO
    void begin();

    // 解绑当前 VAO
    void end();
    
    /******************************************************
     * @ index      ：指定要配置的顶点属性
     * @ size       ：指定顶点属性的大小
     * @ type       ：指定数据的类型  GL_FLOAT
     * @ normalized ：是否希望数据被标准化 GL_TRUE GL_FALSE
     * @ stride     ：指定连续的顶点属性组之间的间隔
     * @ pointer    ：起始位置的偏移量
     *******************************************************/
    // 配置顶点属性指针
    void vertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);

    operator GLuint() {
        return _vao;
    }

public:
    GLuint _vao = 0;
    /*统计已创建的VAO对象的个数, 目前没有使用*/
    static std::atomic<int> counter;
};

#endif