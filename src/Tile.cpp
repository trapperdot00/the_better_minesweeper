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
	if (clickable()) {
		_clicked = true;
		++_data.clicked;
	}
}

auto Tile::flag() -> void {
	if (flaggable()) {
		_flagged = !_flagged;
		if (_flagged) {
			++_data.flagged;
		} else {
			--_data.flagged;
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

auto Tile::untouched_rep() const -> char {
	return '.';
}

auto Tile::flagged_rep() const -> char {
	return 'P';
}
