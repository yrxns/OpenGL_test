#include "core.hpp"
#include <iostream>
#include "Application.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "VAO.hpp"
#include "VBO.hpp"
#include "EBO.hpp"
#include "shader.hpp"
#include <vector>

int main() {
	Application *app = Application::getInstance();
  app->mHeight = 600;
  app->mWidth = 800;
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
      // 位置              // 颜色
      0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // 右下
      -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // 左下
      0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f    // 顶部
  };

  VBO vbo; VAO vao;
  vao.bind(); vbo.bind();

  vbo.setData(vertices, GL_STATIC_DRAW);
  vao.vertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  vao.vertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
  vbo.unbind(); vao.unbind();

  Shader ourShader("../examples/06_glsl_exercise_3/shader/vertex.glsl", "../examples/06_glsl_exercise_3/shader/fragment.glsl");

  app->rendering([&](){
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::Begin("controls");
    ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();

/*******************************************************************/
    
    ourShader.begin(); vao.bind();
    double  timeValue = glfwGetTime();
    float xoffset = static_cast<float>(sin(timeValue));
    float yoffset = static_cast<float>(cos(timeValue));
    ourShader.setFloat("xOffset", xoffset);
    ourShader.setFloat("yOffset", yoffset);
    CHECK_GL(glDrawArrays(GL_TRIANGLES, 0, 3));
    vao.unbind(); ourShader.end();
/********************************************************************/

		// 渲染 gui
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  });

	app->destroy();

	return 0;
}