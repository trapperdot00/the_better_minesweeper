#ifndef MINETILE_H
#define MINETILE_H

#include "Tile.h"

#include <string>

class MineTile : public Tile {
public:
	using Tile::Tile;
	auto clicked_rep() const -> std::string override;
	auto is_mine() const -> bool override;
	auto click() -> void override;
private:
	auto lose_game() -> void;
	auto expose_all_mines() -> void;
};

#endif
