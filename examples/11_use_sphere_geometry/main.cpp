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
#include "geometry/SphereGeometry.h"
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

  SphereGeometry sphereGeometry(0.5, 20.0, 20.0);

  Shader ourShader("../examples/11_use_sphere_geometry/shader/vertex.glsl", "../examples/11_use_sphere_geometry/shader/fragment.glsl");

  Texture_load texture1("../assets/container.png", 0, GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT);
  Texture_load texture2("../assets/awesomeface.png", 1, GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT);
  ourShader.begin(); texture1.bind(); texture2.bind();
  ourShader.setInt("texture1", 0);
  ourShader.setInt("texture2", 1);
  ourShader.end();

  float factor = 0.0;

  app->rendering([&](){
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::Begin("controls");
    ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();

/*******************************************************************/
    ourShader.begin();
    glBindVertexArray(sphereGeometry.VAO);

    factor = glfwGetTime();
    ourShader.setFloat("factor", factor);

    // glDrawElements(GL_TRIANGLES, sphereGeometry.indices.size(), GL_UNSIGNED_INT, 0);
    glDrawElements(GL_POINTS, sphereGeometry.indices.size(), GL_UNSIGNED_INT, 0);
    glDrawElements(GL_LINE_LOOP, sphereGeometry.indices.size(), GL_UNSIGNED_INT, 0);
    ourShader.end();
/********************************************************************/

		// 渲染 gui
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  });

  sphereGeometry.dispose();
	app->destroy();

	return 0;
}