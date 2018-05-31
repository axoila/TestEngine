#include "Game.h"

#include "RenderSystem.h"

Game::Game()
{
}


Game::~Game()
{
	
}

void Game::Init(const char *title) {
	//init RenderSystem
	RenderSystem* renderSystem = RenderSystem::GetInstance();
	renderSystem->SetTitle(title);
	renderSystem->Init();
	systems.push_back(renderSystem);
}

void Game::Clean() {
	for (System* system : systems) {
		system->Clean();
		free(system);
	}
}

void Game::Update() {
	for (System* system : systems) {
		system->Update();
	}
}

bool Game::Running() {
	for (System* system : systems) {
		if (!system->Running())
			return false;
	}
	return true;
}