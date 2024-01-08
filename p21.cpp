#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <map>

#include "common.h"

using namespace std;

namespace {
vector<vector<int64_t>> minDistanceFunc(const vector<string>& data, size_t sr, size_t sc) {
	vector<vector<int64_t>> minDistances(data.size(), vector<int64_t>(data[0].size(), -1));
	queue<tuple<size_t, size_t, int64_t>> q;
	q.emplace(sr, sc, 0);
	minDistances[sr][sc] = 0;
	while (!q.empty()) {
		auto [r, c, d] = q.front();
		q.pop();
		++d;
		auto addPoint = [&](size_t r, size_t c) {
			if (data[r][c] == '.' && minDistances[r][c] == -1) {
				minDistances[r][c] = d;
				q.emplace(r, c, d);
			}
			};
		if (r != 0) addPoint(r - 1, c);
		if (c != 0) addPoint(r, c - 1);
		if (r != data.size() - 1) addPoint(r + 1, c);
		if (c != data[0].size() - 1) addPoint(r, c + 1);
	}
	return minDistances;
}

void p21p1() {
	struct S21p1 {
		vector<string> data;
		vector<vector<map<int, bool>>> mem;

		bool canReach(size_t r, size_t c, int s) {
			if (s == 0) return data[r][c] == 'S';
			if (data[r][c] == '#') return false;
			auto& m = mem[r][c];
			auto it = m.find(s);
			if (it != m.end()) return it->second;
			--s;
			bool reached = false;
			if (r != 0 && canReach(r - 1, c, s)) reached = true;
			if (!reached && c != 0 && canReach(r, c - 1, s)) reached = true;
			if (!reached && r != data.size() - 1 && canReach(r + 1, c, s)) reached = true;
			if (!reached && c != data[0].size() - 1 && canReach(r, c + 1, s)) reached = true;
			++s;
			m[s] = reached;
			return reached;
		}

		void run() {
			std::ifstream is(DATA_PATH + "p21.txt");
			for (string line; std::getline(is, line);) {
				data.emplace_back(line);
			}
			mem.resize(data.size(), vector<map<int, bool>>(data[0].size()));
			int sum = 0;
			for (size_t r = 0; r < data.size(); ++r) {
				for (size_t c = 0; c < data[0].size(); ++c) {
					sum += canReach(r, c, 64);
				}
			}
			cout << sum << endl;
		}
	};
	S21p1().run();
}

void p21p2() {
	vector<string> data;
	std::ifstream is(DATA_PATH + "p21.txt");
	for (string line; std::getline(is, line);) {
		data.emplace_back(line);
	}
	size_t sr = 0;
	size_t sc = 0;
	for (size_t r = 0; r < data.size(); ++r) {
		for (size_t c = 0; c < data[0].size(); ++c) {
			if (data[r][c] == 'S') {
				data[r][c] = '.';
				sr = r;
				sc = c;
			}
		}
	}

	int64_t H = data.size();
	int64_t W = data[0].size();
	auto minDistances = minDistanceFunc(data, sr, sc);

	int64_t dotsCount = 0;
	for (size_t r = 0; r < data.size(); ++r) {
		for (size_t c = 0; c < data[0].size(); ++c) dotsCount += minDistances[r][c] != -1;
	}

	int64_t sum = 0;
	const int64_t DISTANCE = 26501365;
	const int64_t DISTANCE_MOD = DISTANCE % 2;
	auto checkDistance = [&](int64_t d) {
		return d <= DISTANCE && (d % 2) == DISTANCE_MOD;
	};
	auto check = [&](const int64_t d, const vector<vector<int64_t>>& minDistances) {
		int64_t sum = 0;
		for (size_t r = 0; r < data.size(); ++r) {
			for (size_t c = 0; c < data[0].size(); ++c) {
				if (minDistances[r][c] == -1) continue;
				if (checkDistance(d + minDistances[r][c])) ++sum;
			}
		}
		return sum;
	};
	sum += check(0, minDistances);
	int64_t l = (DISTANCE - 4 * W) / (2 * W);
	int64_t sd = 2 * W * l;
	sum += dotsCount * l * 4;
	auto stright = [&](int64_t d, const vector<vector<int64_t>>& minDistances) {
		for (d += sd + 1; d <= DISTANCE; d += W) sum += check(d, minDistances);
	};
	// LEFT
	stright(minDistances[sr][0], minDistanceFunc(data, sr, W - 1));
	// RIGHT
	stright(minDistances[sr][W - 1], minDistanceFunc(data, sr, 0));
	// UP
	stright(minDistances[0][sc], minDistanceFunc(data, 0, sc));
	// DOWN
	stright(minDistances[H - 1][sc], minDistanceFunc(data, H - 1, sc));

	auto diag = [&](int64_t d, const vector<vector<int64_t>>& minDistances) {
		d += 2;
		int64_t s = 0;
		for (int64_t d1 = d + W + 2 * W * l; d1 <= DISTANCE; d1 += W) s += 2 * check(d1, minDistances);
		sum += dotsCount * (l * (l + 1)) + check(d, minDistances) * l + s * l;
		for (int64_t d1 = d + 2 * W * l; d1 <= DISTANCE; d1 += 2 * W) sum += check(d1, minDistances);
		for (d += 2 * W * l; d <= DISTANCE; d += 2 * W) {
			for (int64_t d1 = d + W; d1 <= DISTANCE; d1 += W) sum += 2 * check(d1, minDistances);
		}
	};
	diag(minDistances[0][0], minDistanceFunc(data, H - 1, W - 1));
	diag(minDistances[0][W - 1], minDistanceFunc(data, H - 1, 0));
	diag(minDistances[H - 1][0], minDistanceFunc(data, 0, W - 1));
	diag(minDistances[H - 1][W - 1], minDistanceFunc(data, 0, 0));
	cout << sum << endl;
}
}

void p21() {
	p21p1();
	p21p2();
}
