#include "Object.h"

Object::Object(glm::mat4 transform): _VBO(-1), _VAO(-1), _EBO(-1) {
	this->transform = transform;
}

unsigned int Object::GetVAO() {
	return _VAO;
}

glm::mat4 Object::GetTransform() {
	return transform;
}

