#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include <iostream>
#include <string>

class Room;
class Link;
class Duel;


class Player : public Character
{
public:
	Player(const std::string& name, const std::string& description, Room* parent);
	~Player();

	void Look(const std::vector<std::string>& args) const;
	void Go(const std::vector<std::string>& args);
	void Take(const std::vector<std::string>& args);
	void Drop(const std::vector<std::string>& args);
	void Inventory() const;
	void Open(const std::vector<std::string>& args);
	void Read(const std::vector<std::string>& args);
	void Use(const std::vector<std::string>& args);
	void Talk(const std::vector<std::string>& args) const;

	bool CanSee() const;

	void StartDuel(const std::vector<std::string>& args);
	void EnterDuel();
	void ExitDuel();
	bool DuelAction(const std::vector<std::string>& args) const;


private: 
	Duel* duel;

};

#endif