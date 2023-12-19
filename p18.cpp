#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

#include "common.h"

using namespace std;

namespace {

void p18p1() {
	std::ifstream is(DATA_PATH + "p18.txt");
	int minr = 0;
	int minc = 0;
	int maxr = 0;
	int maxc = 0;
	int cr = 0;
	int cc = 0;
	char cd = 0;
	vector<tuple<char, int>> instructions;
	for (string line; std::getline(is, line);) {
		auto v = splitString(line, ' ', false);
		int n = stoi(v[1]);
		switch (v[0][0]) {
		case 'L': cc -= n; break;
		case 'R': cc += n; break;
		case 'U': cr -= n; break;
		case 'D': cr += n; break;
		}
		minr = min(minr, cr);
		minc = min(minc, cc);
		maxr = max(maxr, cr);
		maxc = max(maxc, cc);
		instructions.emplace_back(v[0][0], n);
	}
	maxc -= minc;
	maxr -= minr;
	vector<string> data(maxr + 1, string(maxc + 1, '.'));
	auto setc = [&](int r, int c, int ch) {
		data[-minr + r][-minc + c] = ch;
	};
	auto setTurn = [&](int r, int c, int d, int pd) {
		switch (d) {
		case 'L': setc(r, c, pd == 'U' ? '7' : 'J'); break;
		case 'R': setc(r, c, pd == 'U' ? 'F' : 'L'); break;
		case 'U': setc(r, c, pd == 'L' ? 'L' : 'J'); break;
		case 'D': setc(r, c, pd == 'L' ? 'F' : '7'); break;
		}
	};
	for (auto& [d, n] : instructions) {
		setTurn(cr, cc, d, cd);
		switch (d) {
		case 'L':
			for (int i = 1; i < n; ++i) setc(cr, cc - i, '-');
			cc -= n;
			break;
		case 'R':
			for (int i = 1; i < n; ++i) setc(cr, cc + i, '-');
			cc += n;
			break;
		case 'U':
			for (int i = 1; i < n; ++i) setc(cr - i, cc, '|');
			cr -= n;
			break;
		case 'D':
			for (int i = 1; i < n; ++i) setc(cr + i, cc, '|');
			cr += n;
			break;
		}
		cd = d;
	}
	setTurn(cr, cc, get<0>(instructions[0]), cd);
	int count = 0;
	for (auto& s : data) {
		bool in = false;
		for (size_t i = 0; i < s.size(); ++i) {
			switch (s[i]) {
			case '|':
				in = !in;
				++count;
				break;
			case 'F':
				count += 2;
				for (++i; i < s.size() && s[i] == '-'; ++i) ++count;
				if (s[i] == 'J') in = !in;
				break;
			case 'L':
				count += 2;
				for (++i; i < s.size() && s[i] == '-'; ++i) ++count;
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

void p18p2() {
	std::ifstream is(DATA_PATH + "p18.txt");
	int64_t cr = 0;
	int64_t cc = 0;
	set<int64_t> nums;
	vector<tuple<int64_t, int64_t, int64_t>> verticals;
	for (string line; std::getline(is, line);) {
		auto v = splitString(line, ' ', false);
		int64_t n = stoll(v[2].substr(2, 5), nullptr, 16);
		switch (v[2][7]) {
		case '2':
			cc -= n;
			nums.emplace(cr + 1);
			break;
		case '0': 
			cc += n;
			nums.emplace(cr + 1);
			break;
		case '3':
			verticals.emplace_back(cr - n, cr, cc);
			cr -= n;
			nums.emplace(cr);
			break;
		case '1':
			verticals.emplace_back(cr, cr + n, cc);
			cr += n;
			nums.emplace(cr);
			break;
		}
	}
	int64_t count = 0;
	for (auto it = nums.begin(); it != nums.end(); ++it) {
		int64_t n = *it;
		vector<tuple<int64_t, int64_t, int64_t>> vs;
		for (auto [r1, r2, c] : verticals) {
			if (n >= r1 && n <= r2) vs.emplace_back(r1, r2, c);
		}
		sort(vs.begin(), vs.end(), [](const tuple<int64_t, int64_t, int64_t>& lhs, const tuple<int64_t, int64_t, int64_t>& rhs) {
			return get<2>(lhs) < get<2>(rhs);
		});
		int64_t cc = 0;
		bool in = false;
		int64_t s = 0;
		for (int j = 0; j < vs.size(); ++j) {
			auto [r1, r2, c] = vs[j];
			if (n == r1) {
				++j;
				auto [r3, r4, c2] = vs[j];
				if (n == r3) {
					if (!in) cc += c2 - c + 1;
				}
				else {
					if (in) cc += c2 - s + 1;
					else s = c;
					in = !in;
				}
			}
			else if (n == r2) {
				++j;
				auto [r3, r4, c2] = vs[j];
				if (n == r4) {
					if (!in) cc += c2 - c + 1;
				}
				else {
					if (in) cc += c2 - s + 1;
					else s = c;
					in = !in;
				}
			}
			else {
				if (!in) s = c;
				else cc += c - s + 1;
				in = !in;
			}
		}
		auto nextIt = next(it);
		int64_t f = nextIt == nums.end() ? 1 : *nextIt - n;
		count += cc * f;
	}
	cout << count << endl;
}
}

void p18() {
	p18p1();
	p18p2();
}
