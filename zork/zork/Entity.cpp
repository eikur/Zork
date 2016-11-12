#include "Entity.h"

Entity::Entity(const char* name, const char* description, Entity* parent) : name(name), description(description), parent(parent)
{
	if (parent != NULL)
	{
		parent->children.push_back(this);
	}
}

Entity::~Entity()
{
}

void Entity::Look() const
{
	cout << "** " << name << " **" << endl;
	cout << description << endl;
}

void Entity::SetNewParent(Entity* new_parent)
{
	if (parent != NULL)
		parent->children.remove(this);
	parent = new_parent;
	if (parent != NULL)
		parent->children.push_back(this);
}

Entity * Entity::Find(const string & name, EntityType type)
{
	for (list<Entity*>::const_iterator it = children.begin(); it != children.end(); ++it)
	{
		if (AreEqual((*it)->name, name) && (*it)->type == type)
		{
			return *it;
		}
	}
	return NULL;
}
