#include "Player.h"

Player::Player( const char* name, const char* description, Room* parent ):Character(name, description, parent){
	type = PLAYER;
}

Player::~Player(){}

void Player::Look(const vector<string>& args) const {
	if (args.size()> 1)
	{ 
		if (AreEqual(args[1],"me"))
		{
			cout << "** " << name << " **" << endl;
			cout << description << endl;
		}
		else
			cout << "I understood up to the look part" << endl;
	}
	else
		parent->Look();
}

void Player::Go(const vector<string>& args) const {
	cout << "player is going somewhere" << endl;
}