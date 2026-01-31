#include "TilePlacer.h"

#include "GameContext.h"
#include "Tile.h"
#include "Point.h"

#include <stdexcept>

TilePlacer::TilePlacer(GameContext& ctx, Difficulty diff) :
	_ctx{ctx},
	_diff{diff},
	_factory{ctx},
	_rand{std::random_device{}()},
	_x_gen(0, diff.width - 1),
	_y_gen(0, diff.height - 1)
{
	if (_diff.width * _diff.height < diff.mine_count) {
		throw std::runtime_error{"more mines than tiles"};
	}
}

auto TilePlacer::place_tiles() -> void {
	place_mine_tiles();
	place_empty_tiles();
}

auto TilePlacer::place_mine_tiles() -> void {
	for (int remaining = _diff.mine_count; remaining > 0; ) {
		const Point p{_x_gen(_rand), _y_gen(_rand)};
		if (!_ctx.get_tile(p)) {
			_ctx.set_tile(p, _factory.create_mine(p));
			--remaining;
		}
	}
}

auto TilePlacer::place_empty_tiles() -> void {
	for (int y = 0; y < _diff.height; ++y) {
		for (int x = 0; x < _diff.width; ++x) {
			const Point p{x, y};
			if (!_ctx.get_tile(p)) {
				_ctx.set_tile(p, _factory.create_empty(p));
			}
		}
	}
}
