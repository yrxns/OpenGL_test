#ifndef __SHADER__
#define __SHADER__

#include "core.hpp"
#include <string>

class Shader {
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();
	
    //开始使用当前Shader
	void begin();

    //结束使用当前Shader
	void end();

	void setFloat(const std::string& name, float value);

	void setVector3(const std::string& name, float x, float y, float z);
	void setVector3(const std::string& name, const float* values);
	void setVector3(const std::string& name, glm::vec3 value);

	void setVector4(const std::string& name, float x, float y, float z, float w);
	void setVector4(const std::string& name, const float* values);

	void setInt(const std::string& name, int value);

	void setMatrix4x4(const std::string& name, glm::mat4 value);

	operator GLuint() {
		return mProgram;
    }
private:
	//shader program
	//type:COMPILE LINK
	void checkShaderErrors(GLuint target,std::string type);

private:
	GLuint mProgram{ 0 };
};

#endif