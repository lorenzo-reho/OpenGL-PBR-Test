#include "Input.h"

namespace Input {
	bool _key[400];
	bool _mouse[12];
	int _deltaX = 0;
	int _deltaY = 0;

	int _lastX = 0;
	int _lastY = 0;
}


void Input::Update(GLFWwindow* window) {

	for (int i = 32; i <= 349; i++) {
		_key[i] = glfwGetKey(window, i) == GLFW_PRESS;
	}

	for (int i = 0; i < 12; i++) {
		_mouse[i] = glfwGetMouseButton(window, i) == GLFW_PRESS;
	}

	
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	_deltaX = xpos - _lastX;
	_deltaY = ypos - _lastY;

	_lastX = xpos;
	_lastY = ypos;

}

bool Input::GetKeyPressed(int keyCode) {
	return _key[keyCode];
}

bool Input::GetMouseButtonPressed(int buttonCode) {
	return _mouse[buttonCode];
}

int Input::GetCursorDeltaX() {
	return _deltaX;
}

int Input::GetCursorDeltaY() {
	return _deltaY;
}


