#include "Board.h"
#include "Point.h"
#include "Tiles.h"

#include <string>
#include <iostream>

int main(int argc, char* argv[]) {
	if (argc != 4) {
		std::cerr << "usage: <program> <width> <height> <mine_count>\n";
		return 1;
	}
	int width      = std::stoi(argv[1]);
	int height     = std::stoi(argv[2]);
	int mine_count = std::stoi(argv[3]);
	Board b{width, height, mine_count};
	b.print();

	char op;
	int x;
	int y;
	while (std::cin >> op >> x >> y) {
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
