#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

#include "common.h"

using namespace std;
namespace {
struct Node {
	string id;
	string left;
	string right;
};

int64_t gcd(int64_t a, int64_t b) {
	if (b > a) std::swap(b, a);
	if (b == 0) return 0;
	int64_t r = a % b;
	while (r != 0) {
		a = b;
		b = r;
		r = a % b;
	}
	return b;
}
}

void p8() {
	{
		map<string, Node> nodes;
		std::ifstream is(DATA_PATH + "p8.txt");
		string directions;
		std::getline(is, directions);
		string line;
		std::getline(is, line);
		for (; std::getline(is, line);) {
			string id = line.substr(0, 3);
			nodes.emplace(id, Node{ id, line.substr(7, 3), line.substr(12, 3) });
		}

		Node* current = &nodes["AAA"];
		int steps = 0;
		for (; current->id != "ZZZ"; ++steps) {
			const string& nid = directions[steps % static_cast<int>(directions.size())] == 'L' ? current->left : current->right;
			current = &nodes[nid];
		}

		cout << steps << endl;
	}
	{
		map<string, Node> nodes;
		std::ifstream is(DATA_PATH + "p8.txt");
		string directions;
		std::getline(is, directions);
		string line;
		std::getline(is, line);
		for (; std::getline(is, line);) {
			string id = line.substr(0, 3);
			nodes.emplace(id, Node{ id, line.substr(7, 3), line.substr(12, 3) });
		}

		int64_t lcm = 1;
		for (auto& [k, n] : nodes) {
			if (k[2] != 'A') continue;
			Node* current = &n;
			int64_t steps = 0;
			for (; current->id[2] != 'Z'; ++steps) {
				const string& nid = directions[steps % static_cast<int>(directions.size())] == 'L' ? current->left : current->right;
				current = &nodes[nid];
			}
			lcm = steps * lcm / gcd(lcm, steps);
		}
		cout << lcm << endl;
	}
}
