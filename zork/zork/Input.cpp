#include <algorithm>
#include "Input.h"

void GetTokens(const std::string& line, std::vector<std::string>& args)
{
	const char* line_c = line.c_str();
	const int length = line.length();
	int i = 0;

	do {
		while (line_c[i] == ' '  && i < length) { ++i; }
		const int start = i;
		while (line_c[i] != ' ' && i < length)	{ ++i; }
		if ( i > start)
			args.push_back(std::string(line_c, start, i - start));
		++i;
	} while (i < length);
}

bool AreEqual(const std::string& token, const std::string& input) 
{
	std::string lowerToken = token;
	std::string lowerInput = input;
	std::transform(lowerToken.begin(), lowerToken.end(), lowerToken.begin(), ::tolower);
	std::transform(lowerInput.begin(), lowerInput.end(), lowerInput.begin(), ::tolower);
	return lowerToken == lowerInput;
}