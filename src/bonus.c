#include "../include/bonus.h"

Bonus * create_bonus (double x, double y, int type){
	Bonus * tmp;

	if (NULL == (tmp = (Bonus *) malloc(sizeof(Bonus)) ) ){
		fprintf(stderr, "No memory left\n");
		exit(EXIT_FAILURE);
	}
	tmp->c.x = x;
	tmp->c.y = y;
	tmp->c.radius = 25;

	tmp->type = type;
	if (type == SCORE){
		tmp->img = MLV_load_image("src/img/icons_pow_up_score.png");
		tmp->probability = 3;
	}
	else if (type == LIFE){
		tmp->img = MLV_load_image("src/img/icons_pow_up_health.png");
		tmp->probability = 4;
	}
	else {
		tmp->img = MLV_load_image("src/img/icons_pow_up_amo.png");
		tmp->probability = 5;
	}

	MLV_resize_image(tmp->img, tmp->c.radius * 2 , tmp->c.radius * 2 );

	return tmp;
}

void move_bonus(Bonus * bs){
	bs->c.x -= 5;
}

void destroy_bonus(Bonus * bs){
	MLV_free_image (bs->img);
	free(bs);
}

void apply_bonus(Bonus * bs, Player * p){
	if (bs->type == SCORE){
		p->score += 500;
	}
	else if (bs->type == LIFE){
		p->health += 200;
		if(p->health > p->health_max )
			p->health = p->health_max;
	}
	else{
		if (p->weapon_lvl < 6)
			p->weapon_lvl += 1;
	}
}