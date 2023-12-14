#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <set>
#include <map>

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
}

void p10() {
	{
		std::ifstream is(DATA_PATH + "p10.txt");
		vector<string> data;
		for (string line; std::getline(is, line);) {
			data.emplace_back(line);
		}

		pair<size_t, size_t> start;
		stack<tuple<size_t, size_t, int, int>> s;
		for (size_t r = 0; r < data.size(); ++r) {
			for (size_t c = 0; c < data[0].size(); ++c) {
				if (data[r][c] == 'S') {
					start = make_pair(r, c);
					s.emplace(r, c, START, 0);
				}
			}
		}
		while (!s.empty()) {
			auto [r, c, direction, d] = s.top();
			s.pop();
			if (d != 0 && r == start.first && c == start.second) {
				cout << d / 2 << endl;
				break;
			};
			/*
			* F-7
			* |.|
			* L-J
			*/
			++d;
			auto check = [&](size_t r, size_t c, const std::string& vals) {
				if (data[r][c] == 'S') return true;
				for (auto v : vals) if (v == data[r][c]) return true;
				return false;
			};
			if (r != 0 && direction != DOWN && check(r, c, "|JL")) {
				if (check(r - 1, c, "|F7")) {
					s.emplace(r - 1, c, UP, d);
				}
			}
			if (r != data.size() - 1 && direction != UP && check(r, c, "|F7")) {
				if (check(r + 1, c, "|JL")) {
					s.emplace(r + 1, c, DOWN, d);
				}
			}
			if (c != 0 && direction != RIGHT && check(r, c, "-7J")) {
				if (check(r, c - 1, "-FL")) {
					s.emplace(r, c - 1, LEFT, d);
				}
			}
			if (c != data[0].size() - 1 && direction != LEFT && check(r, c, "-FL")) {
				if (check(r, c + 1, "-7J")) {
					s.emplace(r, c + 1, RIGHT, d);
				}
			}
		}
	}
	{
		std::ifstream is(DATA_PATH + "p10.txt");
		vector<string> data;
		for (string line; std::getline(is, line);) {
			data.emplace_back(line);
		}

		pair<size_t, size_t> start;
		for (size_t r = 0; r < data.size(); ++r) {
			for (size_t c = 0; c < data[0].size(); ++c) {
				if (data[r][c] == 'S') {
					start = make_pair(r, c);
				}
			}
		}
		string pipes = "-|7FJL";
		for (size_t i = 0; i < pipes.size(); ++i) {
			vector<string> path(data.size(), string(data[0].size(), '.'));
			stack<tuple<size_t, size_t, int, int>> s1;
			data[start.first][start.second] = pipes[i];
			s1.emplace(start.first, start.second, START, 0);
			bool found = false;
			int depth = 0;
			while (!s1.empty()) {
				auto [r, c, direction, d] = s1.top();
				s1.pop();
				if (d != 0 && r == start.first && c == start.second) {
					depth = d;
					found = true;
					break;
				};
				++d;
				auto check = [&](size_t r, size_t c, const std::string& vals) {
					if (data[r][c] == 'S') return true;
					for (auto v : vals) if (v == data[r][c]) return true;
					return false;
				};
				if (r != 0 && direction != DOWN && check(r, c, "|JL")) {
					if (check(r - 1, c, "|F7")) {
						s1.emplace(r - 1, c, UP, d);
						path[r][c] = data[r][c];
					}
				}
				if (r != data.size() - 1 && direction != UP && check(r, c, "|F7")) {
					if (check(r + 1, c, "|JL")) {
						s1.emplace(r + 1, c, DOWN, d);
						path[r][c] = data[r][c];
					}
				}
				if (c != 0 && direction != RIGHT && check(r, c, "-7J")) {
					if (check(r, c - 1, "-FL")) {
						s1.emplace(r, c - 1, LEFT, d);
						path[r][c] = data[r][c];
					}
				}
				if (c != data[0].size() - 1 && direction != LEFT && check(r, c, "-FL")) {
					if (check(r, c + 1, "-7J")) {
						s1.emplace(r, c + 1, RIGHT, d);
						path[r][c] = data[r][c];
					}
				}
			}
			if (!found) continue;
			int count = 0;
			for (auto& s : path) {
				bool in = false;
				for (size_t i = 0; i < s.size(); ++i) {
					switch (s[i]) {
					case '|':
						in = !in;
						break;
					case 'F':
						for (++i; i < s.size() && s[i] == '-'; ++i) {}
						if (s[i] == 'J') in = !in;
						break;
					case 'L':
						for (++i; i < s.size() && s[i] == '-'; ++i) {}
						if (s[i] == '7') in = !in;
						break;
					default:
						if (in) ++count;
						break;
					}
				}
			}
			cout << count << endl;
		}
	}
}
