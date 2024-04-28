// #include "core.hpp"
#include "Shader.hpp"

#include<fstream>
#include<sstream>
#include<iostream>

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
    //声明装入shader代码字符串的两个string
    std::string vertexCode;
    std::string fragmentCode;

    //声明用于读取vs跟fs文件的inFileStream
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    //保证ifstream遇到问题的时候可以抛出异常
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        //1 打开文件
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        
        //2 将文件输入流当中的字符串输入到stringStream里面
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        //3 关闭文件
        vShaderFile.close();
        fShaderFile.close();

        //4 将字符串从stringStream当中读取出来，转化到code String当中
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure& e) {
        std::cout << "ERROR: Shader File Error: " << e.what() << std::endl;
    }

    const char* vertexShaderSource = vertexCode.c_str();
    const char* fragmentShaderSource = fragmentCode.c_str();
    //1 创建Shader程序（vs、fs）
    GLuint vertex, fragment;
    vertex = glCreateShader(GL_VERTEX_SHADER);
    fragment = glCreateShader(GL_FRAGMENT_SHADER);

    //2 为shader程序输入shader代码
    glShaderSource(vertex, 1, &vertexShaderSource, NULL);
    glShaderSource(fragment, 1, &fragmentShaderSource, NULL);

    //3 执行shader代码编译 
    glCompileShader(vertex);
    //检查vertex编译结果
    checkShaderErrors(vertex, "COMPILE");
    
    glCompileShader(fragment);
    //检查fragment编译结果
    checkShaderErrors(fragment, "COMPILE");
    
    //4 创建一个Program壳子
    mProgram = glCreateProgram();

    //6 将vs与fs编译好的结果放到program这个壳子里
    glAttachShader(mProgram, vertex);
    glAttachShader(mProgram, fragment);

    //7 执行program的链接操作，形成最终可执行shader程序
    glLinkProgram(mProgram);

    //检查链接错误
    checkShaderErrors(mProgram, "LINK");

    //清理
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}
Shader::~Shader() {
    glDeleteProgram(mProgram);
}

//开始使用当前Shader
void Shader::begin() {
    CHECK_GL(glUseProgram(mProgram));
}

//结束使用当前Shader
void Shader::end() {
    CHECK_GL(glUseProgram(0));
}

void Shader::setFloat(const std::string& name, float value) {
    GLint location = glGetUniformLocation(mProgram, name.c_str());

    CHECK_GL(glUniform1f(location, value));
}

void Shader::setVector3(const std::string& name, float x, float y, float z) {
    GLint location = glGetUniformLocation(mProgram, name.c_str());
    
    CHECK_GL(glUniform3f(location, x, y, z));
}
void Shader::setVector3(const std::string& name, const float* values) {
    GLint location = glGetUniformLocation(mProgram, name.c_str());

    CHECK_GL(glUniform3fv(location, 1, values));
}

void Shader::setVector4(const std::string& name, float x, float y, float z, float w) {
    GLint location = glGetUniformLocation(mProgram, name.c_str());
    
    CHECK_GL(glUniform4f(location, x, y, z, w));
}
void Shader::setVector4(const std::string& name, const float* values) {
    GLint location = glGetUniformLocation(mProgram, name.c_str());

    CHECK_GL(glUniform4fv(location, 1, values));
}

void Shader::setInt(const std::string& name, int value) {
    GLint location = glGetUniformLocation(mProgram, name.c_str());

    CHECK_GL(glUniform1i(location, value));
}

void Shader::setMatrix4x4(const std::string& name, glm::mat4 value) {
    GLint location = glGetUniformLocation(mProgram, name.c_str());
    
    CHECK_GL(glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value)));
}

void Shader::checkShaderErrors(GLuint target,std::string type) {
        int success = 0;
        char infoLog[1024];

        if (type == "COMPILE") {
            glGetShaderiv(target, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(target, 1024, NULL, infoLog);
                std::cout << "Error: SHADER COMPILE ERROR" << "\n" << infoLog << std::endl;
            }
        }
        else if (type == "LINK") {
            glGetProgramiv(target, GL_LINK_STATUS, &success);
            if (!success) {
                glGetProgramInfoLog(target, 1024, NULL, infoLog);
                std::cout << "Error: SHADER LINK ERROR " << "\n" << infoLog << std::endl;
            }
        }
        else {
            std::cout << "Error: Check shader errors Type is wrong" << std::endl;
        }
    }