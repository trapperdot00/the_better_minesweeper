#ifndef UI_H
#define UI_H

#include "FwdDecls.h"
#include "Point.h"

class UI {
public:
	UI(const GameContext& ctx, const Cursor& cursor, const Timer& timer) :
		_ctx{ctx},
		_cursor{cursor},
		_timer{timer}
	{}

	void draw();
private:
	auto draw_info() -> void;
	auto draw_separator_line() -> void;
	auto draw_header() -> void;
	auto draw_footer() -> void;
	auto draw_rows() -> void;
	auto draw_row(int y) -> void;
	auto draw_tile(Point p) -> void;
private:
	const GameContext& _ctx;
	const Cursor& _cursor;
	const Timer& _timer;
};

#endif
