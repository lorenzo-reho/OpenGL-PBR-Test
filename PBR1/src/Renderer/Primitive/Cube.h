#pragma once
#include "../../Core/Common.h"
#include "../Object.h"

class Cube : public Object {

public:
	Cube(glm::mat4 transform);
	// ~Cube();

	void Render(Shader* shader) override;
private:
	void CreateObject() override;
};