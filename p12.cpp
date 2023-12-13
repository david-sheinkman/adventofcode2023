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

void p12p1() {
	struct solution {
		string data;
		vector<int> nums;
		map<size_t, map<size_t, map<int, int64_t>>> mem;

		int64_t recurse(size_t i, size_t j, int count) {
			if (j == nums.size()) {
				for (; i < data.size(); ++i) {
					if (data[i] == '#') return 0;
				}
				return 1;
			}
			else if (i == data.size()) {
				return j == nums.size() - 1 && count == nums[j];
			}
			else if (count > nums[j]) return 0;
			auto it = mem[i][j].find(count);
			if (it != mem[i][j].end()) return it->second;
			char c = data[i];
			++i;
			int64_t result = 0;

			if (c == '.') {
				if (count == 0) result = recurse(i, j, 0);
				else if (count == nums[j]) result = recurse(i, j + 1, 0);
			}
			else if (c == '#') {
				result = recurse(i, j, count + 1);
			}
			else {
				if (count == 0) result = recurse(i, j, 0) + recurse(i, j, 1);
				else if (count == nums[j]) result = recurse(i, j + 1, 0);
				else result = recurse(i, j, count + 1);
			}
			
			mem[i - 1][j][count] = result;
			return result;
		}

		void run() {
			int64_t sum = 0;
			std::ifstream is(DATA_PATH + "p12.txt");
			for (string line; std::getline(is, line);) {
				auto v = splitString(line, ' ', false);
				data = v[0];
				nums.clear();
				mem.clear();
				for (const auto& s : splitString(v[1], ',', false)) nums.emplace_back(stoi(s));

				sum += recurse(0, 0, 0);
			}
			cout << sum << endl;
		}
	};
	solution().run();
}

void p12p2() {
	struct solution {
		string data;
		vector<int> nums;
		map<size_t, map<size_t, map<int, int64_t>>> mem;

		int64_t recurse(size_t i, size_t j, int count) {
			if (j == nums.size()) {
				for (; i < data.size(); ++i) {
					if (data[i] == '#') return 0;
				}
				return 1;
			}
			else if (i == data.size()) {
				return j == nums.size() - 1 && count == nums[j];
			}
			else if (count > nums[j]) return 0;
			auto it = mem[i][j].find(count);
			if (it != mem[i][j].end()) return it->second;
			char c = data[i];
			++i;
			int64_t result = 0;
			if (c == '.') {
				if (count == 0) result = recurse(i, j, 0);
				else if (count == nums[j]) result = recurse(i, j + 1, 0);
			}
			else if (c == '#') {
				result = recurse(i, j, count + 1);
			}
			else {
				if (count == 0) result = recurse(i, j, 0) + recurse(i, j, 1);
				else if (count == nums[j]) result = recurse(i, j + 1, 0);
				else result = recurse(i, j, count + 1);
			}
			;
			mem[--i][j][count] = result;
			return result;
		}

		void run() {
			int64_t sum = 0;
			std::ifstream is(DATA_PATH + "p12.txt");
			for (string line; std::getline(is, line);) {
				auto v = splitString(line, ' ', false);
				data = v[0] + '?' + v[0] + '?' + v[0] + '?' + v[0] + '?' + v[0];
				nums.clear();
				mem.clear();
				for (int i = 0; i < 5; ++i) {
					for (const auto& s : splitString(v[1], ',', false)) nums.emplace_back(stoi(s));
				}
				sum += recurse(0, 0, 0);
			}
			cout << sum << endl;
		}
	};
	solution().run();
}

}

void p12() {
	p12p1();
	p12p2();
}
