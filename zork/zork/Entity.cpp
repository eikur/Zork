#include "Entity.h"

Entity::Entity(const std::string& name, const std::string& description, EntityType type, Entity* parent) 
	: name(name), description(description), _type(type), parent(parent)
{
	if (parent != nullptr)
	{
		parent->children.push_back(this);
	}
}

Entity::~Entity()
{
}

void Entity::Look() const
{
	std::cout << "** " << name << " **" << std::endl;
	std::cout << description << std::endl;
}

bool Entity::IsTakeable() const
{
	return false;
}

EntityType Entity::getType() const
{
	return _type;
}

void Entity::SetNewParent(Entity* new_parent)
{
	if (parent != nullptr)
		parent->children.remove(this);
	parent = new_parent;
	if (parent != nullptr)
		parent->children.push_back(this);
}

Entity * Entity::Find(const std::string& search_name, EntityType search_type) const
{	
	for (std::list<Entity*>::const_iterator it = children.begin(); it != children.end(); ++it)
	{
		if (AreEqual((*it)->name, search_name) && (*it)->getType() == search_type)
			return *it;
		if ((*it)->getType() == EntityType::ITEM && (*it)->children.size() > 0)
			for (std::list<Entity*>::const_iterator it2 = (*it)->children.begin(); it2 != (*it)->children.end(); ++it2)
				if (AreEqual((*it2)->name, search_name) && (*it2)->getType() == search_type)
					return *it2;
	}
	return nullptr;
}
