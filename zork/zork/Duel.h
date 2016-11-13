#ifndef DUEL_H
#define DUEL_H

#include <iostream>
#include <list>
#include <math.h>
#include <vector>

#include "Character.h"
#include "Player.h"
#include "Interaction.h"

using namespace std;

enum PlayerTurn {
	OFFENSE, 
	DEFENSE
};
class Duel
{

public:
	Duel(Player* player, Character* adversary);
	~Duel();

	void UpdateDuel();
	void PrepareNextRound();

	void PrintRemainingAttacks() const;
	void PrintPlayerComebacks() const;

	void Surrender() const;
	void Win() const;

	bool ChooseOption(const vector<string>& args);
	Interaction* CheckOption(const string code, PlayerTurn turn) const;
	bool CheckCorrectComeback() const;

	Interaction* AdversaryFindComeback() const;
	Interaction* Duel::AdversaryChooseAttack() const;

	void DeleteAttackOption(Interaction* target);

public:
	Player* player;
	Character* adversary;
	list<Interaction*> attacks;
	list<Interaction*> player_comebacks;
	list<Interaction*> adversary_comebacks;
	Interaction* inter[16];
	PlayerTurn turn;
	Interaction* player_choice;
	Interaction* adversary_choice;
	int player_wins;
	int adversary_wins;


};

#endif
