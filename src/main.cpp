#include "core.hpp"
#include <iostream>
#include "Shader.hpp"
#include "Application.hpp"
#include "VBO.hpp"
#include "VAO.hpp"
#include "EBO.hpp"
#include "Texture.hpp"
#include "Camera.hpp"
#include <vector>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

VBO *vbo = nullptr;
VAO *vao = nullptr;
VAO *lightvao = nullptr;
EBO *ebo = nullptr;
Shader	*shader = nullptr;
Shader *lightShader = nullptr;
Texture *container = nullptr;
Texture *awesomeface = nullptr;
glm::mat4 model(1.0f);
glm::mat4 view(1.0f);
glm::mat4 projection(1.0f);

// camera
Camera *camera = nullptr;

void OnResize(int width, int height) {
	CHECK_GL(glViewport(0, 0, width, height));
	std::cout << "onResize" << std::endl;
}

void OnKey(GLFWwindow *window, int key, int action, int mods) {
	std::cout << key << std::endl;
	if (key == 256) {
		glfwSetWindowShouldClose(window, true);
	}
	// if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	// glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera->processKeyboard(Camera_Movement::FORWARD, camera->deltaTime);
	}
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->processKeyboard(Camera_Movement::BACKWARD, camera->deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->processKeyboard(Camera_Movement::LEFT, camera->deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->processKeyboard(Camera_Movement::RIGHT, camera->deltaTime);
}

void OnMouse(int button, int action, int mods) {
	std::cout << "鼠标点击：(" << button << ", " << action << ", " << mods << ")" << std::endl;
}

void OnCursor(double xpos, double ypos) {
	std::cout << "鼠标移动：(" << xpos << ", " << ypos << ")" << std::endl;
	float x = static_cast<float>(xpos);
    float y = static_cast<float>(ypos);

    if (camera->firstMouse)
    {
        camera->lastX = x;
        camera->lastY = y;
        camera->firstMouse = false;
    }

    float xoffset = x - camera->lastX;
    float yoffset = camera->lastY - y; // reversed since y-coordinates go from bottom to top

    camera->lastX = x;
    camera->lastY = y;

    camera->processMouseMovement(xoffset, yoffset);
}

void OnScroll(double xoffset, double yoffset) {
	std::cout << "鼠标滚轮: x offset = " << xoffset << ", y offset = " << yoffset << std::endl;
	camera->processMouseScroll(static_cast<float>(yoffset));
}

// 窗口获得焦点的回调函数  
void on_window_focus(GLFWwindow* window, int focused) {  
    if (focused) {  
        printf("窗口获得焦点...\n");  
        // 在这里执行当窗口获得焦点时需要做的操作  
    } else {  
        printf("窗口失去焦点...\n");  
        // 在这里执行当窗口失去焦点时需要做的操作  
    }  
} 

void prepareData() {
    // 数据
	std::vector<float> vertices = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
	};

	std::vector<int> indexes = {
		0, 1, 3, // 第一个三角形
		1, 2, 3  // 第二个三角形
	};

	vao = new VAO;
	vbo = new VBO;
	ebo = new EBO;
	lightvao = new VAO;

	vao->begin();
	vbo->bind();
	vbo->setData(vertices, GL_STATIC_DRAW);
	vao->vertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	vao->vertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	vao->vertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	vao->end();

	lightvao->begin();
	vbo->bind();
	lightvao->vertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	lightvao->end();
}

void prepareShader() {
	shader = new Shader("../assets/vertex.glsl","../assets/fragment.glsl");
	lightShader = new Shader("../assets/lightV.glsl","../assets/lightF.glsl");
}

void prepareTexture() {
	container = new Texture("../assets/container2.png", 0, shader, "material.diffuse");
	awesomeface = new Texture("../assets/container2_specular.png", 1, shader, "material.specular");
}

void preTransform() {
	camera = new Camera();
}

void render() {
	//执行opengl画布清理操作
	CHECK_GL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

	float currentFrame = static_cast<float>(glfwGetTime());
	camera->deltaTime = currentFrame - camera->lastFrame;
	camera->lastFrame = currentFrame;

	// 绑定纹理
	// container->bind();
	// awesomeface->bind();

	//绑定当前的program
	shader->begin();

	// light properties
	glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
	shader->setVector3("light.position", lightPos);
	shader->setVector3("viewPos", camera->mPosition);
	glm::vec3 lightColor(1.0);
	shader->setVector3("light.ambient", 0.2f, 0.2f, 0.2f);
	shader->setVector3("light.diffuse", 0.5f, 0.5f, 0.5f);
	shader->setVector3("light.specular", 1.0f, 1.0f, 1.0f);

	shader->setFloat("material.shininess", 1.0f);
	model = glm::mat4(1.0f);
	shader->setMatrix4x4("model", model);
	glm::mat4 projection = camera->getProjectionMatrix();
	shader->setMatrix4x4("projection", projection);
	glm::mat4 view = camera->getViewMatrix();
	shader->setMatrix4x4("view", view);

	//绑定当前的vao
	vao->begin();
	glDrawArrays(GL_TRIANGLES, 0, 36);

	//解绑当前的vao
	vao->end();
	shader->end();

	lightShader->begin();
	lightShader->setMatrix4x4("view", view);
	lightShader->setMatrix4x4("projection", projection);
	model = glm::mat4(1.0f);
	model = glm::translate(model, lightPos);
	model = glm::scale(model, glm::vec3(0.2f));
	lightShader->setMatrix4x4("model", model);
	lightvao->begin();
	glDrawArrays(GL_TRIANGLES, 0, 36);
	lightvao->end();
	lightShader->end();
}


int main() {
	Application *app = Application::getInstance();

	if (!app->init(800, 600)) {
		return -1;
	}

	app->setResizeCallback(OnResize);
	app->setKeyBoardCallback(OnKey);
	app->setMouseCallback(OnMouse);
	app->setCursorCallback(OnCursor);
	app->setScrollCallback(OnScroll);
	// 设置窗口获得或失去焦点时的回调函数  
    glfwSetWindowFocusCallback(*app, on_window_focus);  

	prepareShader();
	prepareData();
	prepareTexture();
	preTransform();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	// Setup Platform/Renderer backends
	const char* glsl_version = "#version 330";
	ImGui_ImplGlfw_InitForOpenGL(*app, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	while (app->update()) {
		ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

		ImGui::Begin("controls");
		ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();

		render();

		// 渲染 gui
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	delete vao;
	delete vbo;
	delete ebo;
	delete shader;
	delete container;
	delete awesomeface;
	delete camera;
	delete lightvao;
	delete lightShader;
	app->destroy();

	return 0;
}