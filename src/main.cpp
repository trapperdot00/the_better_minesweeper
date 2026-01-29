#include "Game.h"
#include "Point.h"
#include "Difficulty.h"

#include <string>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <memory>

Difficulty lookup_diff(const std::string& s) {
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

std::unique_ptr<Difficulty> parse_diff(int argc, char* argv[]) {
	if (argc > 1 && std::string{argv[1]} == "custom") {
		if (argc != 5) {
			return nullptr;
		}
		int width;
		int height;
		int mine_count;
		try {
			width      = std::stoi(argv[2]);
			height     = std::stoi(argv[3]);
			mine_count = std::stoi(argv[4]);
		} catch (...) {
			return nullptr;
		}
		return std::make_unique<Difficulty>(width, height, mine_count);
	} else if (argc == 2) {
		return std::make_unique<Difficulty>(lookup_diff(argv[1]));
	}
	return nullptr;
}

int main(int argc, char* argv[]) {
	std::unique_ptr<Difficulty> diff = parse_diff(argc, argv);
	if (!diff) {
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
	try {
		Game game{*diff};
		game.play();
	} catch (const std::exception& err) {
		std::cerr << "Error! " << err.what() << '\n';
	}
}
