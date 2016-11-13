#include "Duel.h"

Duel::Duel(Player* player, Character* adversary): player(player), adversary(adversary)
{
	inter[0] = new Interaction("farmer", "You fight like a dairy farmer", ATTACK, NULL);
	inter[1] = new Interaction("stand", "You will never stand a chance", ATTACK, NULL);
	inter[2] = new Interaction("begins", "Your defeat begins with me", ATTACK, NULL);
	inter[3] = new Interaction("brain", "My brain is on a whole another level", ATTACK, NULL);
	inter[4] = new Interaction("feet", "People fall at my feet when they see me coming", ATTACK, NULL);
	inter[5] = new Interaction("diapers", "Have you stopped wearing diapers yet?", ATTACK, NULL);
	inter[6] = new Interaction("manners", "You have the manners of a beggar.", ATTACK, NULL);

	inter[7] = new Interaction("cow", "How appropriate. You fight like a cow", COMEBACK, inter[0]);
	inter[8] = new Interaction("sheng", "Little you know, I overcame Sheng Long TWICE!", COMEBACK, inter[1]);
	inter[9] = new Interaction("ugly", "Too bad ugly also begins with U!", COMEBACK, inter[2]);
	inter[10] = new Interaction("god", "I thank god you rarely use it!", COMEBACK, inter[3]);
	inter[11] = new Interaction("breath", "Even BEFORE they smell your breath?", COMEBACK, inter[4]);
	inter[12] = new Interaction("borrow", "Why, did you want to borrow one?", COMEBACK, inter[5]);
	inter[13] = new Interaction("sure", "I wanted to make sure you'd feel comfortable with me", COMEBACK, inter[6]);

	inter[14] = new Interaction("mother", "So is your mother!", COMEBACK, NULL);
	inter[15] = new Interaction("yeah", "Oh yeah?", COMEBACK, NULL);

	for (int i = 0; i < 16; i++)
	{
		if (inter[i]->type == ATTACK)
		{
			attacks.push_back(inter[i]);
			continue;
		}
		if (inter[i]->type == COMEBACK)
		{
			player_comebacks.push_back(inter[i]);
			continue;
		}
	}
	// improvement: random comebacks each time
	adversary_comebacks.push_back(inter[7]);
	adversary_comebacks.push_back(inter[10]);
	adversary_comebacks.push_back(inter[11]);
	adversary_comebacks.push_back(inter[8]);
	adversary_comebacks.push_back(inter[9]);

	turn = OFFENSE;
	player_wins = adversary_wins = 0;
	player->EnterDuel();
	PrintRemainingAttacks();
}

Duel::~Duel(){
	
	for (list<Interaction*>::iterator it = attacks.begin(); it != attacks.end(); ++it)
		delete *it;
	attacks.clear();

	for (list<Interaction*>::iterator it = player_comebacks.begin(); it != player_comebacks.end(); ++it)
		delete *it;
	player_comebacks.clear();

	for (list<Interaction*>::iterator it = adversary_comebacks.begin(); it != adversary_comebacks.end(); ++it)
		delete *it;
	adversary_comebacks.clear();
}


bool Duel::ChooseOption( const vector<string>& args){
	if (AreEqual(args[0], "surrender") ) {
		Surrender();
		return true;
	}
	player_choice = CheckOption(args[0], turn);
	if (player_choice == NULL)
		return false; 
	UpdateDuel();
	return true;
}


void Duel::PrintRemainingAttacks() const{
	cout << "** Available attacks **" << endl;
	for (list<Interaction*>::const_iterator it = attacks.begin(); it != attacks.end(); ++it)
		(*it)->Print();
	cout << endl << "I say:"; 
}
void Duel::PrintPlayerComebacks()const {
	cout << "** Available comebacks **" << endl;
	for (list<Interaction*>::const_iterator it = player_comebacks.begin(); it != player_comebacks.end(); ++it)
		(*it)->Print();
	cout << endl << "I say:";
}
void Duel::Surrender() const {
	cout << "I surrendered the duel!!" << endl;
	player->ExitDuel();
}

void Duel::UpdateDuel(){
	if (turn == OFFENSE)
	{
		player_choice->Say();
		adversary_choice = AdversaryFindComeback();
		if (adversary_choice == NULL)
		{
			cout << adversary->name << " says:" << endl; 
			cout << "So's your mother!" << endl;
			cout << endl << "** I won advantage! **" << endl << endl;
			turn = OFFENSE;
			player_wins++;
		}
		else
		{
			cout << adversary->name << " says: "  << endl;
			adversary_choice->Say(); 
			cout << "** I lost advantage... **" << endl << endl;
			turn = DEFENSE;
			adversary_wins++;
		}
		DeleteAttackOption(player_choice);
		PrepareNextRound();
		return;
	}
	if (turn == DEFENSE)
	{
		player_choice->Say();
		if (CheckCorrectComeback())
		{
			cout << endl << "** You won advantage! **" << endl << endl;
			turn = OFFENSE;
			player_wins++;
		}
		else
		{
			cout << "** You lost advantage! **" << endl << endl;
			turn = DEFENSE;
			adversary_wins++;
		}
		DeleteAttackOption(adversary_choice);
		PrepareNextRound();
		return;
	}
}

Interaction* Duel::CheckOption(const string code, PlayerTurn turn) const
{
	if (turn == OFFENSE)
	{
		for (list<Interaction*>::const_iterator it = attacks.begin(); it != attacks.end(); ++it)
			if (AreEqual((*it)->code, code))
				return *it;
	}
	if (turn == DEFENSE)
	{
		for (list<Interaction*>::const_iterator it = player_comebacks.begin(); it != player_comebacks.end(); ++it)
			if (AreEqual((*it)->code, code))
				return *it;
	}
	return NULL;
}

bool Duel::CheckCorrectComeback() const
{
	for (list<Interaction*>::const_iterator it = player_comebacks.begin(); it != player_comebacks.end(); ++it)
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
	for (list<Interaction*>::const_iterator it = adversary_comebacks.begin(); it != adversary_comebacks.end(); ++it)
		if ((*it)->response_to == player_choice)
			return *it;
	return NULL;
}

void Duel::DeleteAttackOption( Interaction* target)
{
	attacks.remove(target);
	target = NULL;
}

void Duel::PrepareNextRound() {
	if (player_wins == 3)
	{
		cout << endl << "With my last move, I opened a hole in " << adversary->name << "'s defense" << endl;
		cout << "There is simply no way anybody could retaliate from this position!" << endl;
		cout << adversary->name << " surrenders! I've won!!" << endl;
		Win();
		return;
	}
	if (adversary_wins == 3)
	{
		cout << endl << "With " << adversary->name << "'s last move, my defense was broken" << endl;
		cout << "There is no way I can retaliate from this position" << endl;
		Surrender();
		return;
	}
	cout << "***** Next round ***** " << endl;
	if (turn == OFFENSE)
	{
		PrintRemainingAttacks();
	}
	else
	{
		adversary_choice = AdversaryChooseAttack();
		cout << adversary->name << " says: " << endl;
		adversary_choice->Say();
		PrintPlayerComebacks();
	}
}

void Duel::Win() const
{
	adversary->GiveDuelPrize(player);
	adversary->beaten = true;
	player->ExitDuel();
}