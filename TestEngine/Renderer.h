#pragma once

#include "Component.h"
#include "Entity.h"

class Renderer : public Component {
public:
	virtual void Draw() {};
};