#include <iostream>
#include "core.hpp"
#include "Shader.hpp"
#include "Application.hpp"
#include <assert.h>//断言


GLuint vao;
Shader* shader = nullptr;

void OnResize(int width, int height) {
	CHECK_GL(glViewport(0, 0, width, height));
	std::cout << "onResize" << std::endl;
}

void OnKey(int key, int action, int mods) {
	std::cout << key << std::endl;
}

void prepareVAO() {
    // 数据

	//2 VBO创建

	//3 EBO创建

	//4 VAO创建
}

void prepareShader() {
	shader = new Shader("assets/vertex.glsl","assets/fragment.glsl");
}

void prepareTexture() {
	// texture = new Texture("assets/textures/goku.jpg", 0);
}

void prepareCamera() {
	//lookat:生成一个viewMatrix
	//eye:当前摄像机所在的位置
	//center:当前摄像机看向的那个点
	//up:穹顶向量
	// viewMatrix = glm::lookAt(glm::vec3(1.0f,0.0f,1.0f),glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,1.0f,0.0f));
}

void prepareOrtho() {
	// orthoMatrix = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, 2.0f, -2.0f);
}

void render() {
	//执行opengl画布清理操作
	CHECK_GL(glClear(GL_COLOR_BUFFER_BIT));

	//绑定当前的program
	shader->begin();
	shader->setInt("sampler", 0);

	//绑定当前的vao
	CHECK_GL(glBindVertexArray(vao));

	//发出绘制指令
	CHECK_GL(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0));
	CHECK_GL(glBindVertexArray(0));

	shader->end();
}


int main() {
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
	prepareTexture();
	prepareCamera();
	prepareOrtho();

	while (app->update()) {
		render();
	}

	app->destroy();

	return 0;
}