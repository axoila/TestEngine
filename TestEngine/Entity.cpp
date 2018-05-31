#include "Entity.h"

#include <iostream>
#include "Transform.h"

Entity::Entity()
{
}


Entity::~Entity()
{
}

void Entity::AddComponent(Component* component)
{
	components.push_back(component);
	component->AddToEntity(this);
}
