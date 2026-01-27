#ifndef BOARD_H
#define BOARD_H

#include "Point.h"
#include "TileFactory.h"
#include "BoardData.h"

class Board {
public:
	Board(int width, int height, int mine_count);

	auto size() const -> int { return _data.width * _data.height; }
	auto width() const -> int { return _data.width; }
	auto height() const -> int { return _data.height; }
	auto mine_count() const -> int { return _data.mine_count; }

	auto click(Point p) -> void;
	auto flag(Point p) -> void;
	auto print() const -> void;
private:
	auto place_mines() -> void;
	auto place_empties() -> void;
private:
	BoardData _data;
	TileFactory _factory;
};

#endif
