#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <set>

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

void p23p1() {
	struct S23p1 {
		vector<string> data;
		int longest = 0;

		bool check(size_t r, size_t c, char ch) {
			return data[r][c] == '.' || data[r][c] == ch;
		}

		void run(size_t r, size_t c, int d, int l) {
			if (r == data.size() - 1 && c == data[0].size() - 2) {
				longest = max(l, longest);
				return;
			}
			data[r][c] += 5;
			++l;
			if (d != DOWN && check(r - 1, c, '^')) run(r - 1, c, UP, l);
			if (d != RIGHT && check(r, c - 1, '<')) run(r, c - 1, LEFT, l);
			if (d != UP && check(r + 1, c, 'v')) run(r + 1, c, DOWN, l);
			if (d != LEFT && check(r, c + 1, '>')) run(r, c + 1, RIGHT, l);
			data[r][c] -= 5;
		}

		void run() {
			std::ifstream is(DATA_PATH + "p23sample.txt");
			for (string line; std::getline(is, line);) {
				data.emplace_back(line);
			}
			run(0, 1, DOWN, 0);
			cout << longest << endl;
		}
	};
	S23p1().run();
}

void p23p2() {
	struct Vertex;
	struct Node {
		size_t r = 0;
		size_t c = 0;
		vector<Vertex*> vs;
		bool visited = false;
	};
	struct Vertex {
		int w;
		Node* n1;
		Node* n2;
	};
	struct S23p2 {
		vector<string> data;
		map<pair<size_t, size_t>, Node> nodes;
		vector<Vertex> vertexes;
		int longest = 0;

		bool check(size_t r, size_t c) {
			return data[r][c] == '.';
		}

		void build(size_t r, size_t c, int d, Vertex& cv) {
			while (true) {
				if (r == data.size() - 1 && c == data[0].size() - 2) {
					auto p = nodes.emplace(make_pair(r, c), Node{ r, c });
					auto* n = &p.first->second;
					cv.n2 = n;
					return;
				}
				int dc = 0;
				if (check(r - 1, c)) dc++;
				if (check(r, c - 1)) dc++;
				if (check(r + 1, c)) dc++;
				if (check(r, c + 1)) dc++;

				if (dc == 0) cv.n2 = nullptr;
				else if (dc > 2) {
					print(r, c);
					auto p = nodes.emplace(make_pair(r, c), Node{ r, c });
					auto* n = &p.first->second;
					cv.n2 = n;
					if (p.second) {
						n->vs.emplace_back(&cv);
						if (d != DOWN && check(r - 1, c)) {
							n->vs.emplace_back(&vertexes.emplace_back(0, n));
							build(r - 1, c, UP, vertexes.back());
						}
						if (d != RIGHT && check(r, c - 1)) {
							n->vs.emplace_back(&vertexes.emplace_back(0, n));
							build(r, c - 1, LEFT, vertexes.back());
						}
						if (d != UP && check(r + 1, c)) {
							n->vs.emplace_back(&vertexes.emplace_back(0, n));
							build(r + 1, c, DOWN, vertexes.back());
						}
						if (d != LEFT && check(r, c + 1)) {
							n->vs.emplace_back(&vertexes.emplace_back(0, n));
							build(r, c + 1, RIGHT, vertexes.back());
						}
					}
					return;
				}
				else {
					cv.w++;
					if (d != DOWN && check(r - 1, c)) {
						--r;
						d = UP;
					}
					else if (d != RIGHT && check(r, c - 1)) {
						--c;
						d = LEFT;
					}
					else if (d != UP && check(r + 1, c)) {
						++r;
						d = DOWN;
					}
					else if (d != LEFT && check(r, c + 1)) {
						++c;
						d = RIGHT;
					}
				}
			}
		}
		void findLongest(Node& n, int l) {
			if (n.r == data.size() - 1 && n.c == data[0].size() - 2) {
				if (l > longest) longest = l;
				return;
			}
			for (auto& v : n.vs) {
				auto* nn = v->n1 == &n ? v->n2 : v->n1;
				if(nn == nullptr || nn->visited) continue;
				nn->visited = true;
				findLongest(*nn, l + v->w + 1);
				nn->visited = false;
			}
		}

		void run() {
			std::ifstream is(DATA_PATH + "p23.txt");
			for (string line; std::getline(is, line);) {
				for (auto& c : line) if (c == '<' || c == 'v' || c == '^' || c == '>') c = '.';
				data.emplace_back(line);
			}
			data[0][1] = '#';
			auto* n = &nodes[make_pair<size_t, size_t>(0, 1)];
			vertexes.reserve(1000);
			vertexes.emplace_back(0, n);
			n->vs.emplace_back(&vertexes.back());
			build(1, 1, DOWN, vertexes.back());
			findLongest(nodes[make_pair<size_t, size_t>(0, 1)], 0);
			cout << longest << endl;
		}
	};
	S23p2().run();
}

}

void p23() {
	p23p1();
	p23p2();
}
