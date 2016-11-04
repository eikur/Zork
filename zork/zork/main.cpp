#include <iostream>
#include <string>
#include <vector>

using namespace std;

void GetTokens(const string& line, vector<string>& args)
{
	const char* line_c = line.c_str();
	const int length = line.length();
	int i = 0;

	do {
		const int start = i;
		while(line_c[i] != ' ' && i < length) {
			++i;
		}
		args.push_back(string(line_c, start, i-start));
		++i;
	} while (i < length);
}

int main(int argc, char* argv[])
{
	string player_input;
	vector<string> arguments;

	cout << "Welcome to Zork";
	cout << endl << "> ";

	while (getline(cin, player_input))
	{
		GetTokens(player_input, arguments); 
		//game happens here

		arguments.clear();
		cout << endl << "> ";
	}
	
	cout << "Thanks for playing!" << endl << endl;
	
	return 0;
}