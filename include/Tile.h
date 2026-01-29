#ifndef TILE_H
#define TILE_H

struct BoardData;
#include "Point.h"

class Tile {
public:
	Tile(BoardData& data, Point pos);

	virtual auto is_mine() const -> bool = 0;
	virtual auto clicked_rep() const -> char = 0;
	virtual auto click() -> void;
	virtual ~Tile() = default;

	auto pos() const -> Point { return _pos; }

	auto rep() const -> char;
	auto untouched_rep() const -> char;
	auto flagged_rep() const -> char;

	auto flag() -> void;

	auto clickable() const -> bool;
	auto flaggable() const -> bool;

	auto clicked() const -> bool;
	auto flagged() const -> bool;
protected:
	BoardData& _data;
private:
	Point _pos;
	bool _clicked = false;
	bool _flagged = false;
};

#endif
