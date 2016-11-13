#ifndef DUEL_H
#define DUEL_H

#include <iostream>
#include <list>
#include <math.h>

#include "Character.h"
#include "Player.h"
#include "Interaction.h"

using namespace std;

class Duel
{

public:
	Duel(Player* player, Character* adversary);
	~Duel();

	bool ChooseOption( const string& option) const;
	void PrintRemainingAttacks() const;
	void PrintPlayerComebacks() const;

	void Surrender();

public:
	Player* player;
	Character* adversary;
	list<Interaction*> attacks;
	list<Interaction*> player_comebacks;
	list<Interaction*> adversary_comebacks;

	Interaction* inter[16];




};

#endif
