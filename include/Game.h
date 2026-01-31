#ifndef GAME_H
#define GAME_H

#include "Point.h"
#include "Cursor.h"
#include "GameContext.h"
#include "Difficulty.h"
#include "TilePlacer.h"
#include "UI.h"
#include "Timer.h"

#include <atomic>
#include <mutex>

class Game {
public:
	explicit Game(Difficulty diff);

	auto play() -> void;
private:
	auto start_game_threads() -> void;
	auto ui_loop(std::atomic<bool>& should_exit) -> void;
	auto cmd_loop(std::atomic<bool>& should_exit) -> void;

	auto draw_ui() -> void;
	auto game_ended() const -> bool;
	auto move_cursor(Point p) -> void;
	auto click() -> void;
	auto flag() -> void;
private:
	mutable std::mutex _m;
	GameContext _ctx;
	Cursor _cur;
	TilePlacer _placer;
	Timer _timer;
	UI _ui;
};

#endif
