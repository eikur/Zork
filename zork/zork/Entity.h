#ifndef ENTITY_H
#define ENTITY_H

#include <list>
#include <string>
#include <vector>

using namespace std;

class Entity {

public:
	string name;
	string description;
	Entity* parent;
	list<Entity*> children;

	Entity(const char* name, const char* description, Entity* parent = NULL);
	virtual ~Entity();

	virtual void Look() const;

	void SetNewParent(Entity* new_parent);
		
};
#endif // ENTITY_H

