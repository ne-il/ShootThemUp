#ifndef __BONUSES__
#define __BONUSES__

#include "bonus.h"

typedef struct {
	Bonus ** bonuses; 
	int size_real;
	int size_max;
}Bonuses;

void create_bonuses(Bonuses * bses);

void add_bonus(Bonuses * bses, Bonus * bs);

void realloc_bonuses(Bonuses * bses);

int is_bonuses_full(Bonuses * bses);

void destroy_bonuses(Bonuses * bses);

void move_bonuses(Bonuses * bses);

void check_bonuses_out_of_screen(Bonuses * bses);

void destroy_bonus_in_bonuses(Bonuses * bses, int index);

void swap_bonus(Bonus ** a, Bonus ** b);

void update_bonuses(Bonuses * bses);

void bonus (Bonuses * bses, Cercle *c);

#endif