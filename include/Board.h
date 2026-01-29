#ifndef BOARD_H
#define BOARD_H

#include "Point.h"
#include "TileFactory.h"
#include "BoardData.h"
#include "Difficulty.h"

class Board {
public:
	Board(int width, int height, int mine_count);
	Board(Difficulty diff);

	auto size() const -> int { return _data.width * _data.height; }
	auto width() const -> int { return _data.width; }
	auto height() const -> int { return _data.height; }
	auto mine_count() const -> int { return _data.mine_count; }
	auto clicked() const -> int { return _data.clicked; }
	auto flagged() const -> int { return _data.flagged; }
	auto remaining_tiles() const -> int { return size() - clicked() - flagged(); }
	auto remaining_mines() const -> int { return mine_count() - flagged(); }

	auto game_ended() const -> bool {
		return remaining_mines() == remaining_tiles()
			|| _data.state != GameState::running;
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

	auto place_mines() -> void;
	auto place_empties() -> void;
private:
	BoardData _data;
	TileFactory _factory;
};

#endif
