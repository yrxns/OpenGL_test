#include "core.hpp"
#include <iostream>
#include "Shader.hpp"
#include "Application.hpp"
#include "VBO.hpp"
#include "VAO.hpp"
#include "EBO.hpp"

VBO *vbo = nullptr;
VAO *vao = nullptr;
Shader* shader = nullptr;

void OnResize(int width, int height) {
	CHECK_GL(glViewport(0, 0, width, height));
	std::cout << "onResize" << std::endl;
}

void OnKey(GLFWwindow *window, int key, int action, int mods) {
	std::cout << key << std::endl;
	if (key == 256) {
		glfwSetWindowShouldClose(window, true);
	}
}

void prepareVAO() {
    // 数据
	float vertices[] = {
		// 位置              // 颜色
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // 右下
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // 左下
		0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f    // 顶部
  	}	;

	vao = new VAO;
	vbo = new VBO;

	vao->begin();
	vbo->setData(vertices);
	vao->vertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
	vao->vertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
	vao->end();
}

void prepareShader() {
	shader = new Shader("../assets/vertex.glsl","../assets/fragment.glsl");
}

void render() {
	//执行opengl画布清理操作
	CHECK_GL(glClear(GL_COLOR_BUFFER_BIT));

	//绑定当前的program
	shader->begin();

	//绑定当前的vao
	vao->begin();

	//发出绘制指令
	CHECK_GL(glDrawArrays(GL_TRIANGLES, 0, 3));

	//解绑当前的vao
	vao->end();
	shader->end();
}


int main() {
	Application *app = Application::getInstance();

	app->glVersionInfo();

	if (!app->init(800, 600)) {
		return -1;
	}

	app->setResizeCallback(OnResize);
	app->setKeyBoardCallback(OnKey);

	//设置opengl视口以及清理颜色
	CHECK_GL(glViewport(0, 0, 800, 600));
	CHECK_GL(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));

	prepareShader();
	prepareVAO();

	// 设置线框绘制模式
  	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	while (app->update()) {
		render();
	}

	delete vao;
	delete vbo;
	delete shader;
	app->destroy();

	return 0;
}