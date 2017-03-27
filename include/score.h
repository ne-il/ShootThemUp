#ifndef __SCORE__
#define __SCORE__

#include "display.h"

typedef struct {
	char *name;
	int score;
}Score;

typedef struct {
	Score high_score[SMAX + 1];
}High_Score;

void set_score(int player_score);

void write_score(High_Score * high_score, FILE * file);

void read_score(High_Score *high_score, FILE * file);

int compare(const void * a, const void * b);

void display_high_score(High_Score * hg, MLV_Font* font);

void display_input_box(char ** name, MLV_Font* font);

#endif