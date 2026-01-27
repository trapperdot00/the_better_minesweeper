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

void Board::click(Point p) {
	_data.tiles.get_tile(p)->click();
}

void Board::flag(Point p) {
	_data.tiles.get_tile(p)->flag();
}

void Board::print() const {
	for (int y = 0; y < height(); ++y) {
		for (int x = 0; x < width(); ++x) {
			std::cout << _data.tiles.get_tile({x, y})->rep() << ' ';
		}
		std::cout << '\n';
	}
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
