#include "Duel.h"

Duel::Duel(Player& player, Character& adversary): player(player), adversary(adversary)
{
	inter[0] = new Interaction("farmer", "You fight like a dairy farmer", ATTACK, nullptr);
	inter[1] = new Interaction("stand", "You will never stand a chance", ATTACK, nullptr);
	inter[2] = new Interaction("begins", "Your defeat begins with me", ATTACK, nullptr);
	inter[3] = new Interaction("brain", "My brain is on a whole another level", ATTACK, nullptr);
	inter[4] = new Interaction("feet", "People fall at my feet when they see me coming", ATTACK, nullptr);
	inter[5] = new Interaction("diapers", "Have you stopped wearing diapers yet?", ATTACK, nullptr);
	inter[6] = new Interaction("manners", "You have the manners of a beggar.", ATTACK, nullptr);

	inter[7] = new Interaction("cow", "How appropriate. You fight like a cow", COMEBACK, inter[0]);
	inter[8] = new Interaction("sheng", "Little you know, I overcame Sheng Long TWICE!", COMEBACK, inter[1]);
	inter[9] = new Interaction("ugly", "Too bad ugly also begins with U!", COMEBACK, inter[2]);
	inter[10] = new Interaction("god", "I thank god you rarely use it!", COMEBACK, inter[3]);
	inter[11] = new Interaction("breath", "Even BEFORE they smell your breath?", COMEBACK, inter[4]);
	inter[12] = new Interaction("borrow", "Why, did you want to borrow one?", COMEBACK, inter[5]);
	inter[13] = new Interaction("sure", "I wanted to make sure you'd feel comfortable with me", COMEBACK, inter[6]);
	inter[14] = new Interaction("mother", "So is your mother!", COMEBACK, nullptr);
	inter[15] = new Interaction("yeah", "Oh yeah?", COMEBACK, nullptr);

	for (int i = 0; i < 16; i++)
		randomizer.push_back(inter[i]);
	random_shuffle(randomizer.begin(), randomizer.end());

	for (std::vector<Interaction*>::const_iterator it = randomizer.cbegin(); it != randomizer.cend(); ++it)
	{
		if ((*it)->type == ATTACK)
		{
			attacks.push_back((*it));
			continue;
		}
		if ((*it)->type == COMEBACK)
		{
			player_comebacks.push_back((*it));
			continue;
		}
	}
	random_shuffle(randomizer.begin(), randomizer.end());
	for (std::vector<Interaction*>::const_iterator it = randomizer.cbegin(); it != randomizer.cend() && adversary_comebacks_cur < adversary_comebacks_max; ++it)
	{
		if ((*it)->type == COMEBACK)
		{
			adversary_comebacks.push_back((*it));
			adversary_comebacks_cur++;
			continue;
		}
	}

	turn = PlayerTurn::OFFENSE;
	player_wins = adversary_wins = 0;
	player.EnterDuel();
	PrintRemainingAttacks();
}

Duel::~Duel(){

	for (std::vector<Interaction*>::iterator it = randomizer.begin(); it != randomizer.end(); ++it)
		delete *it;
	randomizer.clear();

	attacks.clear();
	player_comebacks.clear();
	adversary_comebacks.clear();

}


bool Duel::ChooseOption( const std::vector<std::string>& args){
	if (AreEqual(args[0], "surrender") ) {
		Surrender();
		return true;
	}
	player_choice = CheckOption(args[0], turn);
	if (player_choice == nullptr)
		return false; 
	UpdateDuel();
	return true;
}


void Duel::PrintRemainingAttacks() const{
	std::cout << "** Available attacks **" << std::endl;
	for (std::list<Interaction*>::const_iterator it = attacks.cbegin(); it != attacks.cend(); ++it)
		(*it)->Print();
	std::cout << std::endl << "I say:";
}

void Duel::PrintPlayerComebacks()const {
	std::cout << "** Available comebacks **" << std::endl;
	for (std::list<Interaction*>::const_iterator it = player_comebacks.cbegin(); it != player_comebacks.cend(); ++it)
		(*it)->Print();
	std::cout << std::endl << "I say:";
}
void Duel::Surrender() const {
	std::cout << "I surrendered the duel!!" << std::endl;
	player.ExitDuel();
}

void Duel::UpdateDuel(){
	if (turn == PlayerTurn::OFFENSE)
	{
		player_choice->Say();
		adversary_choice = AdversaryFindComeback();
		if (adversary_choice == nullptr)
		{
			std::cout << adversary.name << " says:" << std::endl;
			std::cout << "So's your mother!" << std::endl;
			std::cout << std::endl << "** I won advantage! **" << std::endl << std::endl;
			turn = PlayerTurn::OFFENSE;
			player_wins++;
		}
		else
		{
			std::cout << adversary.name << " says: "  << std::endl;
			adversary_choice->Say(); 
			std::cout << "** I lost advantage... **" << std::endl << std::endl;
			turn = PlayerTurn::DEFENSE;
			adversary_wins++;
		}
		DeleteAttackOption(player_choice);
		PrepareNextRound();
		return;
	}
	if (turn == PlayerTurn::DEFENSE)
	{
		player_choice->Say();
		if (CheckCorrectComeback())
		{
			std::cout << std::endl << "** You won advantage! **" << std::endl << std::endl;
			turn = PlayerTurn::OFFENSE;
			player_wins++;
		}
		else
		{
			std::cout << "** You lost advantage! **" << std::endl << std::endl;
			turn = PlayerTurn::DEFENSE;
			adversary_wins++;
		}
		DeleteAttackOption(adversary_choice);
		PrepareNextRound();
		return;
	}
}

Interaction* Duel::CheckOption(const std::string& code, const PlayerTurn trn) const
{
	if (trn == PlayerTurn::OFFENSE)
	{
		for (std::list<Interaction*>::const_iterator it = attacks.begin(); it != attacks.end(); ++it)
			if (AreEqual((*it)->code, code))
				return *it;
	}
	if (trn == PlayerTurn::DEFENSE)
	{
		for (std::list<Interaction*>::const_iterator it = player_comebacks.begin(); it != player_comebacks.end(); ++it)
			if (AreEqual((*it)->code, code))
				return *it;
	}
	return nullptr;
}

bool Duel::CheckCorrectComeback() const
{
	for (std::list<Interaction*>::const_iterator it = player_comebacks.begin(); it != player_comebacks.end(); ++it)
		if ((*it)->response_to == adversary_choice && *it == player_choice)
			return true;
	return false;
}

Interaction* Duel::AdversaryChooseAttack() const {
	//improvement: randomize the attacks
	return attacks.front();
}
Interaction* Duel::AdversaryFindComeback() const
{
	for (std::list<Interaction*>::const_iterator it = adversary_comebacks.begin(); it != adversary_comebacks.end(); ++it)
		if ((*it)->response_to == player_choice)
			return *it;
	return nullptr;
}

void Duel::DeleteAttackOption( Interaction* target)
{
	attacks.remove(target);
	target = nullptr;
}

void Duel::PrepareNextRound() {
	if (player_wins == 3)
	{
		std::cout << std::endl << "With my last move, I opened a hole in " << adversary.name << "'s defense" << std::endl;
		std::cout << "There is simply no way anybody could retaliate from this position!" << std::endl;
		std::cout << adversary.name << " surrenders! I've won!!" << std::endl;
		Win();
		return;
	}
	if (adversary_wins == 3)
	{
		std::cout << std::endl << "With " << adversary.name << "'s last move, my defense was broken" << std::endl;
		std::cout << "There is no way I can retaliate from this position" << std::endl;
		Surrender();
		return;
	}
	std::cout << "***** Next round ***** " << std::endl;
	if (turn == PlayerTurn::OFFENSE)
	{
		PrintRemainingAttacks();
	}
	else
	{
		adversary_choice = AdversaryChooseAttack();
		std::cout << adversary.name << " says: " << std::endl;
		adversary_choice->Say();
		PrintPlayerComebacks();
	}
}

void Duel::Win() const
{
	adversary.GiveDuelPrize(player);
	adversary.setBeaten(true);
	player.ExitDuel();
}