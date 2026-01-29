#ifndef GAMECONTEXT_H
#define GAMECONTEXT_H

#include "Point.h"
#include "GameState.h"
#include "Tiles.h"

#include <memory>
#include <functional>

class GameContext {
public:
	GameContext(int width, int height);

	auto width() const -> int;
	auto height() const -> int;
	auto size() const -> int;

	auto get_tile(Point p) const -> std::shared_ptr<Tile>;
	auto set_tile(Point p, std::shared_ptr<Tile> tile) -> void;

	auto for_each(std::function<void(Point)> f) const -> void;
	auto for_each_neighbor
		(Point p, std::function<void(Point)> f) const -> void;

	auto in_range(Point p) const -> bool;

	auto get_state() const -> GameState;
	auto set_state(GameState state) -> void;

	auto flagged_count() const -> int { return _flagged; }
	auto clicked_count() const -> int { return _clicked; }
	auto mine_count() const -> int { return _mine_count; }

	auto increment_mine_count() -> void;
	auto decrement_mine_count() -> void;
	auto increment_clicked_count() -> void;
	auto decrement_clicked_count() -> void;
	auto increment_flagged_count() -> void;
	auto decrement_flagged_count() -> void;
private:
	int _mine_count = 0;
	int _clicked = 0;
	int _flagged = 0;
	GameState _state = GameState::ready;
	Tiles _tiles;
};

#endif
