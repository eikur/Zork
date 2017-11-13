#include <iostream>
#include <string>
#include <vector>

#include "Input.h"
#include "World.h"

namespace
{
	const std::string kCommandQuit = "quit";
	const std::string kCommandExit = "exit";
	const std::string kInputIndicator = " > ";
}

int main()
{
	World gameWorld;
	std::string player_input;
	std::vector<std::string> arguments;
	
	std::cout << "**********************************************************************" << std::endl;
	std::cout << "***                         Welcome to Zork                        ***" << std::endl;
	std::cout << "**********************************************************************" << std::endl;
	std::cout << "You are a wannabee adventurer / treasure hunter with a sharp tongue" << std::endl;
	std::cout << "This is your first real-world approach to start shaping your legend!" << std::endl;
	std::cout << "Stories talk about a rare gem that might be found in the surroundings." << std::endl;
	std::cout << "Have luck my friend!" << std::endl;
	std::cout << std::endl << "Hint: take a look around you!" << std::endl;

	std::cout << std::endl << kInputIndicator;
	while (std::getline(std::cin, player_input))
	{
		GetTokens(player_input, arguments);
		if (arguments.size() == 0)
		{
			std::cout << "Please enter a command" << std::endl;
		}
		else if (AreEqual(arguments[0], kCommandQuit) || AreEqual(arguments[0], kCommandExit))
		{
			break;
		}
		else
		{
			gameWorld.GetPlayerCommands(arguments);
		}
		
		arguments.clear();
		player_input.clear();
		std::cout << std::endl << kInputIndicator;
	}
	
	std::cout << "Thanks for playing!" << std::endl << std::endl;
	
	return 0;
}