#include "MineTile.h"

#include "GameContext.h"

MineTile::MineTile(GameContext& data, Point pos,
		AnsiColor flagged_color,
		AnsiColor clicked_color) :
	Tile{data, pos, flagged_color},
	_clicked_color{clicked_color}
{}

auto MineTile::is_mine() const -> bool {
	return true;
}

auto MineTile::clicked_rep() const -> std::string {
	return _clicked_color.wrap("*");
}

auto MineTile::click(Tile*) -> void {
	Tile::click();
	if (clicked() && _data.state() != GameState::lost) {
		lose_game();
	}
}

auto MineTile::lose_game() -> void {
	_data.set_state(GameState::lost);
	expose_all_mines();
}

auto MineTile::expose_all_mines() -> void {
	_data.for_each([this](auto tile) {
		if (tile->is_mine()) {
			tile->click();
		}
	});
}
