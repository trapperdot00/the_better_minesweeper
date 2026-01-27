#ifndef TILE_H
#define TILE_H

class BoardData;
#include "Point.h"

class Tile {
public:
	Tile(BoardData& data, Point pos);

	auto rep() const -> char;
	virtual auto untouched_rep() const -> char;
	virtual auto flagged_rep() const -> char;
	virtual auto clicked_rep() const -> char = 0;

	virtual auto click() -> void;
	virtual auto flag() -> void;

	auto clickable() const -> bool;
	auto clicked() const -> bool;
	auto flagged() const -> bool;
	virtual auto is_mine() const -> bool = 0;

	virtual ~Tile() = default;
protected:
	BoardData& _data;
	Point _pos;
private:
	bool _clicked = false;
	bool _flagged = false;
};

#endif
