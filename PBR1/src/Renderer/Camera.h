#pragma once
#include "../Core/Common.h"
#include "../Core/Input.h"
// Arcball
class Camera {

public:
	Camera(float distance) : 
		cameraTarget(glm::vec3(0)), 
		cameraPosition(glm::vec3(0)),
		distance(10.0f), 
		forward(glm::vec3(0, 0, 1)), 
		right(glm::vec3(1, 0, 0)), 
		up(glm::vec3(0, 1, 0)), 
		yaw(0), 
		pitch(0.0f){

		this->distance = distance;
		
	}

	void Move(double sensitivity) {

		pitch += -Input::GetCursorDeltaY() * sensitivity;
		yaw += -Input::GetCursorDeltaX() * sensitivity;

		if (pitch <= -89.0f) pitch = -89.0f;
		if (pitch >= 89.0f) pitch = 89.0f;

		glm::mat4 rot1 = glm::rotate(glm::mat4(1.0f), glm::radians(pitch), glm::vec3(1, 0, 0));
		glm::mat4 rot2 = glm::rotate(glm::mat4(1.0f), glm::radians(yaw), glm::vec3(0, 1, 0));

		glm::mat4 base = rot2 * rot1;
		
		// Componenti della nuova base
		right = glm::normalize(glm::vec3(base[0]));
		up = glm::normalize(glm::vec3(base[1]));
		forward = glm::normalize(glm::vec3(base[2]));

	}

	void Update(float deltaTime) {

		if (Input::GetMouseButtonPressed(GLFW_MOUSE_BUTTON_MIDDLE)) {
			Move(0.3f);
		}
		
		cameraPosition = forward * distance;
	}

	glm::mat4 GetView() {
		return glm::lookAt(cameraPosition, cameraTarget, glm::vec3(0, 1, 0));
	}

	glm::vec3 GetCameraPosition() {
		return cameraPosition;
	}

private:
	float distance;
	float pitch;
	float yaw;
	glm::vec3 cameraTarget;
	glm::vec3 cameraPosition;
	glm::vec3 forward;
	glm::vec3 right;
	glm::vec3 up;
};