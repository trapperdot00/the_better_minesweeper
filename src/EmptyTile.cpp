#include "EmptyTile.h"

#include "BoardData.h"

auto to_char(int i) -> char {
	if (i < 0) return '0';
	if (i > 9) return '9';
	return '0' + static_cast<char>(i);
}

auto EmptyTile::clicked_rep() const -> char {
	return (mine_neighbor_count() > 0)
		? to_char(mine_neighbor_count())
		: ' ';
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
	_data.tiles.for_each_neighbor(pos(), [&result](Point) { ++result; });
	return result;
}

auto EmptyTile::mine_neighbor_count() const -> int {
	int result = 0;
	_data.tiles.for_each_neighbor(pos(), [this, &result](Point p) {
		if (_data.tiles.get_tile(p)->is_mine()) {
			++result;
		}
	});
	return result;
}

auto EmptyTile::clicked_neighbor_count() const -> int {
	int result = 0;
	_data.tiles.for_each_neighbor(pos(), [this, &result](Point p) {
		if (_data.tiles.get_tile(p)->clicked()) {
			++result;
		}
	});
	return result;
}

auto EmptyTile::flagged_neighbor_count() const -> int {
	int result = 0;
	_data.tiles.for_each_neighbor(pos(), [this, &result](Point p) {
		if (_data.tiles.get_tile(p)->flagged()) {
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
	_data.tiles.for_each_neighbor(pos(), [this](Point p) {
		auto neighbor = _data.tiles.get_tile(p);
		if (neighbor->clickable()) {
			neighbor->click();
		}
	});
}
