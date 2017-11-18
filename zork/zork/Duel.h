#ifndef DUEL_H
#define DUEL_H

#include <iostream>
#include <list>
#include <vector>
#include <algorithm>

#include "Character.h"
#include "Player.h"
#include "Interaction.h"

enum class PlayerTurn {
	OFFENSE,
	DEFENSE
};


class Duel
{

public:
	Duel(Player& player, Character& adversary);
	~Duel();

	void UpdateDuel();
	void PrepareNextRound();

	void PrintRemainingAttacks() const;
	void PrintPlayerComebacks() const;

	void Surrender() const;
	void Win() const;

	bool ChooseOption(const std::vector<std::string>& args);
	Interaction* CheckOption(const std::string& code, const PlayerTurn trn) const;
	bool CheckCorrectComeback() const;

	Interaction* AdversaryFindComeback() const;
	Interaction* Duel::AdversaryChooseAttack() const;

	void DeleteAttackOption(Interaction* target);

	Player& player;
	Character& adversary;
	
	std::list<Interaction*> attacks;
	std::list<Interaction*> player_comebacks;
	std::list<Interaction*> adversary_comebacks;
	int adversary_comebacks_max = 6;
	int adversary_comebacks_cur = 0;

	Interaction* inter[16];
	std::vector<Interaction*> randomizer;

	Interaction* player_choice;
	Interaction* adversary_choice;
	
	int player_wins;
	int adversary_wins;
	PlayerTurn turn;

};

#endif
