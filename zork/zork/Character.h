#ifndef CHARACTER_H
#define CHARACTER_H

#include "Entity.h"
#include "Room.h"

class Character : public Entity {
public:
	Character(const char* name, const char* description, Room* room );
	~Character();

	virtual void Look(const vector<string>& args) const;
	virtual void Go(const vector<string>& args) const;
	virtual void Take(const vector<string>& args) const;
	virtual void Inventory(const vector<string>& args) const;	// necesito pasar args?
	virtual void Attack(const vector<string>& args) const;
	virtual void Use(const vector<string>& args) const;
	virtual void Drop(const vector<string>& args) const;
	virtual void Status(const vector<string>& args) const;	// necesito pasar args?
	
};


#endif // CHARACTER_H
