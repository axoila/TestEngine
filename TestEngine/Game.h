#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <vector>

#include "MeshRenderer.h"
#include "System.h"
#include "Entity.h"

class Game
{
public:
	Game(); //constructor
	~Game(); //deconstructor

	//starting and stopping
	void Init(const char* title);
	void Clean();

	//every frame stuff
	void Update();

	//status
	bool Running();

private:
	std::vector<System*> systems;
	std::vector<Entity*> entities;

};