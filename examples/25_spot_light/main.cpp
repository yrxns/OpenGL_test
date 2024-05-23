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

  Shader ourShader("../examples/25_spot_light/shader/vertex.glsl", "../examples/25_spot_light/shader/fragment.glsl");
  Shader lightCubeShader("../examples/25_spot_light/shader/light_vert.glsl", "../examples/25_spot_light/shader/light_frag.glsl");

  Texture_load texture1("../assets/container2.png", 0, GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT);
  Texture_load texture2("../assets/container2_specular.png", 1, GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT);

  ourShader.begin(); texture1.bind(); texture2.bind();
  ourShader.setInt("material.diffuse", 0);
  ourShader.setInt("material.specular", 1);
  ourShader.end();

  glm::vec3 ambient(0.1f, 0.1f, 0.1f);
  glm::vec3 diffuse(0.9f, 0.9f, 0.9f);
  glm::vec3 specular(1.0f, 1.0f, 1.0f);
  float cutOff = 12.5f;
  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
  // 光照信息
  glm::vec3 lightPosition = glm::vec3(1.0, 1.5, 0.0); // 光照位置
  ourShader.begin();
  // 传递材质属性
  ourShader.setFloat("material.shininess", 64.0f);

  // 设置衰减
  ourShader.setFloat("light.constant", 1.0f);
  ourShader.setFloat("light.linear", 0.09f);
  ourShader.setFloat("light.quadratic", 0.032f);

  ourShader.end();

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

  gl_app->rendering([&](){
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("imgui");
    ImGui::Text("This is some useful text.");
    ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

    ImGui::SliderFloat("fov", &cameraNS::camera->mFovy, 0.0f, 360.0f);
    ImGui::SliderFloat3("ambient", (float *)&ambient, 0.0f, 1.0f);
    ImGui::SliderFloat3("diffuse", (float *)&diffuse, 0.0f, 1.0f);
    ImGui::SliderFloat3("specular", (float *)&specular, 0.0f, 1.0f);
    ImGui::SliderInt("SCREEN_WIDTH", &(gl_app->mWidth), 1, 1980);
    ImGui::SliderInt("SCREEN_HEIGHT", &(gl_app->mHeight), 1, 1080);
    ImGui::SliderFloat("light.cutOff", &cutOff, 0.0f, 130.0f);
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

    // 设置光照属性
    ourShader.setVector3("light.ambient", ambient);
    ourShader.setVector3("light.diffuse", diffuse);
    ourShader.setVector3("light.specular", specular);

    // ourShader.setVector3("light.position", lightPos);
    // ourShader.setVector3("light.position", lightPosition);
    ourShader.setVector3("light.position", cameraNS::camera->mPosition);
    ourShader.setVector3("light.direction", cameraNS::camera->mFront);
    ourShader.setFloat("light.cutOff", glm::cos(glm::radians(cutOff)));
    ourShader.setVector3("viewPos", cameraNS::camera->mPosition);
    ourShader.setMatrix4x4("model", model);
    ourShader.setMatrix4x4("view", view);
    ourShader.setMatrix4x4("projection", projection);

    for (unsigned int i = 0; i < 10; i++)
    {
      model = glm::mat4(1.0f);
      model = glm::translate(model, cubePositions[i]);

      float angle = 10.0f * i;
      model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

      ourShader.setMatrix4x4("model", model);
      glBindVertexArray(boxGeometry.VAO);
      glDrawElements(GL_TRIANGLES, boxGeometry.indices.size(), GL_UNSIGNED_INT, 0);
    }

    ourShader.end();

    // 绘制灯光物体
    lightCubeShader.begin();
    model = glm::mat4(1.0f);
    // model = glm::translate(model, lightPos);
    // model = glm::translate(model, lightPosition);
    model = glm::translate(model, cameraNS::camera->mPosition);

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