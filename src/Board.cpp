#include "Board.h"

#include "Tile.h"
#include "GameState.h"
#include "Point.h"

#include <memory>
#include <random>
#include <iostream>

Board::Board(int width, int height, int mine_count) :
	_data{width, height},
	_factory{_data}
{
	place_mines(mine_count);
	place_empties();
	_data.set_state(GameState::running);
}

Board::Board(Difficulty diff) :
	Board{diff.width, diff.height, diff.mine_count}
{}

auto Board::click(Point p) -> void {
	_data.get_tile(p)->click();
}

auto Board::flag(Point p) -> void {
	_data.get_tile(p)->flag();
}

auto Board::print() const -> void {
	print_info();
	print_header();
	print_rows();
	print_footer();
}

auto Board::print_info() const -> void {
	std::cout
		<< "clicked: " << clicked() << '\n'
		<< "flagged: " << flagged() << '\n'
		<< "remaining tiles: " << remaining_tiles() << '\n'
		<< "remaining mines: " << remaining_mines() << '\n';
}

auto Board::print_header() const -> void {
	std::cout << "  | ";
	for (int i = 0; i < _data.width(); ++i) {
		std::cout << i % 10 << ' ';
	}
	std::cout << "|\n";
	std::cout << std::string(_data.width() * 2 + 5, '-') << '\n';
}

auto Board::print_footer() const -> void {
	std::cout << std::string(_data.width() * 2 + 5, '-') << '\n';
	std::cout << "  | ";
	for (int i = 0; i < _data.width(); ++i) {
		std::cout << i % 10 << ' ';
	}
	std::cout << "|\n";
}

auto Board::print_rows() const -> void {
	for (int y = 0; y < height(); ++y) {
		print_row(y);
	}
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
	std::cout << _data.get_tile(p)->rep() << ' ';
}

void Board::place_mines(int mine_count) {
	if (mine_count > size()) {
		throw std::runtime_error{"more mines than tiles"};
	}
	std::mt19937 e{std::random_device{}()};
	std::uniform_int_distribution<int> x_gen(0, width() - 1);
	std::uniform_int_distribution<int> y_gen(0, height() - 1);
	for (int remaining = mine_count; remaining > 0; ) {
		const Point p{x_gen(e), y_gen(e)};
		if (!_data.get_tile(p)) {
			_data.set_tile(p, _factory.create_mine(p));
			--remaining;
		}
	}
}

void Board::place_empties() {
	for (int y = 0; y < height(); ++y) {
		for (int x = 0; x < width(); ++x) {
			const Point p{x, y};
			if (!_data.get_tile(p)) {
				_data.set_tile(p, _factory.create_empty(p));
			}
		}
	}
}
