#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include "Application.hpp"
#include <iostream>

Application* Application::getInstance() {
    static Application mInstance;

	return &mInstance;
}

Application::Application() {

}

Application::~Application() {

}


bool Application::init(const int& width, const int& height) {

	//1 初始化GLFW基本环境
	glfwInit();

	//1.1 设置OpenGL主版本号、次版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//1.2 设置OpenGL启用核心模式（非立即渲染模式）
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//2 创建窗体对象
	mWindow = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
	if (mWindow == nullptr) {
		std::cout << "Failed to create GLFW window" << std::endl;
		return false;
	}

	// 设置当前窗体对象为OpenGL的绘制舞台
	glfwMakeContextCurrent(mWindow);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	// std::cout << "OpenGL version: " << (const char *)glGetString(GL_VERSION) << '\n';
	glVersionInfo();

	// 开启深度测试
	glEnable(GL_DEPTH_TEST);

	//设置opengl视口以及清理颜色
	glViewport(0, 0, width, height);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	// 设置线框绘制模式
  	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	glfwSetFramebufferSizeCallback(mWindow, frameBufferSizeCallback);

	//this就是当前全局唯一的Application对象
	glfwSetWindowUserPointer(mWindow, this);

	//键盘响应
	glfwSetKeyCallback(mWindow, keyCallback);

	return true;
}

bool Application::update() {
	if (glfwWindowShouldClose(mWindow)) {
		return false;
	}

	//接收并分发窗体消息
	//检查消息队列是否有需要处理的鼠标、键盘等消息
	//如果有的话就将消息批量处理，清空队列
	glfwPollEvents();

	//切换双缓存
	glfwSwapBuffers(mWindow);

	return true;
}

void Application::destroy() {
	//退出程序前做相关清理
	glfwTerminate();
}


void Application::frameBufferSizeCallback(GLFWwindow* window, int width, int height) {
	std::cout << "Resize" << std::endl;

	Application* self = (Application*)glfwGetWindowUserPointer(window);
	if (self->mResizeCallback != nullptr) {
		self->mResizeCallback(width, height);
	}

	//if (Application::getInstance()->mResizeCallback != nullptr) {
	//	Application::getInstance()->mResizeCallback(width, height);
	//}
}

void Application::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	Application* self = (Application*)glfwGetWindowUserPointer(window);
	if (self->mKeyBoardCallback != nullptr) {
		self->mKeyBoardCallback(window, key, action, mods);
	}
}

void Application::glVersionInfo() {
	const char* byteGlVersion = (const char *)glGetString(GL_VERSION);
	const char* byteGlVendor = (const char *)glGetString(GL_VENDOR);
	const char* byteGlRenderer = (const char *)glGetString(GL_RENDERER);
	const char* byteSLVersion = (const char *)glGetString(GL_SHADING_LANGUAGE_VERSION);

	std::cout << "OpenGL version: " << byteGlVersion << std::endl;
	std::cout << "GL_VENDOR: " << byteGlVendor << std::endl;
	std::cout << "GL_RENDERER: " << byteGlRenderer << std::endl;
	std::cout << "GLSL version: : " << byteSLVersion << std::endl;
}