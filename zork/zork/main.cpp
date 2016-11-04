#include <iostream>
#include <string>
#include <vector>

using namespace std;

void GetArguments(const string& line, vector<string>& args)
{
	cout << line << endl;
	

}

int main(int argc, char* argv[])
{
	string playerInput;
	
	vector<string> arguments;

	cout << "Welcome to Zork";
	cout << endl << "> ";

	while (getline(cin, playerInput))
	{
		/*if (playerInput.length() != 0)
		{
			cout << "**" << endl;
		}
		else {
			cout << "Remain silent, ok" << endl;
		}
		cout << endl << "> ";
		*/
		GetArguments(playerInput, arguments); 
		cout << endl << "> ";

	}
	
	cout << "Thanks for playing!" << endl << endl;
	
	return 0;
}