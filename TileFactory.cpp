#include "TileFactory.h"

#include "BoardData.h"
#include "EmptyTile.h"
#include "MineTile.h"


TileFactory::TileFactory(BoardData& data) :
	_data{data}
{}

auto TileFactory::create_empty(Point p) const -> std::shared_ptr<Tile> {
	return std::make_shared<EmptyTile>(_data, p);
}

auto TileFactory::create_mine(Point p) const -> std::shared_ptr<Tile> {
	return std::make_shared<MineTile>(_data, p);
}
