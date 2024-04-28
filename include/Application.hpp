#ifndef __APPLICATION__
#define __APPLICATION__

class GLFWwindow;

using ResizeCallback = void(*)(int width, int height);
using KeyBoardCallback = void(*)(GLFWwindow *window, int key, int action, int mods);

class Application {
public:
	~Application();
	
	//用于访问实例的静态函数
	static Application* getInstance();

	bool init(const int& width = 800, const int& height = 600);

	bool update();

	void destroy();

	void setResizeCallback(ResizeCallback callback) { mResizeCallback = callback; }
	void setKeyBoardCallback(KeyBoardCallback callback) { mKeyBoardCallback = callback; }

	static void glVersionInfo(void);

private:
	//C++类内函数指针
	static void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

private:

	GLFWwindow* mWindow{ nullptr };

	ResizeCallback mResizeCallback{ nullptr };
	KeyBoardCallback mKeyBoardCallback{ nullptr };

	Application();
};

#endif