#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "common.h"

using namespace std;

namespace {
struct NumMap {
	int64_t dest = 0;
	int64_t start = 0;
	int64_t end = 0;
};
}

void p5() {
	{
		std::ifstream is(DATA_PATH + "p5.txt");
		std::string line;
		std::getline(is, line);
		auto seedStrs = splitString(line.substr(line.find(':') + 1), ' ', false);
		vector<int64_t> nums;
		for (const auto& s : seedStrs) nums.emplace_back(stoll(s));
		std::getline(is, line);
		std::getline(is, line);
		std::vector<NumMap> maps;
		auto logic = [&]() {
			for (auto& num : nums) {
				for (auto& m : maps) {
					if (num >= m.start && num < m.end) {
						num = num - m.start + m.dest;
						break;
					}
				}
			}
			maps.clear();
		};
		for (std::string line; std::getline(is, line);) {
			if (line.empty()) {
				logic();
				std::getline(is, line);
				continue;
			}
			auto v = splitString(line, ' ', false);
			auto& numMap = maps.emplace_back();
			numMap.dest = stoll(v[0]);
			numMap.start = stoll(v[1]);
			numMap.end = numMap.start + stoll(v[2]);
		}
		logic();
		int64_t minVal = nums[0];
		for (const auto& num : nums) minVal = min(minVal, num);
		cout << minVal << endl;
	}
	{
		std::ifstream is(DATA_PATH + "p5.txt");
		std::string line;
		std::getline(is, line);
		auto seedStrs = splitString(line.substr(line.find(':') + 1), ' ', false);
		vector<std::pair<int64_t, int64_t>> ranges;
		for (size_t i = 0; i < seedStrs.size(); i += 2) {
			ranges.emplace_back(stoll(seedStrs[i]), stoll(seedStrs[i]) + stoll(seedStrs[i + 1]));
		}
		std::getline(is, line);
		std::getline(is, line);
		std::vector<NumMap> maps;
		auto logic = [&]() {
			vector<std::pair<int64_t, int64_t>> newRanges;
			for (size_t i = 0; i < ranges.size(); ++i){
				auto [s, e] = ranges[i];
				bool foundMap = false;
				for (auto& m : maps) {
					if (s >= m.start && e <= m.end) {
						foundMap = true;
						int64_t ns = s - m.start + m.dest;
						newRanges.emplace_back(ns, ns + (e - s));
					}
					else if (s == m.start) {
						foundMap = true;
						if (e <= m.end) {
							newRanges.emplace_back(m.dest, m.dest + (e - s));
						}
						else {
							newRanges.emplace_back(m.dest, m.dest + (m.end - m.start));
							ranges.emplace_back(m.end, e);
						}
					}
					else if (s < m.start && e > m.end) {
						foundMap = true;
						ranges.emplace_back(s, m.start);
						ranges.emplace_back(m.end, e);
						newRanges.emplace_back(m.dest, m.dest + (m.end - m.start));
					}
					else if (s < m.start && e > m.start) {
						foundMap = true;
						ranges.emplace_back(s, m.start);
						newRanges.emplace_back(m.dest, m.dest + (e - m.start));
					}
					else if (s < m.end && e > m.end) {
						foundMap = true;
						int64_t ns = s - m.start + m.dest;
						newRanges.emplace_back(ns, ns + (m.end - s));
						ranges.emplace_back(m.end, e);
					}
					if (!newRanges.empty() && newRanges.back().first == 0) {
						int a = 0;
					}
					if (foundMap) break;
				}
				if (!foundMap) newRanges.emplace_back(s, e);
			}
			ranges = std::move(newRanges);
			maps.clear();
		};
		for (std::string line; std::getline(is, line);) {
			if (line.empty()) {
				logic();
				std::getline(is, line);
				continue;
			}
			auto v = splitString(line, ' ', false);
			auto& numMap = maps.emplace_back();
			numMap.dest = stoll(v[0]);
			numMap.start = stoll(v[1]);
			numMap.end = numMap.start + stoll(v[2]);
		}
		logic();
		int64_t minVal = ranges[0].first;
		for (const auto& [s, e] : ranges) minVal = min(minVal, s);
		cout << minVal << endl;
	}
}