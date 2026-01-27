#include "Board.h"
#include "Point.h"
#include "Tiles.h"
#include "Difficulty.h"

#include <string>
#include <cstring>
#include <iostream>
#include <stdexcept>

void play(Board& b) {
	b.print();
	char op;
	int x;
	int y;
	while (!b.game_ended() && (std::cin >> op >> x >> y)) {
		const Point p{x, y};
		switch (op) {
		case 'c':
			b.click(p);
			break;
		case 'f':
			b.flag(p);
			break;
		}
		b.print();
	}
}

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
		int width      = std::stoi(argv[2]);
		int height     = std::stoi(argv[3]);
		int mine_count = std::stoi(argv[4]);
		Board b{width, height, mine_count};
		play(b);
	} else if (argc == 2) {
		Board b{get_diff(argv[1])};
		play(b);
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
