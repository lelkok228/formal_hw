#include <iostream>
#include <string>
#include "MaxCommonSuffix.h"

int main() {
	std::string regularExpression, word;
	std::cin >> regularExpression >> word;
	std::cout << solve(regularExpression, word) << '\n';
	return 0;
}