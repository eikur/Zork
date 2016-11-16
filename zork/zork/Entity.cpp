#include "Entity.h"

Entity::Entity(const char* name, const char* description, Entity* parent) : name(name), description(description), parent(parent)
{
	if (parent != NULL)
	{
		parent->children.push_back(this);
	}
	type = ENTITY;
}

Entity::~Entity()
{
}

void Entity::Look() const
{
	cout << "** " << name << " **" << endl;
	cout << description << endl;
}

bool Entity::IsTakeable() const
{
	return false;
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
			return *it;
		//if (type == ITEM && (*it)->type == ITEM && (*it)->children.size() > 0)
		if ((*it)->type == ITEM && (*it)->children.size() > 0)
			for (list<Entity*>::const_iterator it2 = (*it)->children.begin(); it2 != (*it)->children.end(); ++it2)
				if (AreEqual((*it2)->name, name) && (*it2)->type == type)	//if (AreEqual((*it2)->name, name) )
					return *it2;
	}
	return NULL;
}
