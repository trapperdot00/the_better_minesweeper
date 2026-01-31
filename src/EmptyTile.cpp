#include "EmptyTile.h"

#include "GameContext.h"

EmptyTile::EmptyTile(GameContext& ctx, Point pos,
		AnsiColor flagged_color,
		AnsiColor neighbor_color) :
	Tile{ctx, pos, flagged_color},
	_neighbor_color{neighbor_color}
{}

auto EmptyTile::clicked_rep() const -> std::string {
	return (mine_neighbor_count() > 0)
		? _neighbor_color.wrap(std::to_string(mine_neighbor_count()))
		: " ";
}

auto EmptyTile::click(Tile* prev) -> void {
	Tile::click();
	if (should_click_neighbors(prev)) {
		click_neighbors();
	}
}

auto EmptyTile::is_mine() const -> bool {
	return false;
}

auto EmptyTile::neighbor_count() const -> int {
	int result = 0;
	_data.for_each_neighbor(pos(), [&result](auto) { ++result; });
	return result;
}

auto EmptyTile::mine_neighbor_count() const -> int {
	int result = 0;
	_data.for_each_neighbor(pos(), [this, &result](auto neighbor) {
		if (neighbor->is_mine()) {
			++result;
		}
	});
	return result;
}

auto EmptyTile::clicked_neighbor_count() const -> int {
	int result = 0;
	_data.for_each_neighbor(pos(), [this, &result](auto neighbor) {
		if (neighbor->clicked()) {
			++result;
		}
	});
	return result;
}

auto EmptyTile::flagged_neighbor_count() const -> int {
	int result = 0;
	_data.for_each_neighbor(pos(), [this, &result](auto neighbor) {
		if (neighbor->flagged()) {
			++result;
		}
	});
	return result;
}

auto EmptyTile::all_neighboring_mines_assumed() const -> bool {
	return mine_neighbor_count() == flagged_neighbor_count();
}

auto EmptyTile::should_click_neighbors(Tile* prev) const -> bool {
	if (prev) {
		return mine_neighbor_count() == 0;
	}
	return all_neighboring_mines_assumed();
}

auto EmptyTile::click_neighbors() -> void {
	_data.for_each_neighbor(pos(), [this](auto neighbor) {
		if (neighbor->clickable()) {
			neighbor->click(this);
		}
	});
}
