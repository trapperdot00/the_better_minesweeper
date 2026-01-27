#ifndef TILES_H
#define TILES_H

class Tile;
struct Point;

#include <vector>
#include <memory>

class Tiles {
public:
	Tiles(int width, int height);

	auto width() const -> int { return _width; }
	auto height() const -> int { return _height; }
	auto size() const -> int { return _width * _height; }

	auto get_tile(Point p) const -> std::shared_ptr<Tile>;
	auto get_tile(int idx) const -> std::shared_ptr<Tile>;
	auto set_tile(Point p, std::shared_ptr<Tile> tile) -> void;
	auto set_tile(int idx, std::shared_ptr<Tile> tile) -> void;

	auto in_range(Point p) const -> bool;
	auto in_range(int idx) const -> bool;

	auto to_index(Point p) const -> int;
	auto to_point(int idx) const -> Point;
private:
	int _width;
	int _height;
	std::vector<std::shared_ptr<Tile>> _data;
};

#endif
