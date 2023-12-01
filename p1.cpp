#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "common.h"

using namespace std;


void p1() {
	std::ifstream is(DATA_PATH + "p1.txt");

	for (std::string str; std::getline(is, str);) {
	}
}