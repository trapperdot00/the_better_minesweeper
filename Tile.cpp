#include "Tile.h"

#include "BoardData.h"

Tile::Tile(BoardData& data, Point pos) :
	_data{data},
	_pos{pos}
{}

auto Tile::rep() const -> char {
	if (clicked()) {
		return clicked_rep();
	} else if (flagged()) {
		return flagged_rep();
	} else {
		return untouched_rep();
	}
}

auto Tile::click() -> void {
	if (clicked() || flagged()) return;
	_clicked = true;
}

auto Tile::flag() -> void {
	if (clicked()) return;
	_flagged = !_flagged;
}

auto Tile::clicked() const -> bool {
	return _clicked;
}

auto Tile::flagged() const -> bool {
	return _flagged;
}

auto Tile::untouched_rep() const -> char {
	return '.';
}

auto Tile::flagged_rep() const -> char {
	return 'P';
}
