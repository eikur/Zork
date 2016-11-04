#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
	string player_input;

	cout << "Welcome to Zork" << endl;
	cout << "> ";

	while (getline(cin, player_input))
	{
		cout << "echo: " << player_input << endl;
		cout << "> ";
	}
	
	cout << "Thanks for playing!" << endl << endl;
	
	return 0;
}