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
// #include "texture.hpp"
#include "model.hpp"
#include "geometry/PlaneGeometry.h"
#include "geometry/BoxGeometry.h"
#include "geometry/SphereGeometry.h"
#include "camera.hpp"
#include <vector>

unsigned int loadCubemap(vector<std::string> faces);

int main() {
  cameraNS::camera = new Camera(glm::vec3(0.0f, 0.0f, 5.0f));
  gl_app->mWidth = 800;
  gl_app->mHeight = 600;
  gl_app->setKeyBoardCallback(cameraNS::on_key);
  gl_app->setMouseCallback(cameraNS::on_mouse);
  gl_app->setScrollCallback(cameraNS::on_scroll);
  gl_app->setCursorCallback(cameraNS::on_cursor);
	if (!gl_app->init()) {
		return -1;
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	ImGui::StyleColorsDark();
	const char* glsl_version = "#version 330";
	ImGui_ImplGlfw_InitForOpenGL(*gl_app, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

  Shader ourShader("../examples/37_instancing_rock/shader/instancing.vs", "../examples/37_instancing_rock/shader/instancing.fs");

  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

  Model rock("../assets/rock/rock.obj");
  Model planet("../assets/planet/planet.obj");

  unsigned int amount = 1000;
  glm::mat4* modelMatrices;
  modelMatrices = new glm::mat4[amount];
  srand(static_cast<unsigned int>(glfwGetTime())); // initialize random seed
  float radius = 50.0;
  float offset = 2.5f;
  for (unsigned int i = 0; i < amount; i++)
  {
      glm::mat4 model = glm::mat4(1.0f);
      // 1. translation: displace along circle with 'radius' in range [-offset, offset]
      float angle = (float)i / (float)amount * 360.0f;
      float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
      float x = sin(angle) * radius + displacement;
      displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
      float y = displacement * 0.4f; // keep height of asteroid field smaller compared to width of x and z
      displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
      float z = cos(angle) * radius + displacement;
      model = glm::translate(model, glm::vec3(x, y, z));

      // 2. scale: Scale between 0.05 and 0.25f
      float scale = static_cast<float>((rand() % 20) / 100.0 + 0.05);
      model = glm::scale(model, glm::vec3(scale));

      // 3. rotation: add random rotation around a (semi)randomly picked rotation axis vector
      float rotAngle = static_cast<float>((rand() % 360));
      model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));

      // 4. now add to list of matrices
      modelMatrices[i] = model;
  }


  gl_app->rendering([&](){
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("imgui");
    ImGui::Text("This is some useful text.");
    ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

    ImGui::SliderFloat("fov", &cameraNS::camera->mFovy, 0.0f, 360.0f);
    ImGui::SliderInt("SCREEN_WIDTH", &(gl_app->mWidth), 1, 1980);
    ImGui::SliderInt("SCREEN_HEIGHT", &(gl_app->mHeight), 1, 1080);
    ImGui::ColorEdit3("clear color", (float*)&clear_color);

    // ImGui::SameLine();
    ImGui::End();

    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);

/*******************************************************************/
    ourShader.begin();

    glm::mat4 model         = glm::mat4(1.0f);
    glm::mat4 view = cameraNS::camera->getViewMatrix();
    glm::mat4 projection = cameraNS::camera->getProjectionMatrix(cameraNS::camera->mFovy, (float)gl_app->mWidth / (float)gl_app->mHeight, 0.1f, 100.0f);
    ourShader.setMatrix4x4("model", model);
    ourShader.setMatrix4x4("view", view);
    ourShader.setMatrix4x4("projection", projection);

    // draw planet
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, -3.0f, 0.0f));
    model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
    // model = glm::rotate(model, glm::radians(15.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    ourShader.setMatrix4x4("model", model);
    planet.Draw(ourShader);

    // draw meteorites
    for (unsigned int i = 0; i < amount; i++)
    {
        ourShader.setMatrix4x4("model", modelMatrices[i]);
        rock.Draw(ourShader);
    }
    ourShader.end();
/********************************************************************/

		// 渲染 gui
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  });
  
	gl_app->destroy();

	return 0;
}