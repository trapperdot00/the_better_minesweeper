#include "TileFactory.h"

#include "GameContext.h"
#include "AnsiColor.h"
#include "EmptyTile.h"
#include "MineTile.h"

TileFactory::TileFactory(GameContext& data) :
	_data{data}
{}

auto TileFactory::create_empty(Point p) const -> std::shared_ptr<Tile> {
	return std::make_shared<EmptyTile>(
		_data, p, AnsiColor::yellow, AnsiColor::cyan
	);
}

auto TileFactory::create_mine(Point p) const -> std::shared_ptr<Tile> {
	return std::make_shared<MineTile>(
		_data, p, AnsiColor::yellow, AnsiColor::red
	);
}
