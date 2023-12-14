#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>

#include "common.h"

using namespace std;

void p4() {
	{
		std::ifstream is(DATA_PATH + "p4.txt");

		int sum = 0;
		for (std::string line; std::getline(is, line);) {
			set<int> winning;
			set<int> numbers;
			auto numsStrs = splitString(line.substr(line.find(':') + 1), '|', false);
			for (auto s : splitString(numsStrs[0], ' ', false)) winning.insert(stoi(s));
			for (auto s : splitString(numsStrs[1], ' ', false)) numbers.insert(stoi(s));
			int count = 0;
			for (auto v : numbers) {
				if (winning.find(v) != winning.end()) ++count;
			}
			if (count != 0) sum += 1ll << (count - 1);
		}
		cout << sum << endl;
	}
	{
		std::ifstream is(DATA_PATH + "p4.txt");

		int gameNum = 1;
		vector<int> counts(1000, 1);
		for (std::string line; std::getline(is, line); ++gameNum) {
			set<int> winning;
			set<int> numbers;
			auto numsStrs = splitString(line.substr(line.find(':') + 1), '|', false);
			for (auto s : splitString(numsStrs[0], ' ', false)) winning.insert(stoi(s));
			for (auto s : splitString(numsStrs[1], ' ', false)) numbers.insert(stoi(s));
			int count = 0;
			for (auto v : numbers) {
				if (winning.find(v) != winning.end()) ++count;
			}
			for (int i = 1; i <= count; ++i) counts[i + gameNum] += counts[gameNum];
		}
		int sum = 0;
		for (int i = 1; i < gameNum; ++i) sum += counts[i];
		cout << sum << endl;
	}
}