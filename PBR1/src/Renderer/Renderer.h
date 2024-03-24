#pragma once
#include "../Core/Common.h"
#include "../Core/GL.h"
#include "Shader.h"
#include "Primitive/Cube.h"
#include "Primitive/Sphere.h"
#include "Camera.h"

namespace Renderer {
	
	void Render(Shader* shader, std::vector<Object*> objects, Camera* camera);

}