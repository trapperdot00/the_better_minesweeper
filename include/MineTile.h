#ifndef MINETILE_H
#define MINETILE_H

#include "Tile.h"
#include "Point.h"
#include "AnsiColor.h"

#include <string>

class MineTile : public Tile {
public:
	MineTile(GameContext& data, Point pos,
			AnsiColor flagged_color,
			AnsiColor clicked_color);

	auto clicked_rep() const -> std::string override;
	auto is_mine() const -> bool override;
	auto click(Tile* prev = nullptr) -> void override;
private:
	auto lose_game() -> void;
	auto expose_all_mines() -> void;
private:
	AnsiColor _clicked_color;
};

#endif
