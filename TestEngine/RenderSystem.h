#pragma once

#include <vector>
#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "Renderer.h"
#include "System.h"
#include "MeshRenderer.h"
#include "Camera.h"

class RenderSystem : public System
{
public:
	static RenderSystem* GetInstance();
	static void DestroyInstance();

	~RenderSystem();

	void Init() override;
	void Clean() override;

	void Update() override;

	void Render();
	void HandleEvents();
	void SwapBuffers();

	void AddRenderer(Renderer* renderer);
	void RemoveRenderer(Renderer* renderer);
	void SetTitle(const char *title);

	void SetActiveCamera(Camera* cam, bool overwrite = true);
	glm::mat4 GetViewProjectionMatrix();

	bool Running();

private:
	RenderSystem();

	void Clear();
	SDL_Window* MakeWindow(const char* header);

	std::vector<Renderer*> renderers;

	const char* title;
	bool isRunning = false;
	SDL_Window *window;
	SDL_GLContext context;

	Camera* activeCamera = nullptr;

	static RenderSystem* instance;
};

