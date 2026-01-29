#include "Game.h"
#include "Point.h"
#include "Difficulty.h"

#include <string>
#include <cstring>
#include <iostream>
#include <stdexcept>

Difficulty get_diff(const std::string& s) {
	if (s == "beginner") {
		return Difficulty::beginner;
	} else if (s == "intermediate") {
		return Difficulty::intermediate;
	} else if (s == "expert") {
		return Difficulty::expert;
	} else {
		throw std::runtime_error{"Invalid difficulty"};
	}
}

int main(int argc, char* argv[]) {
	if (argc == 5 && std::strcmp("custom", argv[1]) == 0) {
		const int width      = std::stoi(argv[2]);
		const int height     = std::stoi(argv[3]);
		const int mine_count = std::stoi(argv[4]);
		const Difficulty diff{width, height, mine_count};
		Game game{diff};
		game.play();
	} else if (argc == 2) {
		Game game{get_diff(argv[1])};
		game.play();
	} else {
		std::cerr
			<< "usage: <program> [difficulty]\n"
			<< "  difficulty  ::= <preset_diff> | <custom_diff>\n"
			<< "  preset_diff ::= 'beginner' | 'intermediate' | 'expert'\n"
			<< "  custom_diff ::= 'custom' <width> <height> <mine_count>\n"
			<< "  width       ::= number\n"
			<< "  height      ::= number\n"
			<< "  mine_count  ::= number\n";
		return 1;
	}
}
