#pragma once
#include "Common.h"

namespace GL {

	
	int Init(int width, int height);
	GLFWwindow* GetWindowPtr();
	int GetCurrentWidth();
	int GetCurrentHeight();
	bool IsWindowOpen();
	void Shutdown();
	void SwapBuffer();
	void PollEvent();


	void resize_callback(GLFWwindow* window, int width, int height);

}