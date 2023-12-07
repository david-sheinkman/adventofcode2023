#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

#include "common.h"

using namespace std;

namespace {
struct Hand {
	string cards;
	int bid;
};

enum RANK {
	HIGH_CARD,
	ONE_PAIR,
	TWO_PAIR,
	THREE_KIND,
	FULL_HOUSE,
	FOUR_KIND,
	FIVE_KIND
};

bool compareHands1(const Hand& lhs, const Hand& rhs) {
	auto handRank = [](const Hand& h) -> int {
		map<char, int> m;
		for (auto c : h.cards) ++m[c];
		if (m.size() == 1) return FIVE_KIND;
		else if (m.size() == 2) {
			if (m.begin()->second == 1 || m.begin()->second == 4) return FOUR_KIND;
			else return FULL_HOUSE;
		}
		else if (m.size() == 3) {
			for (auto [k, v] : m) {
				if (v == 3) return THREE_KIND;
				else if (v == 2) return TWO_PAIR;
			}
		}
		else if (m.size() == 4) return ONE_PAIR;
		return HIGH_CARD;
	};
	auto cardRank = [](char c) -> int {
		switch (c)
		{
		case 'A': return 14;
		case 'K': return 13;
		case 'Q': return 12;
		case 'J': return 11;
		case 'T': return 10;
		default:
			return c - '0';
		}
	};
	int r1 = handRank(lhs);
	int r2 = handRank(rhs);
	if (r1 == r2) {
		for (int i = 0; i < 5; ++i) {
			if (lhs.cards[i] != rhs.cards[i]) return cardRank(lhs.cards[i]) < cardRank(rhs.cards[i]);
		}
		return false;
	}
	return r1 < r2;
}

bool compareHands2(const Hand& lhs, const Hand& rhs) {
	auto handRank = [](const Hand& h) -> int {
		map<char, int> m;
		for (auto c : h.cards) {
			if (c != 'J') ++m[c];
		}
		if (m.size() <= 1) return FIVE_KIND;
		else if (m.size() == 2) {
			if ((m.begin()->second == 2 || m.begin()->second == 3) && (next(m.begin()))->second != 1) return FULL_HOUSE;
			else return FOUR_KIND;
		}
		else if (m.size() == 3) {
			int oneCount = 0;
			for (auto [k, v] : m) {
				if (v == 1) ++oneCount;
			}
			if (oneCount >= 2) return THREE_KIND;
			else return TWO_PAIR;
		}
		else if (m.size() == 4) return ONE_PAIR;
		return HIGH_CARD;
		};
	auto cardRank = [](char c) -> int {
		switch (c)
		{
		case 'A': return 14;
		case 'K': return 13;
		case 'Q': return 12;
		case 'J': return 1;
		case 'T': return 10;
		default:
			return c - '0';
		}
		};
	int r1 = handRank(lhs);
	int r2 = handRank(rhs);
	if (r1 == r2) {
		for (int i = 0; i < 5; ++i) {
			if (lhs.cards[i] != rhs.cards[i]) return cardRank(lhs.cards[i]) < cardRank(rhs.cards[i]);
		}
		return false;
	}
	return r1 < r2;
}
}

void p7() {
	{
		vector<Hand> hands;
		std::ifstream is(DATA_PATH + "p7.txt");
		for (std::string line; std::getline(is, line);) {
			auto v = splitString(line, ' ', false);
			hands.emplace_back(v[0], stoi(v[1]));
		}
		sort(hands.begin(), hands.end(), compareHands1);
		int sum = 0;
		for (int i = 0; i < static_cast<int>(hands.size()); ++i) {
			sum += hands[i].bid * (i + 1);
		}
		cout << sum << endl;
	}
	{
		vector<Hand> hands;
		std::ifstream is(DATA_PATH + "p7.txt");
		for (std::string line; std::getline(is, line);) {
			auto v = splitString(line, ' ', false);
			hands.emplace_back(v[0], stoi(v[1]));
		}
		sort(hands.begin(), hands.end(), compareHands2);
		int sum = 0;
		for (int i = 0; i < static_cast<int>(hands.size()); ++i) {
			sum += hands[i].bid * (i + 1);
		}
		cout << sum << endl;
	}
}