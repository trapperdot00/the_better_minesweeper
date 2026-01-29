#ifndef CURSOR_H
#define CURSOR_H

#include "Point.h"
#include "GameContext.h"
#include "Tile.h"

#include <memory>

class Cursor {
public:
	Cursor(GameContext& ctx, Point size);

	auto pos() const -> Point { return _pos; }

	auto move(Point offset) -> void;
	auto click() -> void;
	auto flag() -> void;

	auto get_tile() const -> std::shared_ptr<Tile>;
private:
	GameContext& _ctx;
	const Point _size;
	Point _pos{0, 0};
};

#endif
