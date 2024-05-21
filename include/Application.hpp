#ifndef __APPLICATION__
#define __APPLICATION__
#include <utility>

class GLFWwindow;

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

class Application {
public:
	~Application();
	
	//用于访问实例的静态函数
	static Application* getInstance();

	bool init();

	bool update();

	void destroy();

	void setResizeCallback(ResizeCallback callback) { mResizeCallback = callback; }
	void setKeyBoardCallback(KeyBoardCallback callback) { mKeyBoardCallback = callback; }
	void setMouseCallback(MouseCallback callback) { mMouseCallback = callback; }
	void setCursorCallback(CursorCallback callback) { mCursorCallback = callback; }
	void setScrollCallback(ScrollCallback callback) { mScrollCallback = callback; };

	static void glVersionInfo();

	operator GLFWwindow*() {
		return mWindow;
    }

	std::pair<double, double> getCursorPosition();

public:
	int mWidth{1980};
	int mHeight{1080};

private:
	//C++类内函数指针
	static void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouseCallback(GLFWwindow* window, int button, int action, int mods);
	static void cursorCallback(GLFWwindow* window, double xpos, double ypos);
	static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

private:

	GLFWwindow* mWindow{ nullptr };

	float deltaTime{0.0f};		// 帧时间间隔

	ResizeCallback mResizeCallback{ default_resize };
	KeyBoardCallback mKeyBoardCallback{ default_key };
	MouseCallback mMouseCallback{ default_mouse };
	CursorCallback mCursorCallback{ default_cursor };
	ScrollCallback mScrollCallback{ default_scroll };

	Application();
};
#endif