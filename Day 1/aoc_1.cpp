// https://adventofcode.com/2022/day/1

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>

#define DEBUG false

std::vector<std::vector<int>> readFromFile();
std::vector<int> solve();
int partOne(std::vector<int> vector);
int partTwo(std::vector<int> vector);

int main() {
	std::vector<int> calories = solve();

	std::cout << "Part 1: " << partOne(calories) << "\n";
	std::cout << "Part 2: " << partTwo(calories) << "\n";
}

int partOne(std::vector<int> vector) {
	return vector[0];
}

int partTwo(std::vector<int> vector) {
	return vector[0] + vector[1] + vector[2];
}

std::vector<int> solve() {
	std::vector<std::vector<int>> groups = readFromFile();
	std::vector<int> calories;

	for (auto& group : groups) {
		int sum = accumulate(group.begin(), group.end(), 0);

		if (sum != 0) {
			calories.push_back(sum);
		}
	}

	sort(calories.begin(), calories.end(), std::greater<int>());

#if DEBUG
	for (auto& c : calories) {
		std::cout << c << "\n";
	}
#endif

	return calories;
}

std::vector<std::vector<int>> readFromFile() {
	std::vector<std::vector<int>> vector(10000, std::vector<int>(1000, 0));

	std::fstream readFile("input.txt");
	std::string line;
	int index = 0;

	if (readFile.is_open()) {
		while (std::getline(readFile, line)) {
			if (line.length()) {
				vector[index].push_back(std::stoi(line));
			} else {
				index++;
			}
		}
	}

	readFile.close();

	return vector;
}

