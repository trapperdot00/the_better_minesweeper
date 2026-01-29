#include "Game.h"

#include "GameState.h"
#include "Point.h"
#include "Tile.h"

#include <memory>
#include <random>
#include <iostream>

Game::Game(Difficulty diff) :
	_ctx{diff.width, diff.height},
	_cur{_ctx, Point{diff.width, diff.height}},
	_factory{_ctx}
{
	place_mines(diff.mine_count);
	place_empties();
	_ctx.set_state(GameState::running);
}

auto Game::play() -> void {
	print();
	for (char op; !game_ended() && (std::cin >> op); ) {
		switch (op) {
		case 'w':
			_cur.move(Point{0, -1});
			break;
		case 's':
			_cur.move(Point{0, 1});
			break;
		case 'a':
			_cur.move(Point{-1, 0});
			break;
		case 'd':
			_cur.move(Point{1, 0});
			break;
		case 'c':
			_cur.click();
			break;
		case 'f':
			_cur.flag();
			break;
		}
		print();
	}
}

auto Game::print() const -> void {
	print_info();
	print_header();
	print_rows();
	print_footer();
}

auto Game::game_ended() const -> bool {
	return _ctx.remaining_mines() == _ctx.remaining_tiles()
		|| _ctx.state() != GameState::running;
}

auto Game::print_info() const -> void {
	std::cout
		<< "clicked: " << _ctx.clicked_count() << '\n'
		<< "flagged: " << _ctx.flagged_count() << '\n'
		<< "remaining tiles: " << _ctx.remaining_tiles() << '\n'
		<< "remaining mines: " << _ctx.remaining_mines() << '\n';
}

auto Game::print_header() const -> void {
	std::cout << "  | ";
	for (int i = 0; i < _ctx.width(); ++i) {
		std::cout << i % 10 << ' ';
	}
	std::cout << "|\n";
	std::cout << std::string(_ctx.width() * 2 + 5, '-') << '\n';
}

auto Game::print_footer() const -> void {
	std::cout << std::string(_ctx.width() * 2 + 5, '-') << '\n';
	std::cout << "  | ";
	for (int i = 0; i < _ctx.width(); ++i) {
		std::cout << i % 10 << ' ';
	}
	std::cout << "|\n";
}

auto Game::print_rows() const -> void {
	for (int y = 0; y < _ctx.height(); ++y) {
		print_row(y);
	}
}

auto Game::print_row(int y) const -> void {
	std::cout << y % 10 << " | ";
	for (int x = 0; x < _ctx.width(); ++x) {
		const Point p{x, y};
		print_tile(p);
	}
	std::cout << "|\n";
}

auto Game::print_tile(Point p) const -> void {
	std::cout << _ctx.get_tile(p)->rep() << ' ';
}

void Game::place_mines(int mine_count) {
	if (mine_count > _ctx.size()) {
		throw std::runtime_error{"more mines than tiles"};
	}
	std::mt19937 e{std::random_device{}()};
	std::uniform_int_distribution<int> x_gen(0, _ctx.width() - 1);
	std::uniform_int_distribution<int> y_gen(0, _ctx.height() - 1);
	for (int remaining = mine_count; remaining > 0; ) {
		const Point p{x_gen(e), y_gen(e)};
		if (!_ctx.get_tile(p)) {
			_ctx.set_tile(p, _factory.create_mine(p));
			_ctx.increment_mine_count();
			--remaining;
		}
	}
}

void Game::place_empties() {
	for (int y = 0; y < _ctx.height(); ++y) {
		for (int x = 0; x < _ctx.width(); ++x) {
			const Point p{x, y};
			if (!_ctx.get_tile(p)) {
				_ctx.set_tile(p, _factory.create_empty(p));
			}
		}
	}
}
