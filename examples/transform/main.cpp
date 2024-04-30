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
glm::mat4 model(1.0f);
glm::mat4 view(1.0f);
glm::mat4 projection(1.0f);

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
	vao->vertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	vao->vertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
	// vao->vertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
	vao->end();
}

void prepareShader() {
	shader = new Shader("../examples/transform/shader/vertex.glsl","../examples/transform/shader/fragment.glsl");
}

void prepareTexture() {
	container = new Texture("../assets/container.png", 0, shader, "texture1");
	awesomeface = new Texture("../assets/awesomeface.png", 1, shader, "texture2");
}

void preTransform() {
	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	projection = glm::perspective(glm::radians(45.0f), 800.0f / 600, 0.1f, 100.0f);
}

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

void doTransform() {
	// model = glm::mat4(1.0f);
	// model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
}

void render() {
	//执行opengl画布清理操作
	CHECK_GL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

	// 绑定纹理
	container->bind();
	awesomeface->bind();

	//绑定当前的program
	shader->begin();

	shader->setMatrix4x4("model", model);
	shader->setMatrix4x4("view", view);
	shader->setMatrix4x4("projection", projection);
	//绑定当前的vao
	vao->begin();

	//发出绘制指令
	// CHECK_GL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
	// doTransform();

	for(unsigned int i = 0; i < 10; i++) {
		model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[i]);
		float angle = 20.0f * i; 
		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		shader->setMatrix4x4("model", model);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

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
	preTransform();

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