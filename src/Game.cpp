#include "Game.h"

#include "GameState.h"
#include "Point.h"
#include "Tile.h"

#include <memory>
#include <random>
#include <iostream>
#include <chrono>

Game::Game(Difficulty diff) :
	_ctx{diff.width, diff.height},
	_cur{_ctx, Point{diff.width, diff.height}},
	_placer{_ctx, diff},
	_ui{_ctx, _cur, _timer}
{
	_placer.place_tiles();
	_ctx.set_state(GameState::running);
}

auto Game::play() -> void {
	_timer.start();
	_ui.draw();
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
		_ui.draw();
	}
	_timer.end();
	std::cout << "Time: " << _timer.rep() << '\n';
}

auto Game::game_ended() const -> bool {
	return _ctx.remaining_mines() == _ctx.remaining_tiles()
		|| _ctx.state() != GameState::running;
}

