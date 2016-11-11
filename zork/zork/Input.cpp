#include "Input.h"

void GetTokens(const string& line, vector<string>& args)
{
	const char* line_c = line.c_str();
	const int length = line.length();
	int i = 0;

	do {
		while (line_c[i] == ' '  && i < length) { ++i; }
		const int start = i;
		while (line_c[i] != ' ' && i < length)	{ ++i; }
		if ( i > start)
			args.push_back(string(line_c, start, i - start));
		++i;
	} while (i < length);
}

bool AreEqual(const string& token, const char* compare_to) {
	if (token.compare(compare_to) == 0)
		return true;
	else
		return false;
}