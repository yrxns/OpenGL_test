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

// FreeType
#include <ft2build.h>
#include FT_FREETYPE_H

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

  Shader ourShader("../examples/text_rendering/shader/vertex.glsl", "../examples/text_rendering/shader/fragment.glsl");

  Texture_load texture1("../assets/container.png", 0);
  Texture_load texture2("../assets/awesomeface.png", 1);
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
    
/********************************************************************/

		// 渲染 gui
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  });

	app->destroy();

	return 0;
}