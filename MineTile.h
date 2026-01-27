#ifndef MINETILE_H
#define MINETILE_H

#include "Tile.h"

class MineTile : public Tile {
public:
	using Tile::Tile;
	auto clicked_rep() const -> char override;
	auto is_mine() const -> bool override;
};

#endif
