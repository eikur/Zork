#include <iostream>
#include <string>
#include <vector>

#include "Input.h"
#include "World.h"

using namespace std;

int main()
{
	string player_input;
	vector<string> arguments;
	
	cout << "**********************************************************************" << endl;
	cout << "***                         Welcome to Zork                        ***" << endl;
	cout << "**********************************************************************" << endl;
	cout << "You are a wannabee adventurer / treasure hunter with a sharp tongue" << endl;
	cout << "This is your first real-world approach to start shaping your legend!" << endl;
	cout << "Stories talk about a rare gem that might be found in the surroundings." << endl;
	cout << "Have luck my friend!" << endl;
	cout << endl << "> ";

	World game_world;

	while (getline(cin, player_input))
	{
		GetTokens(player_input, arguments);
		if (arguments.size() == 0)
			cout << "Please enter a command" << endl;
		else if (AreEqual(arguments[0],"quit")) 
			break;
		else
			game_world.GetPlayerCommands(arguments);
		
		arguments.clear();
		player_input.clear();
		cout << endl << "> ";
	}
	
	cout << "Thanks for playing!" << endl << endl;
	
	return 0;
}