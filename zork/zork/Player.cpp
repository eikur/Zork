#include "Player.h"

Player::Player( const char* name, const char* description, Room* parent ):Character(name, description, parent){
	type = PLAYER;
}

Player::~Player(){}

void Player::Look(const vector<string>& args) const {
	if (args.size() > 1)
	{
		if (AreEqual(args[1],"me") || AreEqual(args[1],"player" ) )
		{
			cout << "** " << name << " **" << endl;
			cout << description << endl;
		}
		else
		{
			for (list<Entity*>::const_iterator it = parent->children.begin(); it != parent->children.end(); ++it)
			{
				if (AreEqual((*it)->name, args[1]))
				{
					(*it)->Look();
					return;
				}
			}
			cout << "I can't find what you are looking for" << endl;

		}
	}
	else
		parent->Look();
}

void Player::Go(const vector<string>& args) const {
	if (args.size() == 1)
	{
		cout << "I don't know where to go" << endl;
		return;
	}
}