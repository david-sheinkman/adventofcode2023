#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <map>

#include "common.h"

using namespace std;

namespace {
struct Rule {
	char c = 0;
	int op = 0;
	int v = 0;
	string target;
};
map<string, vector<Rule>> loadWorkflows(std::ifstream& is) {
	map<string, vector<Rule>> workflows;
	for (string line; std::getline(is, line);) {
		if (line.empty()) break;
		auto s = line.find('{');
		string name = line.substr(0, s);
		auto& rules = workflows[name];
		for (const auto& str : splitString(line.substr(s + 1, line.length() - s - 2), ',', false)) {
			auto& rule = rules.emplace_back();
			auto col = str.find(':');
			if (col == string::npos) {
				rule.target = str;
			}
			else {
				switch (str[0]) {
				case 'x': rule.c = 0; break;
				case 'm': rule.c = 1; break;
				case 'a': rule.c = 2; break;
				case 's': rule.c = 3; break;
				}
				rule.op = str[1] == '<' ? 1 : 2;
				rule.v = stoi(str.substr(2, col - 2));
				rule.target = str.substr(col + 1);
			}
		}
	}
	return workflows;
}

void p19p1() {
	std::ifstream is(DATA_PATH + "p19.txt");
	map<string, vector<Rule>> workflows = loadWorkflows(is);
	int sum = 0;
	for (string line; std::getline(is, line);) {
		vector<int> nums(4);
		auto v = splitString(line.substr(1, line.length() - 2), ',', false);
		for (size_t i = 0; i < 4; ++i) nums[i] = stoi(v[i].substr(2));
		string wf = "in";
		while (wf != "A" && wf != "R") {
			for (auto& rule : workflows[wf]) {
				bool t = true;
				if (rule.op == 1) t = nums[rule.c] < rule.v;
				else if (rule.op == 2) t = nums[rule.c] > rule.v;
				if (t) {
					wf = rule.target;
					break;
				}
			}
		}
		if (wf == "A") {
			for (auto n : nums) sum += n;
		}
	}
	cout << sum << endl;
}

void p19p2() {
	std::ifstream is(DATA_PATH + "p19.txt");
	map<string, vector<Rule>> workflows = loadWorkflows(is);
	int64_t sum = 0;
	struct Range {
		vector<pair<int64_t, int64_t>> nums;
		string workflow;
		int rule = 0;
	};
	stack<Range> ranges;
	ranges.emplace(vector<pair<int64_t, int64_t>>{ {1, 4000}, { 1, 4000 }, { 1, 4000 }, { 1, 4000 } }, "in", 0);
	while (!ranges.empty()) {
		auto range = ranges.top();
		ranges.pop();

		if (range.workflow == "A") {
			int64_t s = 1;
			for (auto& v : range.nums) s *= v.second - v.first + 1;
			sum += s;
			continue;
		}
		if (range.workflow == "R") {
			continue;
		}
		const auto& rule = workflows[range.workflow][range.rule];
		if (rule.op == 0) {
			ranges.emplace(range.nums, rule.target, 0);
		}
		if (rule.op == 1) {
			if (range.nums[rule.c].second < rule.v) {
				ranges.emplace(range.nums, rule.target, 0);
			}
			else if (range.nums[rule.c].first >= rule.v) {
				ranges.emplace(range.nums, range.workflow, range.rule + 1);
			}
			else {
				auto n1 = range.nums;
				auto n2 = range.nums;
				n1[rule.c].second = rule.v - 1;
				n2[rule.c].first = rule.v;

				ranges.emplace(n1, rule.target, 0);
				ranges.emplace(n2, range.workflow, range.rule + 1);
			}
		}
		else if (rule.op == 2) {
			if (range.nums[rule.c].first > rule.v) {
				ranges.emplace(range.nums, rule.target, 0);
			}
			else if (range.nums[rule.c].second <= rule.v) {
				ranges.emplace(range.nums, range.workflow, range.rule + 1);
			}
			else {
				auto n1 = range.nums;
				auto n2 = range.nums;
				n1[rule.c].first = rule.v + 1;
				n2[rule.c].second = rule.v;

				ranges.emplace(n1, rule.target, 0);
				ranges.emplace(n2, range.workflow, range.rule + 1);
			}
		}
	}
	cout << sum << endl;
}
}

void p19() {
	p19p1();
	p19p2();
}
