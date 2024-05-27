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

  Shader ourShader("../examples/32_frame_buffers_6/shader/vertex.glsl", "../examples/32_frame_buffers_6/shader/fragment.glsl");
  Shader screenShader("../examples/32_frame_buffers_6/shader/framebuffers_vert.glsl", "../examples/32_frame_buffers_6/shader/framebuffers_frag.glsl");

  Texture_load texture1("../assets/container.png", 0, GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT);
  Texture_load texture2("../assets/image1.png", 1, GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT);

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

    std::vector<float> quadVertices = {
        // positions   // texCoords
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f					
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
  vbo3.setData(quadVertices, GL_STATIC_DRAW);
  vao3.vertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
  vao3.vertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
  vbo3.unbind(); vao3.unbind();

  ourShader.begin(); texture1.bind();texture2.bind();
  ourShader.end();

  screenShader.begin();
  screenShader.setInt("screenTexture", 3);
  screenShader.end();

  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

  // glDepthFunc(GL_ALWAYS);
  // glDepthFunc(GL_LESS);
    // framebuffer configuration
    // -------------------------
    unsigned int framebuffer;
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    // create a color attachment texture
    unsigned int textureColorbuffer;
    glGenTextures(1, &textureColorbuffer);
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, gl_app->mWidth, gl_app->mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
    // create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
    unsigned int rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, gl_app->mWidth, gl_app->mHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

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

    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glEnable(GL_DEPTH_TEST); 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 model         = glm::mat4(1.0f);
    glm::mat4 view = cameraNS::camera->getViewMatrix();
    glm::mat4 projection = cameraNS::camera->getProjectionMatrix(cameraNS::camera->mFovy, (float)gl_app->mWidth / (float)gl_app->mHeight, 0.1f, 100.0f);
    ourShader.setMatrix4x4("model", model);
    ourShader.setMatrix4x4("view", view);
    ourShader.setMatrix4x4("projection", projection);

    // cubes
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

    // floor
    vao2.bind(); texture2.bind();
    ourShader.setInt("texture1", 1);
    ourShader.setMatrix4x4("model", glm::mat4(1.0f));
    glDrawArrays(GL_TRIANGLES, 0, 6);
    vao2.unbind();
    ourShader.end();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDisable(GL_DEPTH_TEST);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    screenShader.begin();
    vao3.bind();
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, textureColorbuffer);	// use the color attachment texture as the texture of the quad plane
    glDrawArrays(GL_TRIANGLES, 0, 6);
    vao3.unbind();
    screenShader.end();
/********************************************************************/

		// 渲染 gui
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  });
  
	gl_app->destroy();

	return 0;
}