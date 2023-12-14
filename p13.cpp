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

vector<string> flip(const vector<string>& data) {
	vector<string> result;
	for (size_t i = 0; i < data[0].size(); ++i) {
		auto& s = result.emplace_back();
		for (size_t j = 0; j < data.size(); ++j) {
			s += data[j][i];
		}
	}
	return result;
}

int64_t findMirror(const vector<string>& data) {
	for (size_t i = 0; i < data.size() - 1; ++i) {
		int j = static_cast<int>(i);
		size_t k = i + 1;
		for (; k < data.size() && j >= 0; --j, ++k) {
			if (data[j] != data[k]) break;
		}
		if (j == -1 || k == data.size()) return i + 1;
	}
	return 0;
};

int64_t findMirror2(const vector<string>& data, int64_t original, int f) {
	for (size_t i = 0; i < data.size() - 1; ++i) {
		if ((i + 1) * f == original) continue;
		int j = static_cast<int>(i);
		size_t k = i + 1;
		for (; k < data.size() && j >= 0; --j, ++k) {
			if (data[j] != data[k]) break;
		}
		if (j == -1 || k == data.size()) return i + 1;
	}
	return 0;
};

void p13p1() {
	std::ifstream is(DATA_PATH + "p13.txt");
	int64_t sum = 0;
	for (string line; std::getline(is, line);) {
		vector<string> data = { line };
		while (std::getline(is, line)) {
			if (line.empty()) break;
			data.emplace_back(line);
		}
		sum += findMirror(data) * 100;
		sum += findMirror(flip(data));
	}
	cout << sum << endl;
}

void p13p2() {
	std::ifstream is(DATA_PATH + "p13.txt");
	auto flipAndTest = [&](vector<string>& data, int64_t original, int f) -> int64_t {
		for (size_t i = 0; i < data.size(); ++i) {
			for (size_t j = 0; j < data[i].size(); ++j) {
				char c = data[i][j];
				data[i][j] = (c == '.' ? '#' : '.');
				auto v = findMirror2(data, original, f) ;
				data[i][j] = c;
				if (v != 0) return v * f;
			}
		}
		return 0;
	};
	int64_t sum = 0;
	for (string line; std::getline(is, line);) {
		vector<string> data = { line };
		while (std::getline(is, line)) {
			if (line.empty()) break;
			data.emplace_back(line);
		}
		auto data2 = flip(data);
		auto original = findMirror(data) * 100 + findMirror(data2);
		sum += flipAndTest(data, original, 100) + flipAndTest(data2, original, 1);
	}
	cout << sum << endl;
}

}

void p13() {
	p13p1();
	p13p2();
}
