#ifndef GAME_H
#define GAME_H

#include "Point.h"
#include "Cursor.h"
#include "GameContext.h"
#include "Difficulty.h"
#include "TilePlacer.h"
#include "UI.h"

class Game {
public:
	Game(Difficulty diff);

	auto play() -> void;
private:
	auto print() -> void;
	auto game_ended() const -> bool;
private:
	GameContext _ctx;
	Cursor _cur;
	TilePlacer _placer;
	UI _ui;
};

#endif
