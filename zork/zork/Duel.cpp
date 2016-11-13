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


bool Duel::ChooseOption( const string& option) const{
	return false;
}


void Duel::PrintRemainingAttacks() const{
	for (list<Interaction*>::const_iterator it = attacks.begin(); it != attacks.end(); ++it)
		(*it)->Print();
	cout << endl << "I say:"; 
}
void Duel::PrintPlayerComebacks()const {
	for (list<Interaction*>::const_iterator it = player_comebacks.begin(); it != player_comebacks.end(); ++it)
		(*it)->Print();
	cout << endl << "I say:";

}


void Duel::Surrender() {
	cout << "You surrendered the duel!!" << endl;
	player->ExitDuel();
}

