#ifndef EMPTYTILE_H
#define EMPTYTILE_H

struct GameContext;
#include "Point.h"
#include "Tile.h"
#include "AnsiColor.h"

#include <string>
#include <functional>

class EmptyTile : public Tile {
public:
	EmptyTile(GameContext& ctx, Point pos,
			AnsiColor flagged_color,
			AnsiColor neighbor_color);

	auto clicked_rep() const -> std::string override;
	auto click() -> void override;
	auto is_mine() const -> bool override;

	auto neighbor_count() const -> int;
	auto mine_neighbor_count() const -> int;
	auto clicked_neighbor_count() const -> int;
	auto flagged_neighbor_count() const -> int;
	auto all_neighboring_mines_assumed() const -> bool;
private:
	auto should_click_neighbors() const -> bool;
	auto click_neighbors() -> void;

	auto clamp_x(int x) const -> int;
	auto clamp_y(int y) const -> int;
	auto neighbor_min_x() const -> int;
	auto neighbor_max_x() const -> int;
	auto neighbor_min_y() const -> int;
	auto neighbor_max_y() const -> int;

	void for_each_neighbor(std::function<void(Point)> func) const;
private:
	AnsiColor _neighbor_color;
};

#endif
