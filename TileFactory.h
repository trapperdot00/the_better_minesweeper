#ifndef TILEFACTORY_H
#define TILEFACTORY_H

class Point;
class BoardData;
class Tile;

#include <memory>

class TileFactory {
public:
	TileFactory(BoardData& data);

	auto create_empty(Point p) const -> std::shared_ptr<Tile>;
	auto create_mine(Point p) const -> std::shared_ptr<Tile>;
private:
	BoardData& _data;
};

#endif
