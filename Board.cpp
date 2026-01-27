#include "Board.h"

#include "Tile.h"
#include "GameState.h"
#include "Point.h"

#include <memory>
#include <random>
#include <iostream>

Board::Board(int width, int height, int mine_count) :
	_data{width, height, mine_count, GameState::ready, Tiles{width, height}},
	_factory{_data}
{
	place_mines();
	place_empties();
}

Board::Board(Difficulty diff) :
	Board{diff.width, diff.height, diff.mine_count}
{}

auto Board::click(Point p) -> void {
	_data.tiles.get_tile(p)->click();
}

auto Board::flag(Point p) -> void {
	_data.tiles.get_tile(p)->flag();
}

auto Board::print() const -> void {
	print_header();
	for (int y = 0; y < height(); ++y) {
		print_row(y);
	}
	print_footer();
}

auto Board::print_header() const -> void {
	std::cout << "  | ";
	for (int i = 0; i < _data.width; ++i) {
		std::cout << i % 10 << ' ';
	}
	std::cout << "|\n";
	std::cout << std::string(_data.width * 2 + 5, '-') << '\n';
}

auto Board::print_footer() const -> void {
	std::cout << std::string(_data.width * 2 + 5, '-') << '\n';
	std::cout << "  | ";
	for (int i = 0; i < _data.width; ++i) {
		std::cout << i % 10 << ' ';
	}
	std::cout << "|\n";
}

auto Board::print_row(int y) const -> void {
	std::cout << y % 10 << " | ";
	for (int x = 0; x < width(); ++x) {
		const Point p{x, y};
		print_tile(p);
	}
	std::cout << "|\n";
}

auto Board::print_tile(Point p) const -> void {
	std::cout << _data.tiles.get_tile(p)->rep() << ' ';
}

void Board::place_mines() {
	if (mine_count() > size()) {
		throw std::runtime_error{"more mines than tiles"};
	}
	std::mt19937 engine{std::random_device{}()};
	std::uniform_int_distribution<int> dist(0, size() - 1);
	for (int remaining = mine_count(); remaining > 0; ) {
		const int i = dist(engine);
		if (!_data.tiles.get_tile(i)) {
			const Point pos = _data.tiles.to_point(i);
			_data.tiles.set_tile(i, _factory.create_mine(pos));
			--remaining;
		}
	}
}

void Board::place_empties() {
	for (int i = 0; i < size(); ++i) {
		if (!_data.tiles.get_tile(i)) {
			const Point pos = _data.tiles.to_point(i);
			_data.tiles.set_tile(i, _factory.create_empty(pos));
		}
	}
}
