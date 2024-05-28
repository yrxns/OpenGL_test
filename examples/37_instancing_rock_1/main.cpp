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

  Shader asteroidShader("../examples/37_instancing_rock_1/shader/asteroids.vs", "../examples/37_instancing_rock_1/shader/asteroids.fs");
  Shader planetShader("../examples/37_instancing_rock_1/shader/planet.vs", "../examples/37_instancing_rock_1/shader/planet.fs");

  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

  Model rock("../assets/rock/rock.obj");
  Model planet("../assets/planet/planet.obj");

    unsigned int amount = 1000;
    glm::mat4* modelMatrices;
    modelMatrices = new glm::mat4[amount];
    srand(static_cast<unsigned int>(glfwGetTime())); // initialize random seed
    float radius = 150.0;
    float offset = 25.0f;
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

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, amount * sizeof(glm::mat4), &modelMatrices[0], GL_STATIC_DRAW);

    for (unsigned int i = 0; i < rock.meshes.size(); i++)
    {
        unsigned int VAO = rock.meshes[i].VAO;
        glBindVertexArray(VAO);
        // set attribute pointers for matrix (4 times vec4)
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
        glEnableVertexAttribArray(5);
        glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
        glEnableVertexAttribArray(6);
        glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

        glVertexAttribDivisor(3, 1);
        glVertexAttribDivisor(4, 1);
        glVertexAttribDivisor(5, 1);
        glVertexAttribDivisor(6, 1);

        glBindVertexArray(0);
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
    glm::mat4 model         = glm::mat4(1.0f);
    glm::mat4 view = cameraNS::camera->getViewMatrix();
    glm::mat4 projection = cameraNS::camera->getProjectionMatrix(cameraNS::camera->mFovy, (float)gl_app->mWidth / (float)gl_app->mHeight, 0.1f, 100.0f);

    asteroidShader.begin();
    asteroidShader.setMatrix4x4("model", model);
    asteroidShader.setMatrix4x4("view", view);
    asteroidShader.setMatrix4x4("projection", projection);
    asteroidShader.end();

    planetShader.begin();
    planetShader.setMatrix4x4("model", model);
    planetShader.setMatrix4x4("view", view);
    planetShader.setMatrix4x4("projection", projection);
    planetShader.end();

    // draw planet
    // planetShader.begin();
    // model = glm::mat4(1.0f);
    // model = glm::translate(model, glm::vec3(0.0f, -3.0f, 0.0f));
    // model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
    // planetShader.setMatrix4x4("model", model);
    // planet.Draw(planetShader);
    // planetShader.end();

    // draw meteorites
    asteroidShader.begin();
    asteroidShader.setInt("texture_diffuse1", 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, rock.textures_loaded[0].id); // note: we also made the textures_loaded vector public (instead of private) from the model class.
    for (unsigned int i = 0; i < rock.meshes.size(); i++)
    {
        glBindVertexArray(rock.meshes[i].VAO);
        glDrawElementsInstanced(GL_TRIANGLES, static_cast<unsigned int>(rock.meshes[i].indices.size()), GL_UNSIGNED_INT, 0, amount);
        glBindVertexArray(0);
    }
    asteroidShader.end();
/********************************************************************/

		// 渲染 gui
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  });
  
	gl_app->destroy();

	return 0;
}