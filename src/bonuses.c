#include "../include/bonuses.h"

void create_bonuses(Bonuses * bses){

	if ((bses->bonuses = (Bonus **) malloc (16 * sizeof(Bonus *))) == NULL){
		fprintf(stderr, "No memory left for malloc bonuses\n" );
		exit(EXIT_FAILURE);
	}
	bses->size_real = 0;
	bses->size_max = 10;
}

void add_bonus(Bonuses * bses, Bonus * bs){
	if (is_bonuses_full(bses))
		realloc_bonuses(bses);

	bses->bonuses[bses->size_real] = bs;
	bses->size_real += 1;
}

void realloc_bonuses(Bonuses * bses){
	Bonus **  tmp = NULL;

	bses->size_max *= 2;

	if (NULL == (tmp =  (Bonus **) realloc (bses->bonuses, bses->size_max * sizeof(Bonus *)))){
		fprintf(stderr, "No more memory left\n");
		exit(EXIT_FAILURE);
	}

	bses->bonuses = tmp;
}

int is_bonuses_full(Bonuses * bses){
	return (bses->size_real >= bses->size_max);
}

void destroy_bonuses(Bonuses * bses){
	int i;

	for(i = 0; i < bses->size_real; i++){
		destroy_bonus(bses->bonuses[i]);
	}

	free(bses->bonuses);
}

void move_bonuses(Bonuses * bses){
	int i;

	for(i = 0; i < bses->size_real; i++)
		move_bonus(bses->bonuses[i]);
}

void check_bonuses_out_of_screen(Bonuses * bses){
	int i;

	for(i = 0; i < bses->size_real; i++)
		if (is_out_of_screen(bses->bonuses[i]->c))
			destroy_bonus_in_bonuses(bses, i);
}

void destroy_bonus_in_bonuses(Bonuses * bses, int index){
	swap_bonus(&bses->bonuses[index], &bses->bonuses[bses->size_real - 1]);
	destroy_bonus(bses->bonuses[bses->size_real - 1]);
	bses->size_real -= 1;
}

void swap_bonus(Bonus ** a, Bonus ** b){
	Bonus* tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void update_bonuses(Bonuses * bses){
	check_bonuses_out_of_screen(bses);
	move_bonuses(bses);
}

static int rand_bonus(){
	int rd;

	rd = MLV_get_random_integer(0, 2);

	if (!rd){
		rd = MLV_get_random_integer(0, 30);
		if (rd < 5)
			return LIFE;
		else if (rd >= 5 && rd < 15)
			return WEAPON;
		else 
			return SCORE;
	}
	return NONE;
}

void bonus (Bonuses * bses, Cercle *c){
	int rd;
	rd = rand_bonus();
	Bonus * bs;

	if (rd != NONE){
		bs = create_bonus (c->x, c->y, rd);
		add_bonus(bses, bs);
	}
	return;
}