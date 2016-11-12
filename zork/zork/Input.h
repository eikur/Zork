#ifndef INPUT_H
#define INPUT_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

void GetTokens(const string& line, vector<string>& args);

bool AreEqual(const string& token, const char* compare_to);
bool AreEqual(const string& token, const string& compare_to);

#endif // INPUT_H
