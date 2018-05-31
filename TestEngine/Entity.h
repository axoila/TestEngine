#pragma once

#include <vector>
#include <typeinfo>

#include "Component.h"

class Entity
{
public:
	Entity();
	~Entity();

	void AddComponent(Component* component);

	//no template files in source files I guess
	template <class ComponentType>
	ComponentType* GetComponent()
	{
		for (Component* component : components) {
			ComponentType* casted = dynamic_cast<ComponentType*>(component);
			if (casted)
				return casted;
		}
		return nullptr;
	}

private:
	std::vector<Component*> components;
};

