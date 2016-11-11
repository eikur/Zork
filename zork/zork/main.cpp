#include <iostream>
#include <string>
#include <vector>

#include "Input.h"
#include "World.h"

using namespace std;

int main(int argc, char* argv[])
{
	string player_input;
	vector<string> arguments;
	
	cout << "Welcome to Zork";
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