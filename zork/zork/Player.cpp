#include "Player.h"

Player::Player( const char* name, const char* description, Room* parent ):Character(name, description, parent){}

Player::~Player(){}

void Player::Look(const vector<string>& args) const {
	if (args.size()> 1)
	{ 
		if (args[1].compare("me") == 0)
		{
			cout << "** " << name << " **" << endl;
			cout << description << endl;
		}
		else
			cout << "look at something command to be implemented" << endl;
	}
	else
		parent->Look();
}

void Player::Go(const vector<string>& args) const {
	cout << "player is going somewhere" << endl;
}