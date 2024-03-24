#include "Renderer.h"


void Renderer::Render(Shader* shader, std::vector<Object*> objects, Camera* camera) {
	
	glClearColor(0, 0, 0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 projection = glm::perspective(1.0f, (float)GL::GetCurrentWidth() / (float)GL::GetCurrentHeight(), 0.1f, 100.0f);
	// glm::mat4 model(1.0f);
	glm::mat4 view = camera->GetView();

	// view = glm::rotate(view, glm::radians(-20.0f), glm::vec3(0, 1, 0));
	// view = glm::translate(view, glm::vec3(0, 0, -5.0f));

	glm::vec3 lightPositions[] = {
		glm::vec3(-10.0f, 10.0f, 10.0f),
		glm::vec3(10.0f, 10.0f, 10.0f),
		glm::vec3(-10.0f, -10.0f, 10.0f),
		glm::vec3(10.0f, -10.0f, 10.0f)
	};

	glm::vec3 lightColors[] = {
			glm::vec3(300.0f, 300.0f, 300.0f),
			glm::vec3(300.0f, 300.0f, 300.0f),
			glm::vec3(300.0f, 300.0f, 300.0f),
			glm::vec3(300.0f, 300.0f, 300.0f)
	};

	for (int i = 0; i < objects.size(); i++) {
		shader->Use();
		shader->SetMat4("projection", projection);
		shader->SetMat4("model", objects[i]->GetTransform());
		shader->SetMat4("view", view);

		shader->SetVec3("albedo", glm::vec3(0.5f, 0.0f, 0.0f));
		shader->SetFloat("metallic", 0);
		shader->SetFloat("roughness", 0.2);


		shader->SetVec3("camPos", camera->GetCameraPosition());
		std::string tmp = "lightPositions[" + std::to_string(i) + "]";
		shader->SetVec3(tmp.c_str(), lightPositions[i]);

		tmp = "lightColors[" + std::to_string(i) + "]";
		shader->SetVec3(tmp.c_str(), lightColors[i]);

		objects[i]->Render(shader);

	}
}
