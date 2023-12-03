#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

#include "common.h"

using namespace std;

void p3() {
	{
		std::ifstream is(DATA_PATH + "p3.txt");

		vector<string> data;
		int sum = 0;
		for (std::string line; std::getline(is, line);) {
			data.emplace_back(line);
		}
		auto checkAdj = [&](size_t r, size_t c) -> bool {
			return !isdigit(data[r][c]) && data[r][c] != '.';
		};
		for (size_t i = 0; i < data.size(); ++i) {
			int num = 0;
			bool adjacent = false;
			for (size_t j = 0; j < data[i].size(); ++j) {
				if (isdigit(data[i][j])) {
					num = num * 10 + (data[i][j] - '0');
					if (i != 0 && j != 0 && checkAdj(i - 1, j - 1)) adjacent = true;
					if (i != 0 && checkAdj(i - 1, j)) adjacent = true;
					if (i != 0 && j + 1 != data[i].size() && checkAdj(i - 1, j + 1)) adjacent = true;
					if (j != 0 && checkAdj(i, j - 1)) adjacent = true;
					if (j + 1 != data[i].size() && checkAdj(i, j + 1)) adjacent = true;
					if (i + 1 != data.size() && j != 0 && checkAdj(i + 1, j - 1)) adjacent = true;
					if (i + 1 != data.size() && checkAdj(i + 1, j)) adjacent = true;
					if (i + 1 != data.size() && j + 1 != data[i].size() && checkAdj(i + 1, j + 1)) adjacent = true;
				}
				else {
					if (adjacent) sum += num;
					num = 0;
					adjacent = false;
				}
			}
			if (adjacent) sum += num;
		}
		cout << sum << endl;
	}
	{
		std::ifstream is(DATA_PATH + "p3.txt");

		vector<string> data;
		for (std::string line; std::getline(is, line);) {
			data.emplace_back(line);
		}
		map<pair<size_t, size_t>, vector<int>> gears;
		for (size_t i = 0; i < data.size(); ++i) {
			int num = 0;
			bool adjacent = false;
			pair<size_t, size_t> loc;
			auto checkAdj = [&](size_t r, size_t c) -> bool {
				if (data[r][c] == '*') {
					loc = { r, c };
					return true;
				}
				return false;
			};
			for (size_t j = 0; j < data[i].size(); ++j) {
				if (isdigit(data[i][j])) {
					num = num * 10 + (data[i][j] - '0');
					if (i != 0 && j != 0 && checkAdj(i - 1, j - 1)) adjacent = true;
					if (i != 0 && checkAdj(i - 1, j)) adjacent = true;
					if (i != 0 && j + 1 != data[i].size() && checkAdj(i - 1, j + 1)) adjacent = true;
					if (j != 0 && checkAdj(i, j - 1)) adjacent = true;
					if (j + 1 != data[i].size() && checkAdj(i, j + 1)) adjacent = true;
					if (i + 1 != data.size() && j != 0 && checkAdj(i + 1, j - 1)) adjacent = true;
					if (i + 1 != data.size() && checkAdj(i + 1, j)) adjacent = true;
					if (i + 1 != data.size() && j + 1 != data[i].size() && checkAdj(i + 1, j + 1)) adjacent = true;
				}
				else {
					if (adjacent) gears[loc].emplace_back(num);
					num = 0;
					adjacent = false;
				}
			}
			if (adjacent) gears[loc].emplace_back(num);
		}
		int64_t sum = 0;
		for (auto& [k, nums] : gears) {
			if (nums.size() == 2) {
				sum += nums[0] * nums[1];
			}
		}
		cout << sum << endl;
	}
}