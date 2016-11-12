#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include "Room.h"

using namespace std;

class Player : public Character
{
public:
	Player(const char* name, const char* description, Room* parent);
	~Player();

	void Look(const vector<string>& args) const;
	void Go(const vector<string>& args) const;

};

#endif