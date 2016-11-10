#include "Entity.h"

Entity::Entity(const char* name, const char* description, Entity* parent)
{
	this->name = name;
	this->description = description;
	if (parent != NULL)
	{
		this->parent = parent;
		parent->children.push_back(this);
	}
}

Entity::~Entity()
{
}

void Entity::Look() const
{
}

void Entity::SetNewParent( Entity* new_parent)
{
	if (parent != NULL)
		parent->children.remove(this); 
	parent = new_parent;
	if (parent != NULL)
		parent->children.push_back(this);
}
