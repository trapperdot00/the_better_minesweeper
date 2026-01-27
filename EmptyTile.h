#ifndef EMPTYTILE_H
#define EMPTYTILE_H

#include "Tile.h"

#include <functional>

class EmptyTile : public Tile {
public:
	using Tile::Tile;

	auto clicked_rep() const -> char override;
	auto click() -> void override;
	auto is_mine() const -> bool override;

	auto neighbor_count() const -> int;
private:
	auto click_neighbors() -> void;

	auto clamp_x(int x) const -> int;
	auto clamp_y(int y) const -> int;
	auto neighbor_min_x() const -> int;
	auto neighbor_max_x() const -> int;
	auto neighbor_min_y() const -> int;
	auto neighbor_max_y() const -> int;

	void for_each_neighbor(std::function<void(Point)> func) const;
};

#endif
