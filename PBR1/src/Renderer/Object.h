#pragma once
#include "Shader.h"

class Object {
public:
	Object(glm::mat4 transform);
	virtual void Render(Shader* shader) = 0;

	glm::mat4 GetTransform();
	unsigned int GetVAO();
protected:
	unsigned int _VBO, _EBO, _VAO;
	glm::mat4 transform; // world space transform

	virtual void CreateObject() = 0;
	
};