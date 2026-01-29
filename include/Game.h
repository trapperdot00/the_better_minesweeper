#ifndef GAME_H
#define GAME_H

#include "Point.h"
#include "TileFactory.h"
#include "GameContext.h"
#include "Difficulty.h"

class Game {
public:
	Game(Difficulty diff);

	auto size() const -> int { return _data.size(); }
	auto width() const -> int { return _data.width(); }
	auto height() const -> int { return _data.height(); }
	auto mine_count() const -> int { return _data.mine_count(); }
	auto clicked() const -> int { return _data.clicked_count(); }
	auto flagged() const -> int { return _data.flagged_count(); }
	auto remaining_tiles() const -> int {
		return size() - clicked() - flagged();
	}
	auto remaining_mines() const -> int {
		return mine_count() - flagged();
	}

	auto game_ended() const -> bool {
		return remaining_mines() == remaining_tiles()
			|| _data.state() != GameState::running;
	}

	auto click(Point p) -> void;
	auto flag(Point p) -> void;
	auto print() const -> void;
private:
	auto print_info() const -> void;
	auto print_header() const -> void;
	auto print_footer() const -> void;
	auto print_rows() const -> void;
	auto print_row(int y) const -> void;
	auto print_tile(Point p) const -> void;

	auto place_mines(int mine_count) -> void;
	auto place_empties() -> void;
private:
	GameContext _data;
	TileFactory _factory;
};

#endif
