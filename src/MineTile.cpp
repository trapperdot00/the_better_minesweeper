#include "MineTile.h"

#include "BoardData.h"

auto MineTile::is_mine() const -> bool {
	return true;
}

auto MineTile::clicked_rep() const -> char {
	return '*';
}

auto MineTile::click() -> void {
	Tile::click();
	if (clicked() && _data.state != GameState::lost) {
		lose_game();
	}
}

auto MineTile::lose_game() -> void {
	_data.state = GameState::lost;
	expose_all_mines();
}

auto MineTile::expose_all_mines() -> void {
	_data.tiles.for_each([this](Point p) {
		auto tile = _data.tiles.get_tile(p);
		if (tile->is_mine()) {
			tile->click();
		}
	});
}
