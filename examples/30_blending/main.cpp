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

  Shader ourShader("../examples/30_blending/shader/vertex.glsl", "../examples/30_blending/shader/fragment.glsl");
  // Shader shaderSingleColor("../examples/30_blending/shader/stencil_vert.glsl", "../examples/30_blending/shader/stencil_frag.glsl");

  Texture_load texture1("../assets/image0.png", 0, GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT);
  Texture_load texture2("../assets/image1.png", 1, GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT);
  Texture_load texture3("../assets/grass.png", 2, GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT);

    std::vector<float> cubeVertices = {
        // positions          // texture Coords
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    std::vector<float> planeVertices = {
        // positions          // texture Coords 
         5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
        -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

         5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
         5.0f, -0.5f, -5.0f,  2.0f, 2.0f						
    };

    std::vector<float> transparentVertices = {
        // positions         // texture Coords (swapped y coordinates because texture is flipped upside down)
        0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
        0.0f, -0.5f,  0.0f,  0.0f,  -1.0f,
        1.0f, -0.5f,  0.0f,  1.0f,  -1.0f,

        0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
        1.0f, -0.5f,  0.0f,  1.0f,  -1.0f,
        1.0f,  0.5f,  0.0f,  1.0f,  0.0f					
    };

    vector<glm::vec3> vegetation 
    {
        glm::vec3(-1.5f, 0.0f, -0.48f),
        glm::vec3( 1.5f, 0.0f, 0.51f),
        glm::vec3( 0.0f, 0.0f, 0.7f),
        glm::vec3(-0.3f, 0.0f, -2.3f),
        glm::vec3 (0.5f, 0.0f, -0.6f)
    };

  VAO vao1, vao2, vao3; VBO vbo1, vbo2, vbo3;
  vao1.bind(); vbo1.bind();
  vbo1.setData(cubeVertices, GL_STATIC_DRAW);
  vao1.vertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
  vao1.vertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
  vbo1.unbind(); vao1.unbind();

  vao2.bind(); vbo2.bind();
  vbo2.setData(planeVertices, GL_STATIC_DRAW);
  vao2.vertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
  vao2.vertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
  vbo2.unbind(); vao2.unbind();

  vao3.bind(); vbo3.bind();
  vbo3.setData(transparentVertices, GL_STATIC_DRAW);
  vao3.vertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
  vao3.vertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
  vbo3.unbind(); vao3.unbind();

  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

/*******************************************************************/
    ourShader.begin();

    glm::mat4 model         = glm::mat4(1.0f);
    glm::mat4 view = cameraNS::camera->getViewMatrix();
    glm::mat4 projection = cameraNS::camera->getProjectionMatrix(cameraNS::camera->mFovy, (float)gl_app->mWidth / (float)gl_app->mHeight, 0.1f, 100.0f);
    ourShader.setMatrix4x4("model", model);
    ourShader.setMatrix4x4("view", view);
    ourShader.setMatrix4x4("projection", projection);

    // floor
    vao2.bind(); texture2.bind();
    ourShader.setInt("texture1", 1);
    ourShader.setMatrix4x4("model", glm::mat4(1.0f));
    glDrawArrays(GL_TRIANGLES, 0, 6);
    vao2.unbind();

    vao1.bind(); texture1.bind();
    ourShader.setInt("texture1", 0);
    model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
    ourShader.setMatrix4x4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
    ourShader.setMatrix4x4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    vao1.unbind();

    vao3.bind(); texture3.bind();
    ourShader.setInt("texture1", 2);
    for (unsigned int i = 0; i < vegetation.size(); i++)
    {
        model = glm::mat4(1.0f);
        model = glm::translate(model, vegetation[i]);
        ourShader.setMatrix4x4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 6);
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