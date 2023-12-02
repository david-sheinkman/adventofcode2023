#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

#include "common.h"

using namespace std;
namespace {
struct RGB {
	int r = 0;
	int g = 0;
	int b = 0;
};
}

void p2() {
	{
		const RGB maxVals = { 12, 13, 14 };
		std::ifstream is(DATA_PATH + "p2.txt");

		int sum = 0;
		for (std::string line; std::getline(is, line);) {
			stringstream ss(line);
			string s;
			int gameNumber;
			ss >> s >> gameNumber >> s;
			bool possible = true;
			while (ss.tellp() == 0) {
				for (std::string game; std::getline(ss, game, ';');) {
					RGB rgb;
					stringstream ss2(game);
					int value = 0;
					string color;
					ss2 >> value >> color;
					while (ss2.tellp() == 0) {
						if (color.back() == ',') color = color.substr(0, color.size() - 1);
						if (color == "red") rgb.r = value;
						else if (color == "green") rgb.g = value;
						else if (color == "blue") rgb.b = value;
						ss2 >> value >> color;
					}
					if (rgb.r > maxVals.r || rgb.g > maxVals.g || rgb.b > maxVals.b) {
						possible = false;
						break;
					}
				}
			}
			if (possible) {
				sum += gameNumber;
			}
		}
		cout << sum << endl;
	}
	{
		std::ifstream is(DATA_PATH + "p2.txt");

		int sum = 0;
		for (std::string line; std::getline(is, line);) {
			stringstream ss(line);
			string s;
			ss >> s >> s;
			RGB minVals;
			while (ss.tellp() == 0) {
				for (std::string game; std::getline(ss, game, ';');) {
					stringstream ss2(game);
					int value = 0;
					string color;
					ss2 >> value >> color;
					while (ss2.tellp() == 0) {
						if (color.back() == ',') color = color.substr(0, color.size() - 1);
						if (color == "red") minVals.r = max(minVals.r, value);
						else if (color == "green") minVals.g = max(minVals.g, value);
						else if (color == "blue") minVals.b = max(minVals.b, value);
						ss2 >> value >> color;
					}
				}
			}
			sum += minVals.r * minVals.g * minVals.b;
		}
		cout << sum << endl;
	}
}