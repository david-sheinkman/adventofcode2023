#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>

#include "common.h"

using namespace std;

namespace {
struct Brick {
	int x1 = 0;
	int y1 = 0;
	int z1 = 0;
	int x2 = 0;
	int y2 = 0;
	int z2 = 0;
};

void setBrick(vector<vector<vector<char>>>& data, const Brick& b, const char ch) {
	for (int x = b.x1; x <= b.x2; ++x) {
		for (int y = b.y1; y <= b.y2; ++y) {
			for (int z = b.z1; z <= b.z2; ++z) {
				data[x][y][z] = ch;
			}
		}
	}
}
bool testBrick(const vector<vector<vector<char>>>& data, const Brick& b) {
	for (int x = b.x1; x <= b.x2; ++x) {
		for (int y = b.y1; y <= b.y2; ++y) {
			for (int z = b.z1; z <= b.z2; ++z) {
				if (data[x][y][z] != '.') return false;
			}
		}
	}
	return true;
}

void loadBricksAndData(const string& path, vector<Brick>& bricks, vector<vector<vector<char>>>& data) {
	std::ifstream is(path);
	int maxX = 0;
	int maxY = 0;
	int maxZ = 0;
	for (string line; std::getline(is, line);) {
		auto v = splitString(line, '~');
		auto v1 = splitString(v[0], ',');
		auto v2 = splitString(v[1], ',');
		auto& b = bricks.emplace_back(stoi(v1[0]), stoi(v1[1]), stoi(v1[2]), stoi(v2[0]), stoi(v2[1]), stoi(v2[2]));
		maxX = max(maxX, b.x2);
		maxY = max(maxY, b.y2);
		maxZ = max(maxZ, b.z2);
	}
	data = vector<vector<vector<char>>>(maxX + 1, vector<vector<char>>(maxY + 1, vector<char>(maxZ + 1, '.')));
	for (const auto& b : bricks) {
		setBrick(data, b, '#');
	}
	for (bool moved = true; moved; ) {
		moved = false;
		for (auto& b : bricks) {
			if (b.z1 <= 1) continue;
			setBrick(data, b, '.');
			b.z1--;
			b.z2--;
			if (testBrick(data, b)) moved = true;
			else {
				b.z1++;
				b.z2++;
			}
			setBrick(data, b, '#');
		}
	}
}

void p22p1() {
	vector<Brick> bricks;
	vector<vector<vector<char>>> data;
	loadBricksAndData(DATA_PATH + "p22.txt", bricks, data);

	int sum = 0;
	for (int i = 0; i < bricks.size(); ++i) {
		setBrick(data, bricks[i], '.');
		bool canMove = false;
		for (int j = 0; j < bricks.size() && !canMove; ++j) {
			if (i == j || bricks[j].z1 <= 1) continue;
			setBrick(data, bricks[j], '.');
			bricks[j].z1--;
			bricks[j].z2--;
			if (testBrick(data, bricks[j])) {
				canMove = true;
			}
			bricks[j].z1++;
			bricks[j].z2++;
			setBrick(data, bricks[j], '#');
		}
		setBrick(data, bricks[i], '#');
		sum += !canMove;
	}
	cout << sum << endl;
}

void p22p2() {
	vector<Brick> bricks;
	vector<vector<vector<char>>> data;
	loadBricksAndData(DATA_PATH + "p22.txt", bricks, data);

	int sum = 0;
	for (int i = 0; i < bricks.size(); ++i) {
		setBrick(data, bricks[i], '.');
		set<int> fell;
		{
			auto tdata = data;
			auto tbricks = bricks;
			for (bool moved = true; moved; ) {
				moved = false;
				for (int j = 0; j < tbricks.size(); ++j) {
					auto& b = tbricks[j];
					if (i == j || b.z1 <= 1) continue;
					if (b.z1 <= 1) continue;
					setBrick(tdata, b, '.');
					b.z1--;
					b.z2--;
					if (testBrick(tdata, b)) {
						fell.insert(j);
						moved = true;
					}
					else {
						b.z1++;
						b.z2++;
					}
					setBrick(tdata, b, '#');
				}
			}
		}
		setBrick(data, bricks[i], '#');
		sum += fell.size();
	}
	cout << sum << endl;
}
}

void p22() {
	p22p1();
	p22p2();
}
