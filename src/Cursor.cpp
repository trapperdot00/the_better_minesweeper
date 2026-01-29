#include "Cursor.h"

#include <algorithm>

Cursor::Cursor(GameContext& ctx, Point size) :
	_ctx{ctx},
	_size{size}
{}

auto Cursor::move(Point offset) -> void {
	const int x = std::clamp(_pos.x + offset.x, 0, _size.x - 1);
	const int y = std::clamp(_pos.y + offset.y, 0, _size.y - 1);
	_pos = Point{x, y};
}

auto Cursor::click() -> void {
	get_tile()->click();
}

auto Cursor::flag() -> void {
	get_tile()->flag();
}

auto Cursor::get_tile() const -> std::shared_ptr<Tile> {
	return _ctx.get_tile(_pos);
}
