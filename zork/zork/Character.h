#ifndef CHARACTER_H
#define CHARACTER_H

#include "Entity.h"
class Room;

using namespace std;

class Character : public Entity {
public:
	Character(const char* name, const char* description, Room* parent );
	Character(const char* name, const char* description, Room* parent, const char* talk_line);
	~Character();

	virtual void Talk() const;
	Room* GetRoom() const;

	bool IsDueling() const;

public:
	bool in_a_duel;

private: 
	string talk_line = "";
};


#endif // CHARACTER_H
