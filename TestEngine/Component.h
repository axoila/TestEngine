#pragma once

class Entity;

class Component {
public:
	virtual void AddToEntity(Entity* entity) {};
protected:
	Entity * entity;
};