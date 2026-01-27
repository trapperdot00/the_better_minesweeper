#ifndef DIFFICULTY_H
#define DIFFICULTY_H

struct Difficulty {
	const static Difficulty beginner;
	const static Difficulty intermediate;
	const static Difficulty expert;

	int width;
	int height;
	int mine_count;
};

#endif
