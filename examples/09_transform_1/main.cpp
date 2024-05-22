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
#include "texture.hpp"
#include <vector>

int main() {
	Application *app = Application::getInstance();
  app->mWidth = 800;
  app->mHeight = 600;
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
        // positions          // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left 
  };

    std::vector<int> indexes = {
      0, 1, 3, // 第一个三角形
      1, 2, 3  // 第二个三角形
  };

  VBO vbo; VAO vao; EBO ebo;
  vao.bind(); vbo.bind(); ebo.bind();

  vbo.setData(vertices, GL_STATIC_DRAW);
  vao.vertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
  vao.vertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));

  ebo.setData(indexes, GL_STATIC_DRAW);
  ebo.unbind(); vbo.unbind(); vao.unbind(); 

  Shader ourShader("../examples/09_transform_1/shader/vertex.glsl", "../examples/09_transform_1/shader/fragment.glsl");

  Texture_load texture1("../assets/container.png", 0, GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT);
  Texture_load texture2("../assets/awesomeface.png", 1, GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT);
  ourShader.begin(); texture1.bind(); texture2.bind();
  ourShader.setInt("texture1", 0);
  ourShader.setInt("texture2", 1);
  ourShader.end();

  app->rendering([&](){
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::Begin("controls");
    ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();

/*******************************************************************/
    
    ourShader.begin(); vao.bind(); ebo.bind();
    // create transformations
    glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
    transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
    ourShader.setMatrix4x4("transform", transform);
    CHECK_GL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));

    transform = glm::mat4(1.0f); // reset it to identity matrix
    transform = glm::translate(transform, glm::vec3(-0.5f, 0.5f, 0.0f));
    float scaleAmount = static_cast<float>(sin(glfwGetTime()));
    transform = glm::scale(transform, glm::vec3(scaleAmount, scaleAmount, scaleAmount));
    ourShader.setMatrix4x4("transform", transform);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    ebo.unbind(); vao.unbind(); ourShader.end();
/********************************************************************/

		// 渲染 gui
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  });

	app->destroy();

	return 0;
}