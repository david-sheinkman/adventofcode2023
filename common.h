#pragma once

#include <string>

const std::string DATA_PATH = "..\\..\\..\\data\\";

template<typename T, typename... Ts>
void print(T&& arg, Ts... arg2) {
	std::cout << arg;
	if constexpr (sizeof...(arg2) != 0) {
		std::cout << ", ";
		print(arg2...);
	}
	else std::cout << std::endl;
}