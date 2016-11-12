#ifndef ENTITY_H
#define ENTITY_H

#include <list>
#include <string>
#include <vector>
#include <iostream>

#include "Input.h"

using namespace std;

enum EntityType 
{
	ENTITY,
	ROOM,
	LINK,
	CHARACTER,
	PLAYER,
	ITEM,
	NOTE
};


class Entity {

public:
	Entity(const char* name, const char* description, Entity* parent = NULL);
	virtual ~Entity();

	virtual void Look() const;

	void SetNewParent(Entity* new_parent);

	Entity* Find(const string& name, EntityType type);
	
	string name;
	string description;
	Entity* parent;
	list<Entity*> children;
	EntityType type;
		
};
#endif // ENTITY_H

