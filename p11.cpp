#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "common.h"

using namespace std;
namespace {
struct Point {
	size_t row = 0;
	size_t col = 0;
};
}

void p11() {
	{
		std::ifstream is(DATA_PATH + "p11.txt");
		vector<string> data;
		for (string line; std::getline(is, line);) {
			data.emplace_back(line);
		}
		vector<int> emptyRows;
		vector<int> emptyColumns;
		int previous = 0;
		for (size_t r = 0; r < data.size(); ++r) {
			bool all = true;
			for (size_t c = 0; c < data[r].size(); ++c) {
				if (data[r][c] != '.') {
					all = false;
					break;
				}
			}
			previous = emptyRows.emplace_back(previous + all);
		}
		for (size_t c = 0; c < data[0].size(); ++c) {
			bool all = true;
			for (size_t r = 0; r < data.size(); ++r) {
				if (data[r][c] != '.') {
					all = false;
					break;
				}
			}
			previous = emptyColumns.emplace_back(previous + all);
		}
		vector<Point> points;
		for (size_t r = 0; r < data.size(); ++r) {
			for (size_t c = 0; c < data[r].size(); ++c) {
				if (data[r][c] == '#') {
					points.emplace_back(r, c);
				}
			}
		}
		size_t sum = 0;
		for (size_t i = 0; i < points.size(); ++i) {
			for (size_t j = i + 1; j < points.size(); ++j) {
				size_t x1 = min(points[i].col, points[j].col);
				size_t x2 = max(points[i].col, points[j].col);
				size_t y1 = min(points[i].row, points[j].row);
				size_t y2 = max(points[i].row, points[j].row);
				sum += y2 - y1 + x2 - x1 + emptyColumns[x2] - emptyColumns[x1] + emptyRows[y2] - emptyRows[y1];
			}
		}
		cout << sum << endl;
	}
	{
		std::ifstream is(DATA_PATH + "p11.txt");
		vector<string> data;
		for (string line; std::getline(is, line);) {
			data.emplace_back(line);
		}
		vector<int64_t> emptyRows;
		vector<int64_t> emptyColumns;
		int64_t previous = 0;
		const int64_t EXPANSION = 1000000 - 1;
		for (size_t r = 0; r < data.size(); ++r) {
			bool all = true;
			for (size_t c = 0; c < data[r].size(); ++c) {
				if (data[r][c] != '.') {
					all = false;
					break;
				}
			}
			previous = emptyRows.emplace_back(previous + all * EXPANSION);
		}
		for (size_t c = 0; c < data[0].size(); ++c) {
			bool all = true;
			for (size_t r = 0; r < data.size(); ++r) {
				if (data[r][c] != '.') {
					all = false;
					break;
				}
			}
			previous = emptyColumns.emplace_back(previous + all * EXPANSION);
		}
		vector<Point> points;
		for (size_t r = 0; r < data.size(); ++r) {
			for (size_t c = 0; c < data[r].size(); ++c) {
				if (data[r][c] == '#') {
					points.emplace_back(r, c);
				}
			}
		}
		int64_t sum = 0;
		for (size_t i = 0; i < points.size(); ++i) {
			for (size_t j = i + 1; j < points.size(); ++j) {
				int64_t x1 = min(points[i].col, points[j].col);
				int64_t x2 = max(points[i].col, points[j].col);
				int64_t y1 = min(points[i].row, points[j].row);
				int64_t y2 = max(points[i].row, points[j].row);
				sum += y2 - y1 + x2 - x1 + emptyColumns[x2] - emptyColumns[x1] + emptyRows[y2] - emptyRows[y1];
			}
		}
		cout << sum << endl;
	}
}
