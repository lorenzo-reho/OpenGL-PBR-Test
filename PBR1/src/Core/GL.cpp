#include "GL.h"

namespace GL {
	GLFWwindow* _window;
	int _currentWidth;
	int _currentHeight;
}

void GL::resize_callback(GLFWwindow* window, int width, int height) {
	if (width == 0 || height == 0) return;
	glViewport(0, 0, width, height);
	_currentWidth = width;
	_currentHeight = height;
}

int GL::Init(int width, int height) {
	if (glfwInit() == -1) {
		return 1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	_window = glfwCreateWindow(width, height, "PBR1", NULL, NULL);
	_currentWidth = width;
	_currentHeight = height;

	if (!_window) {
		return 2;
	}
	glfwMakeContextCurrent(_window);
	glfwSetFramebufferSizeCallback(_window, resize_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		return 3;

	return 0;
}

GLFWwindow* GL::GetWindowPtr() {
	return _window;
}

int GL::GetCurrentWidth() {
	return _currentWidth;
}

int GL::GetCurrentHeight() {
	return _currentHeight;
}

bool GL::IsWindowOpen() {
	return !glfwWindowShouldClose(_window);
}

void GL::SwapBuffer() {
	glfwSwapBuffers(_window);
}

void GL::PollEvent() {
	glfwPollEvents();
}

void GL::Shutdown() {
	glfwTerminate();
}