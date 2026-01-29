#include "Tiles.h"

#include "Tile.h"
#include "Point.h"

#include <stdexcept>
#include <algorithm>

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

auto Tiles::for_each_neighbor
(Point p, std::function<void(Point)> func) const -> void {
	for (int y = neighbor_min_y(p); y <= neighbor_max_y(p); ++y) {
		for (int x = neighbor_min_x(p); x <= neighbor_max_x(p); ++x) {
			const Point neighbor{x, y};
			if (p != neighbor) {
				func(neighbor);
			}
		}
	}
}

auto Tiles::in_range(Point p) const -> bool {
	return (p.x >= 0 && p.x < _width)
		&& (p.y >= 0 && p.y < _height);
}

auto Tiles::to_index(Point p) const -> int {
	return p.y * _width + p.x;
}

auto Tiles::clamp_x(int x) const -> int {
	return std::clamp(x, 0, _width - 1);
}

auto Tiles::clamp_y(int y) const -> int {
	return std::clamp(y, 0, _height - 1);
}

auto Tiles::neighbor_min_x(Point p) const -> int {
	return clamp_x(p.x - 1);
}

auto Tiles::neighbor_max_x(Point p) const -> int {
	return clamp_x(p.x + 1);
}

auto Tiles::neighbor_min_y(Point p) const -> int {
	return clamp_y(p.y - 1);
}

auto Tiles::neighbor_max_y(Point p) const -> int {
	return clamp_y(p.y + 1);
}
