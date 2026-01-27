#ifndef POINT_H
#define POINT_H

struct Point {
	int x;
	int y;
};

inline bool operator==(const Point& a, const Point& b) {
	return a.x == b.x && a.y == b.y;
}

inline bool operator!=(const Point& a, const Point& b) {
	return !(a == b);
}

#endif
