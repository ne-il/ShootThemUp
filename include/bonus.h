#ifndef __BONUS__
#define __BONUS__ 

#include "enemies.h"

typedef struct {
	Cercle c;
	MLV_Image * img;
	short probability;
	int type;
}Bonus;


Bonus * create_bonus (double x, double y, int type);

void move_bonus(Bonus * bs);

void destroy_bonus(Bonus * bs);

void apply_bonus(Bonus * bs, Player * p);

#endif