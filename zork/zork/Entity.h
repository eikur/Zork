#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <list>
#include <string>

using namespace std;

class Entity {

public:
	string name;
	string description;
	Entity* parent;
	list<Entity*> childs;

	Entity(const char* name, const char* description, Entity* parent = NULL);

	virtual ~Entity();
	virtual void Update();
	virtual void Look() const;
		
};
#endif // ENTITY_H

