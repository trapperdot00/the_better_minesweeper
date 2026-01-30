#include "EmptyTile.h"

#include "GameContext.h"

auto EmptyTile::clicked_rep() const -> std::string {
	return std::string{"\e[0;34m"}
		+ ((mine_neighbor_count() > 0)
			? std::to_string(mine_neighbor_count())
			: " ")
		+ "\e[0m";
}

auto EmptyTile::click() -> void {
	Tile::click();
	if (should_click_neighbors()) {
		click_neighbors();
	}
}

auto EmptyTile::is_mine() const -> bool {
	return false;
}

auto EmptyTile::neighbor_count() const -> int {
	int result = 0;
	_data.for_each_neighbor(pos(), [&result](Point) { ++result; });
	return result;
}

auto EmptyTile::mine_neighbor_count() const -> int {
	int result = 0;
	_data.for_each_neighbor(pos(), [this, &result](Point p) {
		if (_data.get_tile(p)->is_mine()) {
			++result;
		}
	});
	return result;
}

auto EmptyTile::clicked_neighbor_count() const -> int {
	int result = 0;
	_data.for_each_neighbor(pos(), [this, &result](Point p) {
		if (_data.get_tile(p)->clicked()) {
			++result;
		}
	});
	return result;
}

auto EmptyTile::flagged_neighbor_count() const -> int {
	int result = 0;
	_data.for_each_neighbor(pos(), [this, &result](Point p) {
		if (_data.get_tile(p)->flagged()) {
			++result;
		}
	});
	return result;
}

auto EmptyTile::all_neighboring_mines_assumed() const -> bool {
	return mine_neighbor_count() == flagged_neighbor_count();
}

auto EmptyTile::should_click_neighbors() const -> bool {
	return (!clicked() && mine_neighbor_count() == 0)
		|| all_neighboring_mines_assumed();
}

auto EmptyTile::click_neighbors() -> void {
	_data.for_each_neighbor(pos(), [this](Point p) {
		auto neighbor = _data.get_tile(p);
		if (neighbor->clickable()) {
			neighbor->click();
		}
	});
}
