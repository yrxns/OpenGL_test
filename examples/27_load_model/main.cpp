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
#include "geometry/PlaneGeometry.h"
#include "geometry/BoxGeometry.h"
#include "geometry/SphereGeometry.h"
#include "camera.hpp"
// #include "mesh.hpp"
#include "model.hpp"
#include <vector>

int main() {
  cameraNS::camera = new Camera(glm::vec3(0.0f, 0.0f, 5.0f));
  gl_app->mWidth = 800;
  gl_app->mHeight = 600;
  gl_app->setKeyBoardCallback(cameraNS::on_key);
  gl_app->setMouseCallback(cameraNS::on_mouse);
  gl_app->setScrollCallback(cameraNS::on_scroll);
  // gl_app->setCursorCallback(cameraNS::on_cursor);
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

  BoxGeometry boxGeometry(1.0, 1.0, 1.0);
  SphereGeometry sphereGeometry(0.1, 10.0, 10.0);

  Shader ourShader("../examples/27_load_model/shader/vertex.glsl", "../examples/27_load_model/shader/fragment.glsl");
  Shader lightCubeShader("../examples/27_load_model/shader/light_vert.glsl", "../examples/27_load_model/shader/light_frag.glsl");

  // Texture_load texture1("../assets/container2.png", 0, GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT);
  // Texture_load texture2("../assets/container2_specular.png", 1, GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT);

  ourShader.begin();
  // ourShader.setInt("material.diffuse", 0);
  // ourShader.setInt("material.specular", 1);
  ourShader.setFloat("material.shininess", 32.0f);
  ourShader.end();

    // positions all containers
    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    // positions of the point lights
    glm::vec3 pointLightPositions[] = {
        glm::vec3( 0.7f,  0.2f,  2.0f),
        glm::vec3( 2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3( 0.0f,  0.0f, -3.0f)
    };

  glm::vec3 pointLightColors[] = {
      glm::vec3(1.0f, 1.0f, 1.0f),
      glm::vec3(1.0f, 0.0f, 1.0f),
      glm::vec3(0.0f, 0.0f, 1.0f),
      glm::vec3(0.0f, 1.0f, 0.0f)
  };

  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

  Model ourModel("../assets/model/nanosuit.obj");

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
    ourShader.setVector3("viewPos", cameraNS::camera->mPosition);

    // directional light
    ourShader.setVector3("dirLight.direction", -0.2f, -1.0f, -0.3f);
    ourShader.setVector3("dirLight.ambient", 0.01f, 0.01f, 0.01f);
    ourShader.setVector3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
    ourShader.setVector3("dirLight.specular", 0.5f, 0.5f, 0.5f);

    for (unsigned int i = 0; i < 4; i++)
    {
      // 设置点光源属性
      ourShader.setVector3("pointLights[" + std::to_string(i) + "].position", pointLightPositions[i]);
      ourShader.setVector3("pointLights[" + std::to_string(i) + "].ambient", 0.01f, 0.01f, 0.01f);
      ourShader.setVector3("pointLights[" + std::to_string(i) + "].diffuse", pointLightColors[i]);
      ourShader.setVector3("pointLights[" + std::to_string(i) + "].specular", 1.0f, 1.0f, 1.0f);

      // // 设置衰减
      ourShader.setFloat("pointLights[" + std::to_string(i) + "].constant", 1.0f);
      ourShader.setFloat("pointLights[" + std::to_string(i) + "].linear", 0.09f);
      ourShader.setFloat("pointLights[" + std::to_string(i) + "].quadratic", 0.032f);
    }

    // spotLight
    ourShader.setVector3("spotLight.position", cameraNS::camera->mPosition);
    ourShader.setVector3("spotLight.direction", cameraNS::camera->mFront);
    ourShader.setVector3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
    ourShader.setVector3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
    ourShader.setVector3("spotLight.specular", 1.0f, 1.0f, 1.0f);
    ourShader.setFloat("spotLight.constant", 1.0f);
    ourShader.setFloat("spotLight.linear", 0.09f);
    ourShader.setFloat("spotLight.quadratic", 0.032f);
    ourShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
    ourShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f))); 

    glm::mat4 model         = glm::mat4(1.0f);
    glm::mat4 view = cameraNS::camera->getViewMatrix();
    glm::mat4 projection = cameraNS::camera->getProjectionMatrix(cameraNS::camera->mFovy, (float)gl_app->mWidth / (float)gl_app->mHeight, 0.1f, 100.0f);
    ourShader.setMatrix4x4("model", model);
    ourShader.setMatrix4x4("view", view);
    ourShader.setMatrix4x4("projection", projection);

    model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(15.0f * (float)glfwGetTime()), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.13f, 0.13f, 0.13f));
    ourShader.setMatrix4x4("model", model);

    ourModel.Draw(ourShader);

    ourShader.end();

    // 绘制灯光物体
    lightCubeShader.begin();

    lightCubeShader.setMatrix4x4("view", view);
    lightCubeShader.setMatrix4x4("projection", projection);

    glBindVertexArray(sphereGeometry.VAO);
    for (unsigned int i = 0; i < 4; i++)
    {
        model = glm::mat4(1.0f);
        model = glm::translate(model, pointLightPositions[i]);
        // model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
        lightCubeShader.setMatrix4x4("model", model);
        lightCubeShader.setVector3("lightColor", pointLightColors[i]);
        glDrawElements(GL_TRIANGLES, sphereGeometry.indices.size(), GL_UNSIGNED_INT, 0);
    }

    lightCubeShader.end();
/********************************************************************/

		// 渲染 gui
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  });
  
  boxGeometry.dispose();
  sphereGeometry.dispose();
	gl_app->destroy();

	return 0;
}