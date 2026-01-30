#include "Tile.h"

#include "GameContext.h"

Tile::Tile(GameContext& data, Point pos,
		AnsiColor flagged_color) :
	_data{data},
	_pos{pos},
	_flagged_color{flagged_color}
{}

auto Tile::rep() const -> std::string {
	if (clicked()) {
		return clicked_rep();
	} else if (flagged()) {
		return flagged_rep();
	} else {
		return untouched_rep();
	}
}

auto Tile::click() -> void {
	if (clickable()) {
		_clicked = true;
		_data.increment_clicked_count();
	}
}

auto Tile::flag() -> void {
	if (flaggable()) {
		_flagged = !_flagged;
		if (_flagged) {
			_data.increment_flagged_count();
		} else {
			_data.decrement_flagged_count();
		}
	}
}

auto Tile::clickable() const -> bool {
	return !clicked() && !flagged();
}

auto Tile::flaggable() const -> bool {
	return !clicked();
}

auto Tile::clicked() const -> bool {
	return _clicked;
}

auto Tile::flagged() const -> bool {
	return _flagged;
}

auto Tile::untouched_rep() const -> std::string {
	return ".";
}

auto Tile::flagged_rep() const -> std::string {
	return _flagged_color.wrap("P");
}
