#ifndef __CONST__
#define __CONST__

#include <stdlib.h>
#include <stdio.h>

#define BORDER 10
#define WIDTH 1200
#define HEIGHT 705

#define NMAX 64
#define SMAX 9

enum BOOL {
	FALSE, TRUE
};

enum DIR {
	UP, RIGHT, LEFT, DOWN	
};

enum TEAM{
	GOOD_GUYS, BAD_GUYS
};

enum {
	SCORE, WEAPON, LIFE, NONE
};

enum ENEMY_MOVE{
	RECT, SINUS, AFFINE_NEG, AFFINE_POS
};

enum ENEMY_TYPE{
	EASY, MEDIUM, HARD
};

#endif