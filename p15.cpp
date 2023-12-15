#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>

#include "common.h"

using namespace std;
namespace {
int hash(const string& str) {
	int v = 0;
	for (auto c : str) {
		v += c;
		v *= 17;
		v = v % 256;
	}
	return v;
}

void p15p1() {
	std::ifstream is(DATA_PATH + "p15.txt");
	int sum = 0;
	for (string line; std::getline(is, line);) {
		for (auto& str : splitString(line, ',', false)) {
			sum += hash(str);
		}
	}
	cout << sum << endl;
}

void p15p2() {
	std::ifstream is(DATA_PATH + "p15.txt");
	vector<vector<pair<string, int>>> boxes(256);
	for (string line; std::getline(is, line);) {
		for (auto& str : splitString(line, ',', false)) {
			auto f = str.find('=');
			if (f == string::npos) {
				string label = str.substr(0, str.size() - 1);
				auto& box = boxes[hash(label)];
				for (auto it = box.begin(); it != box.end(); ++it) {
					if (it->first == label) {
						box.erase(it);
						break;
					}
				}
			}
			else {
				string label = str.substr(0, f);
				int focal = stoi(str.substr(f + 1));
				auto& box = boxes[hash(str.substr(0, f))];
				auto it = box.begin();
				for (; it != box.end(); ++it) {
					if (it->first == label) {
						it->second = focal;
						break;
					}
				}
				if (it == box.end()) box.emplace_back(label, focal);
			}
		}
	}
	size_t sum = 0;
	for (size_t i = 0; i < boxes.size(); ++i) {
		for (size_t j = 0; j < boxes[i].size(); ++j) {
			sum += (i + 1) * (j + 1) * boxes[i][j].second;
		}
	}
	cout << sum << endl;
}

}

void p15() {
	p15p1();
	p15p2();
}
