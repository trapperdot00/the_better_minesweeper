#ifndef BOARDDATA_H
#define BOARDDATA_H

#include "GameState.h"
#include "Tiles.h"

struct BoardData {
	int width;
	int height;
	int mine_count;
	GameState state;
	Tiles tiles;
	int clicked = 0;
	int flagged = 0;
};

#endif
