#pragma once
#include "Common.h"

namespace Input {

	void Update(GLFWwindow* window);
	bool GetKeyPressed(int keyCode);
	bool GetMouseButtonPressed(int buttonCode);
	int GetCursorDeltaX();
	int GetCursorDeltaY();
}