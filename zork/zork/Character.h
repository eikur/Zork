#ifndef __Character__
#define __Character__

#include "Entity.h"

class Character : public Entity {
public:
	Character(const char* name, const char* description, Entity* parent = NULL );
	~Character();
	void Upgrade();
	void Look() const;
};


#endif // !__Character__
