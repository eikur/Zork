#ifndef ENTITY_H
#define ENTITY_H

#include <list>
#include <string>
#include <vector>
#include <iostream>

#include "Input.h"

enum class EntityType 
{
	ENTITY,
	ROOM,
	LINK,
	CHARACTER,
	PLAYER,
	ITEM
};

class Entity {

public:
	Entity(const std::string& name, const std::string& description, EntityType type = EntityType::ENTITY, Entity* parent = nullptr);
	virtual ~Entity();

	virtual void Look() const;
	virtual bool IsTakeable() const;

	void SetNewParent(Entity* new_parent);

	Entity* Find(const std::string& searchName, EntityType searchType) const;
	EntityType getType() const;

	std::string name = "no name";
	std::string description = "no description";
	Entity* parent = nullptr;
	std::list<Entity*> children;

private:
	EntityType _type = EntityType::ENTITY;
};
#endif // ENTITY_H

