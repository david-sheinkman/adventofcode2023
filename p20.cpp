#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <map>

#include "common.h"

using namespace std;

namespace {
enum {
	BASIC,
	BROADCAST,
	FLIPFLOP,
	CONJUCTION
};
enum {
	FLIP_OFF,
	FLIP_ON
};
enum {
	LOW,
	HIGH
};
struct Module {
	string name;
	int type = BASIC;
	vector<string> destinations;
	map<string, int> inputs;
	int onoff = FLIP_OFF;

	bool operator<(const Module& rhs) const {
		return name < rhs.name;
	}
};

map<string, Module> readModules(const string& filename) {
	std::ifstream is(filename);
	map<string, Module> modules;
	for (string line; std::getline(is, line);) {
		auto dash = line.find('-');
		auto name = line.substr(0, dash - 1);
		int type = BASIC;
		if (name[0] == '%') {
			type = FLIPFLOP;
			name = name.substr(1);
		}
		else if (name[0] == '&') {
			type = CONJUCTION;
			name = name.substr(1);
		}
		else {
			type = BROADCAST;
		}
		auto& m = modules[name];
		m.name = name;
		m.type = type;
		for (auto& s : splitString(line.substr(dash + 2), ',', false)) {
			if (s[0] == ' ') m.destinations.emplace_back(s.substr(1));
			else m.destinations.emplace_back(s);
			modules[m.destinations.back()].inputs[name] = LOW;
		}
	}
	return modules;
}


void p20p1() {
	map<string, Module> modules = readModules(DATA_PATH + "p20.txt");
	int64_t lowCount = 0;
	int64_t highCount = 0;
	for (int push = 0; push < 1000; ++push) {
		queue<tuple<string, string, int>> q;
		q.emplace("button", "broadcaster", LOW);
		while (!q.empty()) {
			auto [from, to, pulse] = q.front();
			q.pop();
			if (pulse == LOW) ++lowCount;
			else ++highCount;
			auto& m = modules[to];
			bool send = true;
			if (m.type == FLIPFLOP) {
				if (pulse == LOW) {
					if (m.onoff == FLIP_ON) {
						m.onoff = FLIP_OFF;
						pulse = LOW;
					}
					else {
						m.onoff = FLIP_ON;
						pulse = HIGH;
					}
				}
				else send = false;
			}
			else if (m.type == CONJUCTION) {
				m.inputs[from] = pulse;
				bool allHigh = true;
				for (const auto& [in, p] : m.inputs) {
					if (p == LOW) {
						allHigh = false;
						break;
					}
				}
				pulse = allHigh ? LOW : HIGH;
			}
			if (send) {
				for (auto& d : m.destinations) {
					q.emplace(to, d, pulse);
				}
			}
		}
	}
	int64_t product = lowCount * highCount;
	cout << product << endl;
}

void p20p2() {	
	struct S20p2 {
		map<string, Module> modules;
		void findDepends(const string& on, set<string>& depends) {
			auto& m = modules[on];
			for (auto& i : m.inputs) {
				auto it = depends.insert(i.first);
				if (it.second) findDepends(i.first, depends);
			}
		}
		void runPush() {
			queue<tuple<string, string, int>> q;
			q.emplace("button", "broadcaster", LOW);
			while (!q.empty()) {
				auto [from, to, pulse] = q.front();
				q.pop();
				auto& m = modules[to];
				bool send = true;
				if (m.type == FLIPFLOP) {
					if (pulse == LOW) {
						if (m.onoff == FLIP_ON) {
							m.onoff = FLIP_OFF;
							pulse = LOW;
						}
						else {
							m.onoff = FLIP_ON;
							pulse = HIGH;
						}
					}
					else send = false;
				}
				else if (m.type == CONJUCTION) {
					m.inputs[from] = pulse;
					bool allHigh = true;
					for (const auto& [in, p] : m.inputs) {
						if (p == LOW) {
							allHigh = false;
							break;
						}
					}
					pulse = allHigh ? LOW : HIGH;
				}
				if (send) {
					for (auto& d : m.destinations) {
						q.emplace(to, d, pulse);
					}
				}
			}
		}
		void run() {
			map<string, set<string>> dependsOn;
			map<string, int> mem;
			map<string, int> pattern;
			modules = readModules(DATA_PATH + "p20.txt");
			for (auto& m : modules) findDepends(m.first, dependsOn[m.first]);
			/*queue<pair<string, int>> q;
			q.emplace("rx", 0);
			set<string> seen;
			while (!q.empty()) {
				auto [m, d] = q.front();
				q.pop();
				cout << m << ", " << modules[m].type << ", " << d << " :";
				for (auto s : modules[m].inputs) {
					cout << s.first << ", ";
					if(seen.find(s.first) == seen.end()) q.emplace(s.first, d + 1);
					seen.insert(s.first);
				}
				cout << endl;
			}*/

			const vector<string> nodesToSearch = { "sl", "rr", "pq", "jz" };
			bool found = false;
			for (int push = 0; !found; ++push) {
				runPush();
				for (auto& name : nodesToSearch) {
					auto& m = modules[name];
					string s = name + ":";
					for (auto& d : dependsOn[name]) {
						auto& dm = modules[d];
						if (dm.type == FLIPFLOP) {
							s += dm.onoff == FLIP_ON ? "1" : "0";
						}
						else if (dm.type == CONJUCTION) {
							for (const auto& [in, p] : dm.inputs) s += p == LOW ? "0" : "1";
						}
					}
					auto it = mem.find(s);
					if (it != mem.end()) {
						auto it2 = pattern.find(name);
						if (it2 == pattern.end()) {
							pattern[name] = push - it->second;
							if (pattern.size() == 4) found = true;
						}
					}
					else mem[s] = push;
				}
			}
			int64_t product = 1;
			for (auto& [m, p] : pattern) product *= p;
			cout << product << endl;
		}
	};
	S20p2().run();
}
}

void p20() {
	p20p1();
	p20p2();
}
 