#include "Item.h"

Item::Item(const std::string& name, const std::string& description, Entity* parent, bool takeable, bool storage, bool locked, EntityType type) 
	: Entity(name, description, type, parent), takeable(takeable), storage(storage), locked(locked)
{
}

Item::~Item()
{
}

void Item::Look() const
{
	std::cout << "** " << name << " **" << std::endl;
	std::cout << description << std::endl;
	if (IsLocked())
	{
		std::cout << " It's closed!" << std::endl;
	}
	else if (HasStorage())
	{
		if (children.size() == 0)
			std::cout << " It's empty!" << std::endl;
		else
		{
			std::cout << " It contains:" << std::endl;
			for (std::list<Entity*>::const_iterator it = children.begin(); it != children.end(); ++it)
				std::cout << "  - " <<  (*it)->name << std::endl;
		}
	}
}

bool Item::IsTakeable() const
{
	return takeable;
}
bool Item::HasStorage() const 
{
	return storage;
}

bool Item::IsLocked() const 
{
	return locked;
}

void Item::Unlock() {
	locked = false;
}