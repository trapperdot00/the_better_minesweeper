add_executable(Minesweeper
	main.cpp
	Game.cpp
	UI.cpp
	Timer.cpp
	Tile.cpp
	EmptyTile.cpp
	MineTile.cpp
	TileFactory.cpp
	TilePlacer.cpp
	Tiles.cpp
	GameContext.cpp
	Difficulty.cpp
	AnsiColor.cpp
	Cursor.cpp
)

target_compile_features(Minesweeper PRIVATE cxx_std_20)

target_include_directories(Minesweeper
	PRIVATE ../include
)
