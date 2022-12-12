#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>
#include <queue>

#define DEBUG false

std::vector<std::string> readFromFile(std::string fileName);
int solve(std::vector<std::string> map, char startingChar);

bool isPossible(int row, int col, int n, int m) {
	return !(row >= n || col >= m || row < 0 || col < 0);
}

int main() {
	std::vector<std::string> map = readFromFile("input.txt");

	std::cout << "Part 1: " << solve(map, 'S') << "\n";
	std::cout << "Part 2: " << solve(map, 'a') << "\n";

	return 0;
}

int solve(std::vector<std::string> map, char startingChar) {
	int columnSize = map.size();
	int rowSize = map[0].size();

#if DEBUG
	std::cout << "column " << columnSize << "\nrow " << rowSize << "\n";
#endif

	std::pair<int, int> end;

	for (int i = 0; i < columnSize; i++) {
		for (int j = 0; j < rowSize; j++) {
			if (map[i][j] == 'E') {
				end = std::make_pair(i, j);
				map[i][j] = 'z';
			}
		}
	}

	std::vector<std::vector<bool>> visited(columnSize, std::vector<bool>(rowSize, false));
	std::queue<std::pair<int, std::pair<int, int>>> queue;

	visited[end.first][end.second] = true;

	queue.push(std::make_pair(0, end));

	while (!queue.empty()) {
		int distance = queue.front().first;
		int row = queue.front().second.first;
		int column = queue.front().second.second;

		queue.pop();

		if (map[row][column] == startingChar) {
			return distance;
		}

		int dx[4] = {
			1, -1, 0, 0
		};

		int dy[4] = {
			0, 0, 1, -1
		};

		for (int i = 0; i < 4; i++) {
			if (isPossible(row + dx[i], column + dy[i], columnSize, rowSize) && !visited[row + dx[i]][column + dy[i]]) {
				char prev = map[row + dx[i]][column + dy[i]] == 'S' ? 'a' : map[row + dx[i]][column + dy[i]];

				if (map[row][column] - prev <= 1) {
					visited[row + dx[i]][column + dy[i]] = true;
					queue.push(std::make_pair(distance + 1, std::make_pair(row + dx[i], column + dy[i])));
				}
			}
		}
	}
	
	std::cerr << "Can't find.\n";

	return -1;
}

std::vector<std::string> readFromFile(std::string fileName) {
	std::fstream readFile(fileName);

	std::vector<std::string> map;

	if (readFile.is_open()) {
		std::string line;

		while (std::getline(readFile, line)) {
			map.push_back(line);
		}
	}

	readFile.close();

	return map;
}