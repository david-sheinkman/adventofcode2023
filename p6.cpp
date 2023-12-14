#include <iostream>
#include <fstream>
#include <string>

#include "common.h"

using namespace std;

void p6() {
	{
		std::ifstream is(DATA_PATH + "p6.txt");
		std::string line;
		std::getline(is, line);
		auto timesStr = splitString(line.substr(line.find(':') + 1), ' ', false);
		std::getline(is, line);
		auto distancesStr = splitString(line.substr(line.find(':') + 1), ' ', false);

		int64_t product = 1;
		for (size_t i = 0; i < timesStr.size(); ++i) {
			int64_t t = stoll(timesStr[i]);
			int64_t d = stoll(distancesStr[i]);
			int64_t count = 0;
			for (int64_t a = 1; a <= t; ++a) {
				if (a * (t - a) > d) ++count;

			}
			product *= count;
		}
		cout << product << endl;
	}
	{
		std::ifstream is(DATA_PATH + "p6.txt");
		std::string line;
		std::getline(is, line);
		auto timesStr = splitString(line.substr(line.find(':') + 1), ' ', false);
		std::getline(is, line);
		auto distancesStr = splitString(line.substr(line.find(':') + 1), ' ', false);

		int64_t time = 0;
		int64_t distance = 0;
		for (size_t i = 0; i < timesStr.size(); ++i) { 
			int64_t t = stoll(timesStr[i]);
			int64_t d = stoll(distancesStr[i]);
			for (int64_t a = t; a != 0; a /= 10) time *= 10;
			for (int64_t a = d; a != 0; a /= 10) distance *= 10;
			time += t;
			distance += d;
		}
		int64_t count = 0;
		for (int64_t a = 1; a <= time; ++a) {
			if (a * (time - a) > distance) ++count;
		}
		cout << count << endl;
	}
}