#include "Input.h"

void GetTokens(const string& line, vector<string>& args)
{
	const char* line_c = line.c_str();
	const int length = line.length();
	int i = 0;

	do {
		const int start = i;
		while (line_c[i] != ' ' && i < length) {
			++i;
		}
		args.push_back(string(line_c, start, i - start));
		++i;
	} while (i < length);
	std::cout << args.capacity() << endl;
}