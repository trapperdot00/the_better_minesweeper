#ifndef TILEFACTORY_H
#define TILEFACTORY_H

#include "FwdDecls.h"

#include <memory>

class TileFactory {
public:
	TileFactory(GameContext& data);

	auto create_empty(Point p) const -> std::shared_ptr<Tile>;
	auto create_mine(Point p) const -> std::shared_ptr<Tile>;
private:
	GameContext& _data;
};

#endif
