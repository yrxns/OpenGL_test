#include "core.hpp"
#include <iostream>
#include "Shader.hpp"
#include "Application.hpp"
#include "VBO.hpp"
#include "VAO.hpp"
#include "EBO.hpp"
#include "Texture.hpp"
#include <vector>

VBO *vbo = nullptr;
VAO *vao = nullptr;
EBO *ebo = nullptr;
Shader	*shader = nullptr;
Texture *container = nullptr;
Texture *awesomeface = nullptr;

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
		// positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
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
	vao->vertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	vao->vertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
	vao->vertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
	vao->end();
}

void prepareShader() {
	shader = new Shader("../examples/texture/shader/vertex.glsl","../examples/texture/shader/fragment.glsl");
}

void prepareTexture() {
	container = new Texture("../assets/container.png", 0, shader, "texture1", GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER);
	awesomeface = new Texture("../assets/awesomeface.png", 1, shader, "texture2", GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_MIRRORED_REPEAT, GL_MIRRORED_REPEAT);
}

void render() {
	//执行opengl画布清理操作
	CHECK_GL(glClear(GL_COLOR_BUFFER_BIT));

	// 绑定纹理
	container->bind();
	awesomeface->bind();

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

	prepareShader();
	prepareData();
	prepareTexture();

	while (app->update()) {
		render();
	}

	delete vao;
	delete vbo;
	delete ebo;
	delete shader;
	delete container;
	delete awesomeface;
	app->destroy();

	return 0;
}