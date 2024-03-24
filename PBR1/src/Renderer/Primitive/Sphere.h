#pragma once
#include "../Object.h"
#include "vector"
class Sphere : public Object {

public:

	Sphere(glm::mat4 transform, int segments, float radius);
	Sphere(glm::mat4 transform);
	
	void Render(Shader* shader) override;

private:
	void CreateObject() override;
	unsigned int X_SEGMENTS = 64;
	unsigned int Y_SEGMENTS = 64;
	unsigned int indexCount = 0;
	float radius = 1.0f;
};