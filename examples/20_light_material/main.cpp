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
#include "geometry/PlaneGeometry.h"
#include "geometry/BoxGeometry.h"
#include "geometry/SphereGeometry.h"
#include "camera.hpp"
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

  Shader ourShader("../examples/20_light_material/shader/vertex.glsl", "../examples/20_light_material/shader/fragment.glsl");
  Shader lightCubeShader("../examples/20_light_material/shader/light_vert.glsl", "../examples/20_light_material/shader/light_frag.glsl");

  Texture_load texture1("../assets/container.png", 0, GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT);
  Texture_load texture2("../assets/awesomeface.png", 1, GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT);

  ourShader.begin(); texture1.bind(); texture2.bind();
  ourShader.setInt("texture1", 0);
  ourShader.setInt("texture2", 1);
  ourShader.end();

  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
  // 光照信息
  glm::vec3 lightPosition = glm::vec3(1.0, 1.5, 0.0); // 光照位置
  ourShader.begin();
  // 传递材质属性
  ourShader.setVector3("material.ambient", 1.0f, 0.5f, 0.31f);
  ourShader.setVector3("material.diffuse", 1.0f, 0.5f, 0.31f);
  ourShader.setVector3("material.specular", 0.5f, 0.5f, 0.5f);
  ourShader.setFloat("material.shininess", 32.0f);
  ourShader.end();

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
    glm::mat4 projection    = glm::mat4(1.0f);
    glm::mat4 view = cameraNS::camera->getViewMatrix();
    projection = cameraNS::camera->getProjectionMatrix(cameraNS::camera->mFovy, (float)gl_app->mWidth / (float)gl_app->mHeight, 0.1f, 100.0f);

    float rotate = glfwGetTime() * 0.2f;
    glm::qua<float> qu = glm::qua<float>(glm::vec3(rotate, rotate, rotate));
    model = glm::mat4_cast(qu);

    glm::vec3 lightPos = glm::vec3(lightPosition.x * glm::sin(glfwGetTime()), lightPosition.y, lightPosition.z);

    glm::vec3 lightColor;
    lightColor.x = sin(glfwGetTime() * 2.0f);
    lightColor.y = sin(glfwGetTime() * 0.7f);
    lightColor.z = sin(glfwGetTime() * 1.3f);
    glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);   // 降低影响
    glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // 很低的影响

    // 设置光照属性
    ourShader.setVector3("light.ambient", ambientColor);
    ourShader.setVector3("light.diffuse", diffuseColor);
    ourShader.setVector3("light.specular", 1.0f, 1.0f, 1.0f);

    ourShader.setVector3("light.position", lightPos);
    ourShader.setVector3("viewPos", cameraNS::camera->mPosition);
    ourShader.setMatrix4x4("model", model);
    ourShader.setMatrix4x4("view", view);
    ourShader.setMatrix4x4("projection", projection);

    glBindVertexArray(boxGeometry.VAO);
    glDrawElements(GL_TRIANGLES, boxGeometry.indices.size(), GL_UNSIGNED_INT, 0);

    ourShader.end();

    // 绘制灯光物体
    lightCubeShader.begin();
    model = glm::mat4(1.0f);
    model = glm::translate(model, lightPos);

    lightCubeShader.setMatrix4x4("model", model);
    lightCubeShader.setMatrix4x4("view", view);
    lightCubeShader.setMatrix4x4("projection", projection);
    glBindVertexArray(sphereGeometry.VAO);
    glDrawElements(GL_TRIANGLES, sphereGeometry.indices.size(), GL_UNSIGNED_INT, 0);
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