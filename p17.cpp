#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>

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


struct Pos {
	int cost;
	int r;
	int c;
	int d;
	int dc;
};

bool operator<(const Pos& lhs, const Pos& rhs) {
	return lhs.cost > rhs.cost;
}

int solve(const vector<string>& data, int MIN_DIR, int MAX_DIR) {
	vector<vector<vector<vector<bool>>>> visited(data.size(), vector<vector<vector<bool>>>(data[0].size(), vector<vector<bool>>(5, vector<bool>(MAX_DIR + 2, false))));
	priority_queue<Pos> q;
	q.emplace(0, 0, 0, 0);
	while (!q.empty()) {
		auto pos = q.top();
		q.pop();

		if (pos.r == data.size() - 1 && pos.c == data[0].size() - 1) {
			return pos.cost;
		}
		auto addPos = [&](int nr, int nc, int nd, int ndc) {
			if (!visited[nr][nc][nd][ndc] && ndc <= MAX_DIR) {
				visited[nr][nc][nd][ndc] = true;
				q.emplace(pos.cost + (data[nr][nc] - '0'), nr, nc, nd, ndc);
			}
			};
		auto addPos2 = [&](int cost, int nr, int nc, int nd, int ndc) {
			if (!visited[nr][nc][nd][ndc]) {
				visited[nr][nc][nd][ndc] = true;
				q.emplace(cost, nr, nc, nd, ndc);
			}
			};
		if (pos.r > 0 && pos.d == UP) {
			addPos(pos.r - 1, pos.c, pos.d, pos.dc + 1);
		}
		else if (pos.r >= MIN_DIR && pos.d != DOWN) {
			int cost = pos.cost;
			for (int i = 1; i <= MIN_DIR; i++) cost += (data[pos.r - i][pos.c] - '0');
			addPos2(cost, pos.r - MIN_DIR, pos.c, UP, MIN_DIR);
		}

		if (pos.c > 0 && pos.d == LEFT) {
			addPos(pos.r, pos.c - 1, pos.d, pos.dc + 1);
		}
		else if (pos.c >= MIN_DIR && pos.d != RIGHT) {
			int cost = pos.cost;
			for (int i = 1; i <= MIN_DIR; i++) cost += (data[pos.r][pos.c - i] - '0');
			addPos2(cost, pos.r, pos.c - MIN_DIR, LEFT, MIN_DIR);
		}

		if (pos.r < (data.size() - 1) && pos.d == DOWN) {
			addPos(pos.r + 1, pos.c, pos.d, pos.dc + 1);
		}
		else if (pos.r <= (data.size() - 1 - MIN_DIR) && pos.d != UP) {
			int cost = pos.cost;
			for (int i = 1; i <= MIN_DIR; i++) cost += (data[pos.r + i][pos.c] - '0');
			addPos2(cost, pos.r + MIN_DIR, pos.c, DOWN, MIN_DIR);
		}

		if (pos.c < (data[0].size() - 1) && pos.d == RIGHT) {
			addPos(pos.r, pos.c + 1, pos.d, pos.dc + 1);
		}
		else if (pos.c <= (data[0].size() - 1 - MIN_DIR) && pos.d != LEFT) {
			int cost = pos.cost;
			for (int i = 1; i <= MIN_DIR; i++) cost += (data[pos.r][pos.c + i] - '0');
			addPos2(cost, pos.r, pos.c + MIN_DIR, RIGHT, MIN_DIR);
		}
	}
	return 0;
}


void p17p1() {
	vector<string> data;
	std::ifstream is(DATA_PATH + "p17.txt");
	for (string line; std::getline(is, line);) {
		data.emplace_back(line);
	}
	cout << solve(data, 1, 3) << endl;
}

void p17p2() {
	vector<string> data;
	std::ifstream is(DATA_PATH + "p17.txt");
	for (string line; std::getline(is, line);) {
		data.emplace_back(line);
	}
	cout << solve(data, 4, 10) << endl;
}
}

void p17() {
	p17p1();
	p17p2();
}
