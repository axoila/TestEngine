#include "RenderSystem.h"

#include <iostream>


RenderSystem * RenderSystem::GetInstance()
{
	if (instance == nullptr) {
		instance = new RenderSystem();

		std::cout << "new rendersystem created" << std::endl;
	}
	return instance;
}

void RenderSystem::DestroyInstance()
{
	instance->Clean();
	instance = nullptr;
}

RenderSystem::~RenderSystem()
{
}

void RenderSystem::Init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "SDL initialisation failed!" << std::endl;
		isRunning = false;
		return;
	}
	else {
		std::cout << "sdl initialised" << std::endl;
	}

	if (!MakeWindow(title)) {
		std::cout << "failed to create window!" << std::endl;
		isRunning = false;
		return;
	}
	else {
		std::cout << "window created" << std::endl;
	}

	context = SDL_GL_CreateContext(window);

	GLenum status = glewInit();
	if (status != GLEW_OK) {
		std::cout << "failed to initialize GLEW!" << std::endl;
		isRunning = false;
		return;
	}
	else {
		std::cout << "glew initialized" << std::endl;
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	isRunning = true;
}

void RenderSystem::Clean() {
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();

	std::cout << "Stopped SDL" << std::endl;

	isRunning = false;
}

void RenderSystem::Update()
{
	if (!isRunning) {
		std::cerr << "Tried to render with inactive renderSystem" << std::endl;
		return;
	}

	HandleEvents();
	Render();
	SwapBuffers();
}

void RenderSystem::Render() {
	Clear();

	for (Renderer* renderer : renderers) {
		renderer->Draw();
	}
}

void RenderSystem::SwapBuffers() {
	SDL_GL_SwapWindow(window);
}

void RenderSystem::HandleEvents() {
	SDL_Event event;
	while(SDL_PollEvent(&event)){
		switch (event.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;
		default:
			break;
		}
	}
}

void RenderSystem::AddRenderer(Renderer * renderer)
{
	renderers.push_back(renderer);
}

void RenderSystem::RemoveRenderer(Renderer * renderer)
{
	for (auto it = renderers.begin(); it != renderers.end(); ) {
		if (*it == renderer) {
			it = renderers.erase(it);
		}
		else {
			++it;
		}
	}
}

void RenderSystem::SetTitle(const char * title)
{
	this->title = title;
	if (isRunning) {
		SDL_SetWindowTitle(window, title);
	}
}

void RenderSystem::SetActiveCamera(Camera * cam, bool overwrite)
{
	if (!overwrite && activeCamera != nullptr)
		return;

	activeCamera = cam;
}

glm::mat4 RenderSystem::GetViewProjectionMatrix()
{
	if (activeCamera == nullptr)
		return glm::mat4(1);
	else
		return activeCamera->GetViewProjectionMatrix();
}

bool RenderSystem::Running() {
	return isRunning;
}

void RenderSystem::Clear()
{
	glClearColor(1, 0.666667f, 0.733333f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

SDL_Window* RenderSystem::MakeWindow(const char* header) {
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, true);

	window = SDL_CreateWindow(header, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400,
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	return window;
}

//singleton stuff???

RenderSystem::RenderSystem()
{}

RenderSystem* RenderSystem::instance = nullptr;