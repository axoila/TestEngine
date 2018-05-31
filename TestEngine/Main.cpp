#include <Windows.h>

#define GLM_ENABLE_EXPERIMENTAL

#include <GL/glew.h>
#include <glm/gtx/euler_angles.hpp>
#include <string>


#include "Game.h"
#include "TextureProperty.h"
#include "Camera.h"
#include "RenderSystem.h"
#include "MeshRenderer.h"

Game *game;

int main(int argc, char *args[])
{
	game = new Game();

	game->Init("test");

	
	Entity* object = new Entity();

	Transform* transform = new Transform();
	object->AddComponent(transform);

	std::vector<Mesh*> meshes = std::vector<Mesh*>();

	Mesh::FromObj("./MonkeyMesh.obj", meshes);

	Shader* shader = new Shader("./VertexShader.glsl", "./FragmentShader.glsl");
	Property* texture = new TextureProperty("MainTex", new Texture("./colorgrid.png"));
	Material* material = new Material(shader);
	material->SetCull(Material::NONE);
	material->SetDepthTest(Material::LESS);

	for (Mesh* mesh : meshes) {
		MeshRenderer* renderer = new MeshRenderer(mesh, material);
		object->AddComponent(renderer);

		std::cout << mesh->GetPositions().size() << std::endl;
	}
	

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
	float deltaTime = 0;

	//game loop
	while (game->Running()) {
		counter++;
		if (counter > 1000) {
			deltaTime = (float)(SDL_GetTicks() - startTime) / ((float)counter*1000.0);
			float fps = 1.0f / deltaTime;
			RenderSystem::GetInstance()->SetTitle(std::to_string(fps).c_str());
			startTime = SDL_GetTicks();
			counter = 0;
		}

		rot += deltaTime * 1;

		cameraTransform->SetPosition(glm::vec3(sinf(rot) * 3, 0, cosf(rot) * 3));
		cameraTransform->LookAt(glm::vec3(0));
		
		game->Update();
	}

	game->Clean();

	return 0;
}