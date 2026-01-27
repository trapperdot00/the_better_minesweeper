#include "EmptyTile.h"

#include "BoardData.h"

#include <algorithm>

auto to_char(int i) -> char {
	if (i < 0) return '0';
	if (i > 9) return '9';
	return '0' + i;
}

auto EmptyTile::clicked_rep() const -> char {
	return (neighbor_count() > 0)
		? to_char(neighbor_count())
		: ' ';
}

auto EmptyTile::click() -> void {
	Tile::click();
	if (neighbor_count() == 0) {
		click_neighbors();
	}
}

auto EmptyTile::neighbor_count() const -> int {
	int result = 0;
	for_each_neighbor([this, &result](Point p) {
		if (_data.tiles.get_tile(p)->is_mine()) {
			++result;
		}
	});
	return result;
}

auto EmptyTile::is_mine() const -> bool {
	return false;
}

auto EmptyTile::click_neighbors() -> void {
	for_each_neighbor([this](Point p) {
		auto neighbor = _data.tiles.get_tile(p);
		if (!neighbor->is_mine() && !neighbor->clicked()) {
			_data.tiles.get_tile(p)->click();
		}
	});
}

auto EmptyTile::clamp_x(int x) const -> int {
	return std::clamp(x, 0, _data.width - 1);
}

auto EmptyTile::clamp_y(int y) const -> int {
	return std::clamp(y, 0, _data.height - 1);
}

auto EmptyTile::neighbor_min_x() const -> int {
	return clamp_x(_pos.x - 1);
}

auto EmptyTile::neighbor_max_x() const -> int {
	return clamp_x(_pos.x + 1);
}

auto EmptyTile::neighbor_min_y() const -> int {
	return clamp_y(_pos.y - 1);
}

auto EmptyTile::neighbor_max_y() const -> int {
	return clamp_y(_pos.y + 1);
}

auto EmptyTile::for_each_neighbor(std::function<void(Point)> func) const -> void {
	for (int y = neighbor_min_y(); y <= neighbor_max_y(); ++y) {
		for (int x = neighbor_min_x(); x <= neighbor_max_x(); ++x) {
			func(Point{x, y});
		}
	}
}
