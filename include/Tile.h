#ifndef TILE_H
#define TILE_H

#include "FwdDecls.h"
#include "Point.h"
#include "AnsiColor.h"

#include <string>

class Tile {
public:
	Tile(GameContext& data, Point pos,
			AnsiColor flagged_color);

	virtual auto is_mine() const -> bool = 0;
	virtual auto clicked_rep() const -> std::string = 0;
	virtual auto click(Tile* prev = nullptr) -> void;
	virtual ~Tile() = default;

	auto pos() const -> Point { return _pos; }

	auto rep() const -> std::string;
	auto untouched_rep() const -> std::string;
	auto flagged_rep() const -> std::string;

	auto flag() -> void;

	auto clickable() const -> bool;
	auto flaggable() const -> bool;

	auto clicked() const -> bool;
	auto flagged() const -> bool;
protected:
	GameContext& _data;
private:
	Point _pos;
	AnsiColor _flagged_color;
	bool _clicked = false;
	bool _flagged = false;
};

#endif
