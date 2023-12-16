#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <set>

#include "common.h"

using namespace std;

namespace {
enum : int {
	START,
	UP,
	DOWN,
	LEFT,
	RIGHT
} DIRECTION;

int energizesCount(const vector<string>& data, int r, int c, int d) {
	vector<string> visited(data.size(), string(data[0].size(), '.'));
	set<tuple<int, int, int>> added;
	stack<tuple<int, int, int>> s;
	s.emplace(r, c, d);
	auto add = [&](int r, int c, int d) {
		tuple<int, int, int> t{ r, c, d };
		if (added.find(t) == added.end()) {
			added.emplace(t);
			switch (d) {
			case UP: --r; break;
			case DOWN: ++r; break;
			case LEFT: --c; break;
			case RIGHT: ++c; break;
			}
			if (r >= 0 && r < data.size() && c >= 0 && c < data[0].size()) s.emplace(r, c, d);
		}
	};
	while (!s.empty()) {
		auto [r, c, d] = s.top();
		s.pop();
		switch (d) {
		case UP:
			for (; r >= 0; --r) {
				visited[r][c] = '#';
				if (data[r][c] == '-') {
					add(r, c, LEFT);
					add(r, c, RIGHT);
					break;
				}
				else if (data[r][c] == '/') {
					add(r, c, RIGHT);
					break;
				}
				else if (data[r][c] == '\\') {
					add(r, c, LEFT);
					break;
				}
			}
			break;
		case DOWN:
			for (; r < data.size(); ++r) {
				visited[r][c] = '#';
				if (data[r][c] == '-') {
					add(r, c, LEFT);
					add(r, c, RIGHT);
					break;
				}
				else if (data[r][c] == '/') {
					add(r, c, LEFT);
					break;
				}
				else if (data[r][c] == '\\') {
					add(r, c, RIGHT);
					break;
				}
			}
			break;
		case LEFT:
			for (; c >= 0; --c) {
				visited[r][c] = '#';
				if (data[r][c] == '|') {
					add(r, c, UP);
					add(r, c, DOWN);
					break;
				}
				else if (data[r][c] == '/') {
					add(r, c, DOWN);
					break;
				}
				else if (data[r][c] == '\\') {
					add(r, c, UP);
					break;
				}
			}
			break;
		case RIGHT:
			for (; c < data[0].size(); ++c) {
				visited[r][c] = '#';
				if (data[r][c] == '|') {
					add(r, c, UP);
					add(r, c, DOWN);
					break;
				}
				else if (data[r][c] == '/') {
					add(r, c, UP);
					break;
				}
				else if (data[r][c] == '\\') {
					add(r, c, DOWN);
					break;
				}
			}
			break;
		}
	}
	int count = 0;
	for (const auto& s : visited) {
		for (auto c : s) {
			if (c == '#') ++count;
		}
	}
	return count;
}

void p16p1() {
	std::ifstream is(DATA_PATH + "p16.txt");
	vector<string> data;
	for (string line; std::getline(is, line);) {
		data.emplace_back(line);
	}
	cout << energizesCount(data, 0, 0, RIGHT) << endl;
}

void p16p2() {
	std::ifstream is(DATA_PATH + "p16.txt");
	vector<string> data;
	for (string line; std::getline(is, line);) {
		data.emplace_back(line);
	}
	int maxCount = 0;
	for (int r = 0; r < static_cast<int>(data.size()); ++r) {
		maxCount = max(maxCount, energizesCount(data, r, 0, RIGHT));
		maxCount = max(maxCount, energizesCount(data, r, static_cast<int>(data[r].size()) - 1, LEFT));
	}
	for (int c = 0; c < static_cast<int>(data[0].size()); ++c) {
		maxCount = max(maxCount, energizesCount(data, 0, c, DOWN));
		maxCount = max(maxCount, energizesCount(data, static_cast<int>(data.size()) - 1, c, UP));
	}
	cout << maxCount << endl;
}
}

void p16() {
	p16p1();
	p16p2();
}
