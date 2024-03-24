#include "Engine.h"

void Engine::Run() {
	// inizializzazioni
	int error = GL::Init(700, 800);
	if (error ^ 0) {
		std::cout << "Errore nella configurazione iniziale" << std::endl;
		return;
	}

	Shader* shader = new Shader("res/shaders/vertex.vert", "res/shaders/fragment.frag");
	// Object* cube = new Cube();
	std::vector<Object*> spheres;
	for (int i = -3; i <= 3; i++) {
		for (int j = -3; j <= 3; j++) {

			glm::mat4 transform = glm::mat4(1.0f);
			transform = glm::translate(transform, glm::vec3(j * (1.0f + 0.1f), i * (1.0f + 0.1f), 0));

			Object* sphere = new Sphere(transform, 64, 0.5f);
			spheres.push_back(sphere);
		}
	}

	glm::mat4 transform = glm::mat4(1.0f);
	Object* sphere = new Sphere(transform, 64, 0.5f);


	Camera* camera = new Camera(10.0f);
	// render loop

	glEnable(GL_DEPTH_TEST);

	while (GL::IsWindowOpen()) {
		Input::Update(GL::GetWindowPtr());
		camera->Update(0.0f);
		Renderer::Render(shader, spheres, camera);

		GL::SwapBuffer();
		GL::PollEvent();
	}

	GL::Shutdown();

}