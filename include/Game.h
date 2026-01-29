#ifndef GAME_H
#define GAME_H

#include "Point.h"
#include "Cursor.h"
#include "TileFactory.h"
#include "GameContext.h"
#include "Difficulty.h"

class Game {
public:
	Game(Difficulty diff);

	auto play() -> void;
private:
	auto click(Point p) -> void;
	auto flag(Point p) -> void;
	auto print() const -> void;

	auto game_ended() const -> bool;

	auto print_info() const -> void;
	auto print_header() const -> void;
	auto print_footer() const -> void;
	auto print_rows() const -> void;
	auto print_row(int y) const -> void;
	auto print_tile(Point p) const -> void;

	auto place_mines(int mine_count) -> void;
	auto place_empties() -> void;
private:
	GameContext _ctx;
	Cursor _cur;
	TileFactory _factory;
};

#endif
