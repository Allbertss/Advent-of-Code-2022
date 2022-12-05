#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>

#define DEBUG true

enum Strategy {
	Rock = 1,
	Paper = 2,
	Scissors = 3
};

enum Result {
	LOSE = 0,
	DRAW = 3,
	WIN = 6
};

class RockPaperScissors {
private:
	int opponent = Strategy::Rock;
	int my = Strategy::Rock;
public:
	RockPaperScissors(char opponent, char my) {
		switch (opponent) {
			case 'A':
				this->opponent = Strategy::Rock;
				break;
			case 'B':
				this->opponent = Strategy::Paper;
				break;
			case 'C':
				this->opponent = Strategy::Scissors;
				break;
			default:
				std::cerr << "Invalid opponent choice";
				exit(1);
				break;
		}

		switch (my) {
			case 'X':
				this->my = Strategy::Rock;
				break;
			case 'Y':
				this->my = Strategy::Paper;
				break;
			case 'Z':
				this->my = Strategy::Scissors;
				break;
			default:
				std::cerr << "Invalid choice";
				exit(1);
				break;
		}
	}

	Result shoot() {
		if (my == opponent) {
			return DRAW;
		}

		if (my == Paper && opponent == Scissors) {
			return LOSE;
		}

		if (my == Scissors && opponent == Rock) {
			return LOSE;
		}

		if (my == Rock && opponent == Paper) {
			return LOSE;
		}

		return WIN;
	}

	int getMy() {
		return this->my;
	}
};

std::vector<RockPaperScissors> readFromFile(std::string fileName);
int partOne(std::vector<RockPaperScissors> game);

int main() {
	std::vector<RockPaperScissors> game = readFromFile("input.txt");
	
	std::cout << "Part one: " << partOne(game) << "\n";

	return 0;
}

int partOne(std::vector<RockPaperScissors> game) {
	return accumulate(game.begin(), game.end(), 0, [](int i, RockPaperScissors& rps) {
		return rps.getMy() + rps.shoot() + i;
		});
}

std::vector<RockPaperScissors> readFromFile(std::string fileName) {
	std::fstream readFile(fileName);

	if (!readFile.is_open()) {
		std::cerr << fileName << " file not found.\n";
		exit(1);
	}

	char opponent, my;
	std::vector<RockPaperScissors> game;

	while (readFile >> opponent >> my) {
		game.push_back(RockPaperScissors(opponent, my));
	}

	readFile.close();

	return game;
}
