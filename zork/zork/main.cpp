#include <iostream>
#include <string>
#include <vector>

#include "Input.h"

using namespace std;

int main(int argc, char* argv[])
{
	string player_input;
	vector<string> arguments;

	cout << "Welcome to Zork";
	cout << endl << "> ";

	while (getline(cin, player_input))
	{
		GetTokens(player_input, arguments);

		if (arguments.size() == 0)
			cout << "Sorry, couldn't read you at all" << endl;
		arguments.clear();
		player_input.clear();
		cout << endl << "> ";
	}
	
	cout << "Thanks for playing!" << endl << endl;
	
	return 0;
}