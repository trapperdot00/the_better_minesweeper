#include "Game.h"

#include "GameState.h"
#include "Point.h"
#include "Tile.h"

#include <memory>
#include <random>
#include <iostream>
#include <chrono>
#include <thread>

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
	start_game_threads();
	_timer.stop();
}

auto Game::start_game_threads() -> void {
	std::atomic<bool> should_exit{false};
	std::jthread ui_thread{[this, &should_exit] { ui_loop(should_exit); }};
	std::jthread cmd_thread{[this, &should_exit] { cmd_loop(should_exit); }};
}

auto Game::ui_loop(std::atomic<bool>& should_exit) -> void {
	while (!should_exit.load(std::memory_order_relaxed) && !game_ended()) {
		draw_ui();
		std::this_thread::sleep_for(std::chrono::milliseconds{15});
	}
	draw_ui();
}

auto Game::cmd_loop(std::atomic<bool>& should_exit) -> void {
	char op;
	while (!should_exit.load() && !game_ended() && (std::cin >> op)) {
		switch (op) {
		case 'w':
			move_cursor(Point{0, -1});
			break;
		case 's':
			move_cursor(Point{0, 1});
			break;
		case 'a':
			move_cursor(Point{-1, 0});
			break;
		case 'd':
			move_cursor(Point{1, 0});
			break;
		case 'c':
			click();
			break;
		case 'f':
			flag();
			break;
		}
	}
	if (!std::cin) {
		should_exit.store(true, std::memory_order_relaxed);
	}
}

auto Game::draw_ui() -> void {
	std::lock_guard lock{_m};
	_ui.draw();
}

auto Game::game_ended() const -> bool {
	std::lock_guard lock{_m};
	return _ctx.remaining_mines() == _ctx.remaining_tiles()
		|| _ctx.state() != GameState::running;
}

auto Game::move_cursor(Point p) -> void {
	std::lock_guard lock{_m};
	_cur.move(p);
}

auto Game::click() -> void {
	std::lock_guard lock{_m};
	_cur.click();
}

auto Game::flag() -> void {
	std::lock_guard lock{_m};
	_cur.flag();
}
