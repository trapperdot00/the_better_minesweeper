#include "UI.h"

#include "GameContext.h"
#include "Cursor.h"
#include "Tile.h"

#include <iostream>

auto UI::draw() -> void {
	draw_info();
	draw_header();
	draw_rows();
	draw_footer();
}

auto UI::draw_info() -> void {
	std::cout
		<< "clicked: " << _ctx.clicked_count() << '\n'
		<< "flagged: " << _ctx.flagged_count() << '\n'
		<< "remaining tiles: " << _ctx.remaining_tiles() << '\n'
		<< "remaining mines: " << _ctx.remaining_mines() << '\n';
}

auto UI::draw_header() -> void {
	std::cout << "  | ";
	for (int i = 0; i < _ctx.width(); ++i) {
		std::cout << i % 10 << ' ';
	}
	std::cout << "|\n";
	std::cout << std::string(_ctx.width() * 2 + 5, '-') << '\n';
}

auto UI::draw_footer() -> void {
	std::cout << std::string(_ctx.width() * 2 + 5, '-') << '\n';
	std::cout << "  | ";
	for (int i = 0; i < _ctx.width(); ++i) {
		std::cout << i % 10 << ' ';
	}
	std::cout << "|\n";
}

auto UI::draw_rows() -> void {
	for (int y = 0; y < _ctx.height(); ++y) {
		draw_row(y);
	}
}

auto UI::draw_row(int y) -> void {
	std::cout << y % 10 << " |";
	for (int x = 0; x < _ctx.width(); ++x) {
		const Point p{x, y};
		if (p == _cursor.pos()) {
			std::cout << '>';
		} else {
			if (Point{p.x - 1, p.y} == _cursor.pos()) {
				std::cout << '<';
			} else {
				std::cout << ' ';
			}
		}
		draw_tile(p);
	}
	if (_cursor.pos().y == y && _cursor.pos().x == _ctx.width() - 1) {
		std::cout << '<';
	} else {
		std::cout << ' ';
	}
	std::cout << "|\n";
}

auto UI::draw_tile(Point p) -> void {
	std::cout << _ctx.get_tile(p)->rep();
}
