#include <Windows.h>

#define GLM_ENABLE_EXPERIMENTAL

#include <GL/glew.h>
#include <glm/gtx/euler_angles.hpp>
#include <string>


#include "Game.h"
#include "TextureProperty.h"
#include "Camera.h"
#include "RenderSystem.h"

Game *game;

int main(int argc, char *args[])
{
	game = new Game();

	game->Init("test");

	
		Entity* object = new Entity();

		Transform* transform = new Transform();
		object->AddComponent(transform);

		Vertex cube[] = {
			Vertex(glm::vec3(-1, -1, -1),	glm::vec2(0,0)),
			Vertex(glm::vec3(-1, 1, -1),	glm::vec2(0,1)),
			Vertex(glm::vec3(1, -1, -1),	glm::vec2(1,0)),

			Vertex(glm::vec3(1, 1, -1),		glm::vec2(1,1)),
			Vertex(glm::vec3(1, -1, -1),	glm::vec2(1,0)),
			Vertex(glm::vec3(-1, 1, -1),	glm::vec2(0,1)),


			Vertex(glm::vec3(-1, -1, 1),	glm::vec2(0,0)),
			Vertex(glm::vec3(1, -1, 1),		glm::vec2(1,0)),
			Vertex(glm::vec3(-1, 1, 1),		glm::vec2(0,1)),

			Vertex(glm::vec3(1, 1, 1),		glm::vec2(1,1)),
			Vertex(glm::vec3(-1, 1, 1),		glm::vec2(0,1)),
			Vertex(glm::vec3(1, -1, 1),		glm::vec2(1,0)),


			Vertex(glm::vec3(-1, 1, -1),	glm::vec2(0,0)),
			Vertex(glm::vec3(-1, 1, 1),		glm::vec2(0,1)),
			Vertex(glm::vec3(1, 1, -1),		glm::vec2(1,0)),

			Vertex(glm::vec3(1, 1, 1),		glm::vec2(1,1)),
			Vertex(glm::vec3(1, 1, -1),		glm::vec2(1,0)),
			Vertex(glm::vec3(-1, 1, 1),		glm::vec2(0,1)),


			Vertex(glm::vec3(-1, -1, -1),	glm::vec2(0,0)),
			Vertex(glm::vec3(1, -1, -1),	glm::vec2(1,0)),
			Vertex(glm::vec3(-1, -1, 1),	glm::vec2(0,1)),

			Vertex(glm::vec3(1, -1, 1),		glm::vec2(1,1)),
			Vertex(glm::vec3(-1, -1, 1),	glm::vec2(0,1)),
			Vertex(glm::vec3(1, -1, -1),	glm::vec2(1,0)),


			Vertex(glm::vec3(1, -1, -1),	glm::vec2(0,0)),
			Vertex(glm::vec3(1, 1, -1),		glm::vec2(1,0)),
			Vertex(glm::vec3(1, -1, 1),		glm::vec2(0,1)),

			Vertex(glm::vec3(1, 1, 1),		glm::vec2(1,1)),
			Vertex(glm::vec3(1, -1, 1),		glm::vec2(0,1)),
			Vertex(glm::vec3(1, 1, -1),		glm::vec2(1,0)),

		
			Vertex(glm::vec3(-1, -1, -1),	glm::vec2(0,0)),
			Vertex(glm::vec3(-1, -1, 1),	glm::vec2(0,1)),
			Vertex(glm::vec3(-1, 1, -1),	glm::vec2(1,0)),

			Vertex(glm::vec3(-1, 1, 1),		glm::vec2(1,1)),
			Vertex(glm::vec3(-1, 1, -1),	glm::vec2(1,0)),
			Vertex(glm::vec3(-1, -1, 1),	glm::vec2(0,1)), };

		Mesh* mesh = new Mesh(cube, sizeof(cube) / sizeof(cube[0]));

		Shader* shader = new Shader("./VertexShader.glsl", "./FragmentShader.glsl");
		Property* texture = new TextureProperty("MainTex", new Texture("./colorgrid.png"));
		Material* material = new Material(shader);
		material->SetCull(Material::GREATER);
		material->SetDepthTest(Material::LESS);

		MeshRenderer* renderer = new MeshRenderer(mesh, material);
		object->AddComponent(renderer);
	

	Transform* cameraTransform = new Transform();
	cameraTransform->SetPosition(glm::vec3(0, 0, -3));
	cameraTransform->LookAt(glm::vec3(0));

	Entity* camera = new Entity();
		
	camera->AddComponent(cameraTransform);

	Camera* cameraComponent = new Camera();
	cameraComponent->SetAspectRatio(600.0f / 400.0f);
	cameraComponent->SetFov(80);
	cameraComponent->SetNearFarPlanes(0.1f, 10000.0f);
	camera->AddComponent(cameraComponent);

	float rot = 0;

	int counter = 0;
	Uint32 startTime = SDL_GetTicks();

	glm::mat4 mvp = cameraComponent->GetViewProjectionMatrix();
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			std::cout << mvp[x][y] << " | ";
		}
		std::cout << std::endl;
	}

	//game loop
	while (game->Running()) {
			
		float fps = 1.0f/(((1.0f * (SDL_GetTicks() - startTime)) / counter)/1000.0f);
		RenderSystem::GetInstance()->SetTitle(std::to_string(fps).c_str());
		startTime = SDL_GetTicks();

		rot += 0.001f;

		cameraTransform->SetPosition(glm::vec3(sinf(rot) * 3, 0, cosf(rot) * 3));
		cameraTransform->LookAt(glm::vec3(0));
		
		game->Update();
	}

	game->Clean();

	return 0;
}