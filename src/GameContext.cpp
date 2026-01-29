#include "GameContext.h"

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

auto GameContext::get_tile(Point p) const -> std::shared_ptr<Tile> {
	return _tiles.get_tile(p);
}

auto GameContext::set_tile(Point p, std::shared_ptr<Tile> tile) -> void {
	_tiles.set_tile(p, tile);
}

auto GameContext::for_each(std::function<void(Point)> f) const -> void {
	_tiles.for_each(f);
}

auto GameContext::for_each_neighbor
(Point p, std::function<void(Point)> f) const -> void {
	_tiles.for_each_neighbor(p, f);
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

auto GameContext::increment_mine_count() -> void {
	++_mine_count;
}

auto GameContext::decrement_mine_count() -> void {
	--_mine_count;
}

auto GameContext::increment_clicked_count() -> void {
	++_clicked;
}

auto GameContext::decrement_clicked_count() -> void {
	--_clicked;
}

auto GameContext::increment_flagged_count() -> void {
	++_flagged;
}

auto GameContext::decrement_flagged_count() -> void {
	--_flagged;
}
