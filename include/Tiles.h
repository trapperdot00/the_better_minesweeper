#ifndef TILES_H
#define TILES_H

class Tile;
struct Point;

#include <vector>
#include <memory>
#include <functional>

class Tiles {
public:
	Tiles(int width, int height);

	auto width() const -> int { return _width; }
	auto height() const -> int { return _height; }
	auto size() const -> int { return _width * _height; }

	auto get_tile(Point p) const -> std::shared_ptr<Tile>;
	auto set_tile(Point p, std::shared_ptr<Tile> tile) -> void;

	auto for_each_neighbor
		(Point p, std::function<void(Point)> f) const -> void;

	auto in_range(Point p) const -> bool;
private:
	auto to_index(Point p) const -> int;
	auto clamp_x(int x) const -> int;
	auto clamp_y(int y) const -> int;
	auto neighbor_min_x(Point p) const -> int;
	auto neighbor_max_x(Point p) const -> int;
	auto neighbor_min_y(Point p) const -> int;
	auto neighbor_max_y(Point p) const -> int;
private:
	int _width;
	int _height;
	std::vector<std::shared_ptr<Tile>> _data;
};

#endif
