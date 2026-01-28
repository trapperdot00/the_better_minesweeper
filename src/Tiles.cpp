#include "Tiles.h"

#include "Tile.h"
#include "Point.h"

#include <stdexcept>

Tiles::Tiles(int width, int height) :
	_width{width},
	_height{height},
	_data(width * height)
{}

auto Tiles::get_tile(Point p) const -> std::shared_ptr<Tile> {
	if (!in_range(p)) {
		throw std::runtime_error{"point out of range"};
	}
	return _data[to_index(p)];
}

auto Tiles::set_tile(Point p, std::shared_ptr<Tile> tile) -> void {
	if (!in_range(p)) {
		throw std::runtime_error{"point out of range"};
	}
	_data[to_index(p)] = tile;
}

auto Tiles::in_range(Point p) const -> bool {
	return (p.x >= 0 && p.x < _width)
		&& (p.y >= 0 && p.y < _height);
}

auto Tiles::to_index(Point p) const -> int {
	return p.y * _width + p.x;
}
