#include "core.hpp"
#include <iostream>
#include "Shader.hpp"
#include "Application.hpp"
#include "VBO.hpp"
#include "VAO.hpp"
#include "EBO.hpp"
#include <vector>

VBO *vbo = nullptr;
VAO *vao = nullptr;
EBO *ebo = nullptr;
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

void prepareData() {
    // 数据
	std::vector<float> vertices = {
		0.5f, 0.5f, 0.0f,   // 右上角
		0.5f, -0.5f, 0.0f,  // 右下角
		-0.5f, -0.5f, 0.0f, // 左下角
		-0.5f, 0.5f, 0.0f   // 左上角
	};

	std::vector<int> indexes = {
		0, 1, 3, // 第一个三角形
		1, 2, 3  // 第二个三角形
	};

	vao = new VAO;
	vbo = new VBO;
	ebo = new EBO;

	vao->begin();
	vbo->bind();
	ebo->bind();
	vbo->setData(vertices, GL_STATIC_DRAW);
	ebo->setData(indexes, GL_STATIC_DRAW);
	vao->vertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// vao->vertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
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
	CHECK_GL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));

	//解绑当前的vao
	vao->end();
	shader->end();
}


int main() {
	Application *app = Application::getInstance();

	if (!app->init(800, 600)) {
		return -1;
	}

	app->setResizeCallback(OnResize);
	app->setKeyBoardCallback(OnKey);

	//设置opengl视口以及清理颜色
	CHECK_GL(glViewport(0, 0, 800, 600));
	CHECK_GL(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));

	prepareShader();
	prepareData();

	// 设置线框绘制模式
  	// glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while (app->update()) {
		render();
	}

	delete vao;
	delete vbo;
	delete ebo;
	delete shader;
	app->destroy();

	return 0;
}