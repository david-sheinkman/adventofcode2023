#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>

#include "common.h"

using namespace std;

void p9() {
	{
		int sum = 0;
		std::ifstream is(DATA_PATH + "p9.txt");
		for (string line; std::getline(is, line);) {
			vector<int> nums;
			for (auto v : splitString(line, ' ', false)) nums.emplace_back(stoi(v));
			for (int i = static_cast<int>(nums.size()) - 1; i > 0; --i) {
				for (int j = 0; j < i; ++j) {
					nums[j] = nums[j + 1] - nums[j];
				}
			}
			for (auto n : nums) sum += n;
		}
		cout << sum << endl;
	}
	{
		int sum = 0;
		std::ifstream is(DATA_PATH + "p9.txt");
		for (string line; std::getline(is, line);) {
			vector<int> nums;
			for (auto v : splitString(line, ' ', false)) nums.emplace_back(stoi(v));
			for (int i = 1; i < nums.size(); ++i) {
				int pv = nums[i - 1];
				for (int j = i; j < nums.size(); ++j) {
					int t = pv;
					pv = nums[j];
					nums[j] = nums[j] - t;
				}
			}
			int pv = 0;
			for (int i = static_cast<int>(nums.size()) - 1; i >= 0; --i) {
				pv = nums[i] - pv;
			}
			sum += pv;
		}
		cout << sum << endl;
	}
}
