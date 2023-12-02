#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "common.h"

using namespace std;


void p1() {
	{
		std::ifstream is(DATA_PATH + "p1.txt");

		int sum = 0;
		for (std::string str; std::getline(is, str);) {
			vector<int> digits;
			for (auto c : str) {
				if (isdigit(c)) digits.emplace_back(c - '0');
			}
			sum += digits.front() * 10 + digits.back();
		}
		cout << sum << endl;
	}
	{
		std::ifstream is(DATA_PATH + "p1.txt");
		std::string digitNames[] = { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };

		int sum = 0;
		for (std::string str; std::getline(is, str);) {
			vector<int> digits;
			for (size_t i = 0; i < str.size(); ++i) {
				char c = str[i];
				if (isdigit(c)) digits.emplace_back(c - '0');
				else {
					for (size_t j = 0; j < 9; ++j) {
						size_t k = 0;
						for (; k < digitNames[j].size() && i + k < str.size(); ++k) {
							if (str[i + k] != digitNames[j][k]) break;
						}
						if (k == digitNames[j].size()) {
							digits.emplace_back(j + 1);
							break;
						}
					}
				}
			}
			sum += digits.front() * 10 + digits.back();
		}
		cout << sum << endl;
	}
}