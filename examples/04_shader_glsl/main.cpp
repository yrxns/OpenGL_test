#include "core.hpp"
#include <iostream>
#include "Application.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "VAO.hpp"
#include "VBO.hpp"
#include "EBO.hpp"
#include <vector>

const char *vertexShaderSource ="#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos, 1.0);\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "uniform vec4 ourColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = ourColor;\n"
    "}\n\0";

int main() {
	Application *app = Application::getInstance();
	if (!app->init()) {
		return -1;
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	ImGui::StyleColorsDark();
	const char* glsl_version = "#version 330";
	ImGui_ImplGlfw_InitForOpenGL(*app, true);
	ImGui_ImplOpenGL3_Init(glsl_version);


    // 定义顶点数组
  std::vector<float> vertices = {
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
         0.0f,  0.5f, 0.0f   // top 
  };

  VBO vbo; VAO vao;
  vao.bind(); vbo.bind();

  vbo.setData(vertices, GL_STATIC_DRAW);
  vao.vertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

  vbo.unbind(); vao.unbind();


  // 创建顶点和片段着色器
  unsigned int vertexShader, fragmentShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

  // 附加着色器代码
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  // 检测是否编译成功
  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR:SHADER::VERTEX::COMPILATION_FAILED\n"
              << std::endl;
  }

  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cout << "ERROR:SHADER::FRAGMENT::COMPILATION_FAILED\n"
              << std::endl;
  }

  // 创建程序对象
  unsigned int shaderProgram;
  shaderProgram = glCreateProgram();
  // 将着色器附加到程序对象上
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);

  // 链接
  glLinkProgram(shaderProgram);
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success)
  {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR:SHADER_PROGRAM_LINK_FAILED" << std::endl;
  }

  // 使用着色器程序
  glUseProgram(shaderProgram);

  // 删除着色器
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  app->rendering([&](){
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::Begin("controls");
    ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();

/*******************************************************************/
    glUseProgram(shaderProgram);
    vao.bind();
    // update shader uniform
    double  timeValue = glfwGetTime();
    float greenValue = static_cast<float>(sin(timeValue) / 2.0 + 0.5);
    int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
    glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
    CHECK_GL(glDrawArrays(GL_TRIANGLES, 0, 3));
    vao.unbind();
/********************************************************************/

		// 渲染 gui
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  });

	app->destroy();

	return 0;
}