#ifndef __APPLICATION__
#define __APPLICATION__
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <iostream>
#include <utility>

using ResizeCallback = void(*)(int width, int height);
using KeyBoardCallback = void(*)(GLFWwindow *window, int key, int action, int mods);
using MouseCallback = void(*)(int button, int action, int mods);
using CursorCallback = void(*)(double xpos, double ypos);
using ScrollCallback = void(*)(double xoffset, double yoffset);

void default_resize(int width, int height);
void default_key(GLFWwindow *window, int key, int action, int mods);
void default_mouse(int button, int action, int mods);
void default_cursor(double xpos, double ypos);
void default_scroll(double xoffset, double yoffset);

#define gl_app Application::getInstance()

class Application {
public:
	~Application(){};
	
	//用于访问实例的静态函数
	static Application* getInstance() {
		static Application mInstance;
		return &mInstance;
	}

	bool init() {
		//1 初始化GLFW基本环境
		glfwInit();
		//1.1 设置OpenGL主版本号、次版本号
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		//1.2 设置OpenGL启用核心模式（非立即渲染模式）
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		//2 创建窗体对象
		mWindow = glfwCreateWindow(mWidth, mHeight, "LearnOpenGL", NULL, NULL);
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
		glViewport(0, 0, mWidth, mHeight);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		// glClearColor(255.0 / 255.0f, 218.0 / 255.0f, 185.0 / 255.0f, 1.0f);

		// 设置线框绘制模式
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		
		glfwSetFramebufferSizeCallback(mWindow, frameBufferSizeCallback);
		//this就是当前全局唯一的Application对象
		glfwSetWindowUserPointer(mWindow, this);
		//键盘响应
		glfwSetKeyCallback(mWindow, keyCallback);
		// 鼠标点击事件响应
		glfwSetMouseButtonCallback(mWindow, mouseCallback);
		// 鼠标移动事件响应
		glfwSetCursorPosCallback(mWindow, cursorCallback);
		// 鼠标滚轮事件
		glfwSetScrollCallback(mWindow, scrollCallback);

		return true;
	}

	template <typename FUNC>
	void rendering(FUNC func) {
		while (!glfwWindowShouldClose(mWindow)) {
			//执行opengl画布清理操作
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			frame.currentFrame = static_cast<float>(glfwGetTime());
			frame.deltaTime = frame.currentFrame - frame.lastFrame;
			frame.lastFrame = frame.currentFrame;

			func();

			//接收并分发窗体消息
			//检查消息队列是否有需要处理的鼠标、键盘等消息
			//如果有的话就将消息批量处理，清空队列
			glfwPollEvents();

			//切换双缓存
			glfwSwapBuffers(mWindow);
		}
	}

	void destroy() {
		//退出程序前做相关清理
		glfwTerminate();
	}

	void setResizeCallback(ResizeCallback callback) { mResizeCallback = callback; }
	void setKeyBoardCallback(KeyBoardCallback callback) { mKeyBoardCallback = callback; }
	void setMouseCallback(MouseCallback callback) { mMouseCallback = callback; }
	void setCursorCallback(CursorCallback callback) { mCursorCallback = callback; }
	void setScrollCallback(ScrollCallback callback) { mScrollCallback = callback; };

	static void glVersionInfo() {
		const char* byteGlVersion = (const char *)glGetString(GL_VERSION);
		const char* byteGlVendor = (const char *)glGetString(GL_VENDOR);
		const char* byteGlRenderer = (const char *)glGetString(GL_RENDERER);
		const char* byteSLVersion = (const char *)glGetString(GL_SHADING_LANGUAGE_VERSION);

		std::cout << "OpenGL version: " << byteGlVersion << std::endl;
		std::cout << "GL_VENDOR: " << byteGlVendor << std::endl;
		std::cout << "GL_RENDERER: " << byteGlRenderer << std::endl;
		std::cout << "GLSL version: : " << byteSLVersion << std::endl;
	}

	operator GLFWwindow*() {
		return mWindow;
    }

	std::pair<double, double> getCursorPosition() {
		double x{}, y{};
		glfwGetCursorPos(mWindow, &x, &y);

		return {x, y};
	}

public:
	int mWidth{1980};
	int mHeight{1080};

private:
	//C++类内函数指针
	static void frameBufferSizeCallback(GLFWwindow* window, int width, int height) {
		std::cout << "resize" << std::endl;

		Application* self = (Application*)glfwGetWindowUserPointer(window);
		if (self->mResizeCallback != nullptr) {
			self->mResizeCallback(width, height);
		}
	}
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		Application* self = (Application*)glfwGetWindowUserPointer(window);
		if (self->mKeyBoardCallback != nullptr) {
			self->mKeyBoardCallback(window, key, action, mods);
		}
	}
	static void mouseCallback(GLFWwindow* window, int button, int action, int mods) {
		Application* self = (Application*)glfwGetWindowUserPointer(window);
		if (self->mMouseCallback != nullptr) {
			self->mMouseCallback(button, action, mods);
		}
	}
	static void cursorCallback(GLFWwindow* window, double xpos, double ypos) {
		Application* self = (Application*)glfwGetWindowUserPointer(window);
		if (self->mCursorCallback != nullptr) {
			self->mCursorCallback(xpos, ypos);
		}
	}
	static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
		Application* self = (Application*)glfwGetWindowUserPointer(window);
		if (self->mScrollCallback != nullptr) {
			self->mScrollCallback(xoffset, yoffset);
		}
	}

public:
	struct Frame {
		float currentFrame{0.0f};
		float lastFrame{0.0f};
		float deltaTime{0.0f};	// 帧时间间隔
	};

	Frame frame;

private:

	GLFWwindow* mWindow{ nullptr };

	ResizeCallback mResizeCallback{ default_resize };
	KeyBoardCallback mKeyBoardCallback{ default_key };
	MouseCallback mMouseCallback{ default_mouse };
	CursorCallback mCursorCallback{ default_cursor };
	ScrollCallback mScrollCallback{ default_scroll };

	Application(){};
};

void default_resize(int width, int height) {
	std::cout << "(width, height): " << "(" << width << ", " << height << ")" << std::endl;
	glViewport(0, 0, width, height);
	gl_app->mWidth = width;
	gl_app->mHeight = height;
	std::cout << "default_resize" << std::endl;
}

void default_key(GLFWwindow *window, int key, int action, int mods) {
	std::cout << key << std::endl;
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

void default_mouse(int button, int action, int mods) {
	std::cout << "鼠标点击：(" << button << ", " << action << ", " << mods << ")" << std::endl;
}

void default_cursor(double xpos, double ypos) {
	std::cout << "鼠标移动：(" << xpos << ", " << ypos << ")" << std::endl;
}

void default_scroll(double xoffset, double yoffset) {
	std::cout << "鼠标滚轮: x offset = " << xoffset << ", y offset = " << yoffset << std::endl;
}
#endif