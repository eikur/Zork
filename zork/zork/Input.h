#ifndef INPUT_H
#define INPUT_H

#include <string>
#include <vector>
#include <iostream>

void GetTokens(const std::string& line, std::vector<std::string>& args);

bool AreEqual(const std::string& token, const std::string& compare_to);

#endif // INPUT_H
