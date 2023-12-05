#include "common.h"
#include <sstream>

std::vector<std::string> splitString(const std::string& str, const char c, const bool allowEmpty) {
	std::vector<std::string> result;
	std::stringstream ss(str);
	for (std::string s; std::getline(ss, s, c);) {
		if (allowEmpty || !s.empty()) result.emplace_back(s);
	}
	return result;
}