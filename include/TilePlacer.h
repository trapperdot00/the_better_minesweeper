#ifndef TILEPLACER_H
#define TILEPLACER_H

#include "FwdDecls.h"
#include "TileFactory.h"
#include "Difficulty.h"

#include <random>

class TilePlacer {
public:
	TilePlacer(GameContext& ctx, Difficulty diff);

	auto place_tiles() -> void;
private:
	auto place_mine_tiles() -> void;
	auto place_empty_tiles() -> void;
private:
	GameContext& _ctx;
	Difficulty _diff;
	TileFactory _factory;
	std::mt19937 _rand;
	std::uniform_int_distribution<int> _x_gen;
	std::uniform_int_distribution<int> _y_gen;
};

#endif
