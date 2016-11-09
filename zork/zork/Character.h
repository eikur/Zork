#ifndef CHARACTER_H
#define CHARACTER_H

#include "Entity.h"

class Character : public Entity {
public:
	Character(const char* name, const char* description, Entity* parent = NULL );
	~Character();
	void Upgrade();
	void Look() const;
};


#endif // CHARACTER_H
