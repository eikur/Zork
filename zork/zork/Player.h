#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include <iostream>

class Room;
class Link;
class Duel;


class Player : public Character
{
public:
	Player(const char* name, const char* description, Room* parent);
	~Player();

	void Look(const vector<string>& args) const;
	void Go(const vector<string>& args);
	void Take(const vector<string>& args);
	void Drop(const vector<string>& args); 
	void Inventory() const;
	void Open(const vector<string>& args);
	void Read(const vector<string>& args);
	void Use(const vector<string>& args);
	void Talk(const vector<string>& args) const;


	bool CanSee() const;

	void StartDuel(const vector<string>& args);
	void EnterDuel();
	void ExitDuel();
	bool DuelAction(const vector<string>& args) const;


private: 
	Duel* duel;

};

#endif