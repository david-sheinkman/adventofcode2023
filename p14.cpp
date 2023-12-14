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
void rollNorth(vector<string>& data) {
	for (size_t r = 1; r < data.size(); ++r) {
		for (size_t c = 0; c < data[r].size(); ++c) {
			if (data[r][c] == 'O') {
				size_t i = r;
				for (; i > 0; --i) {
					if (data[i - 1][c] != '.') break;
				}
				data[r][c] = '.';
				data[i][c] = 'O';
			}
		}
	}
}

void rollWest(vector<string>& data) {
	for (size_t r = 0; r < data.size(); ++r) {
		for (size_t c = 1; c < data[r].size(); ++c) {
			if (data[r][c] == 'O') {
				size_t i = c;
				for (; i > 0; --i) {
					if (data[r][i - 1] != '.') break;
				}
				data[r][c] = '.';
				data[r][i] = 'O';
			}
		}
	}
}

void rollSouth(vector<string>& data) {
	for (int r = static_cast<int>(data.size()) - 2; r >= 0; --r) {
		for (size_t c = 0; c < data[r].size(); ++c) {
			if (data[r][c] == 'O') {
				int i = r;
				for (; i < static_cast<int>(data.size()) - 1; ++i) {
					if (data[i + 1][c] != '.') break;
				}
				data[r][c] = '.';
				data[i][c] = 'O';
			}
		}
	}
}

void rollEast(vector<string>& data) {
	for (size_t r = 0; r < data.size(); ++r) {
		for (int c = static_cast<int>(data[r].size()) - 2; c >= 0; --c) {
			if (data[r][c] == 'O') {
				int i = c;
				for (; i < static_cast<int>(data[r].size()) - 1; ++i) {
					if (data[r][i + 1] != '.') break;
				}
				data[r][c] = '.';
				data[r][i] = 'O';
			}
		}
	}
}

int64_t totalLoad(vector<string>& data) {
	int64_t sum = 0;
	for (size_t r = 0; r < data.size(); ++r) {
		for (size_t c = 0; c < data[r].size(); ++c) {
			if (data[r][c] == 'O') sum += data.size() - r;
		}
	}
	return sum;
}

void p14p1() {
	std::ifstream is(DATA_PATH + "p14.txt");
	vector<string> data;
	for (string line; std::getline(is, line);) {
		data.emplace_back(line);
	}
	rollNorth(data);
	cout << totalLoad(data) << endl;
}

void p14p2() {
	std::ifstream is(DATA_PATH + "p14.txt");
	vector<string> data;
	for (string line; std::getline(is, line);) {
		data.emplace_back(line);
	}
	map<string, int64_t> seen;
	vector<int64_t> weights;
	const int64_t CYCLES = 1000000000;
	for (int64_t i = 0; i < CYCLES; ++i) {
		rollNorth(data);
		rollWest(data);
		rollSouth(data);
		rollEast(data);
		string str;
		for (auto& s : data) str += s;
		if (seen.find(str) != seen.end()) {
			auto s = seen[str];
			print(weights[s + (CYCLES - i - 1) % (i - s)]);
			break;
		}
		seen[str] = i;
		weights.emplace_back(totalLoad(data));
	}
}

}

void p14() {
	p14p1();
	p14p2();
}
