#include "GameContext.h"

#include "Tile.h"

GameContext::GameContext(int width, int height) :
	_tiles{width, height}
{}

auto GameContext::width() const -> int {
	return _tiles.width();
}

auto GameContext::height() const -> int {
	return _tiles.height();
}

auto GameContext::size() const -> int {
	return _tiles.size();
}

auto GameContext::mine_count() const -> int {
	int result = 0;
	for_each([&result, this](auto tile) {
		if (tile->is_mine()) {
			++result;
		}
	});
	return result;
}

auto GameContext::clicked_count() const -> int {
	int result = 0;
	for_each([&result, this](auto tile) {
		if (tile->clicked()) {
			++result;
		}
	});
	return result;
}

auto GameContext::flagged_count() const -> int {
	int result = 0;
	for_each([&result, this](auto tile) {
		if (tile->flagged()) {
			++result;
		}
	});
	return result;
}

auto GameContext::remaining_tiles() const -> int {
	return size() - clicked_count() - flagged_count();
}

auto GameContext::remaining_mines() const -> int {
	return mine_count() - flagged_count();
}

auto GameContext::get_tile(Point p) const -> std::shared_ptr<Tile> {
	return _tiles.get_tile(p);
}

auto GameContext::set_tile(Point p, std::shared_ptr<Tile> tile) -> void {
	_tiles.set_tile(p, tile);
}

auto GameContext::for_each(std::function<void(std::shared_ptr<Tile>)> f) const -> void {
	_tiles.for_each([f, this](Point pos) {
		f(_tiles.get_tile(pos));
	});
}

auto GameContext::for_each_neighbor
(Point p, std::function<void(std::shared_ptr<Tile>)> f) const -> void {
	_tiles.for_each_neighbor(p, [f, this](Point pos) {
		f(_tiles.get_tile(pos));
	});
}

auto GameContext::in_range(Point p) const -> bool {
	return _tiles.in_range(p);
}

auto GameContext::state() const -> GameState {
	return _state;
}

auto GameContext::set_state(GameState new_state) -> void {
	_state = new_state;
}
