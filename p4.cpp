#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>

#include "common.h"

using namespace std;

void p4() {
	{
		std::ifstream is(DATA_PATH + "p4.txt");

		int64_t sum = 0;
		for (std::string line; std::getline(is, line);) {
			set<int64_t> winning;
			set<int64_t> numbers;
			{
				auto colon = line.find(':') + 1;
				string str = line.substr(colon, line.find('|') - colon);
				stringstream ss(str);
				int64_t v;
				ss >> v;
				while (ss.tellp() == 0) {
					winning.insert(v);
					ss >> v;
				}
			}
			{
				string str = line.substr(line.find('|') + 1);
				stringstream ss(str);
				int64_t v;
				ss >> v;
				while (ss.tellp() == 0) {
					numbers.insert(v);
					ss >> v;
				}
			}
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

		int64_t sum = 0;
		int gameNum = 1;
		vector<int> counts(1000, 1);
		for (std::string line; std::getline(is, line); ++gameNum) {
			set<int> winning;
			set<int> numbers;
			{
				auto colon = line.find(':') + 1;
				string str = line.substr(colon, line.find('|') - colon);
				stringstream ss(str);
				int v;
				ss >> v;
				while (ss.tellp() == 0) {
					winning.insert(v);
					ss >> v;
				}
			}
			{
				string str = line.substr(line.find('|') + 1);
				stringstream ss(str);
				int64_t v;
				ss >> v;
				while (ss.tellp() == 0) {
					numbers.insert(v);
					ss >> v;
				}
			}
			int count = 0;
			for (auto v : numbers) {
				if (winning.find(v) != winning.end()) ++count;
			}
			for (int i = 1; i <= count; ++i) counts[i + gameNum] += counts[gameNum];
		}
		for (int i = 1; i < gameNum; ++i) sum += counts[i];
		cout << sum << endl;
	}
}