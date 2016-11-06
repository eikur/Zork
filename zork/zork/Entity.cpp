#include "Entity.h"

Entity::Entity(const char* name, const char* description, Entity* parent)
{
	this->name = name;
	this->description = description;
	if (parent != NULL)
		parent->childs.push_back(this);
}

Entity::~Entity()
{
}

void Entity::Update()
{}

void Entity::Look() const
{
}
