#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
class Room;
class Link;


using namespace std;

class Player : public Character
{
public:
	Player(const char* name, const char* description, Room* parent);
	~Player();

	void Look(const vector<string>& args) const;
	void Go(const vector<string>& args);
	void Take(const vector<string>& args);
	void Drop(const vector<string>& args);
	void Inventory(const vector<string>& args) const;
	void Open(const vector<string>& args);
	void Read(const vector<string>& args);

};

#endif