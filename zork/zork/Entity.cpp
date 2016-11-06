#include "Entity.h"

Entity::Entity(const char* name, const char* description, Entity* parent = NULL)
{
	this->name = name;
	this->description = description;
	if (parent != NULL)
		parent->childs.push_back(this);
}

Entity::~Entity()
{
	//consider removing childs list
}

void Entity::Update()
{}