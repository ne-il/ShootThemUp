#include "../include/animation.h"

Animation* create_animation(int x, int y, int diameter){
	Animation* anim = NULL;

	anim = (Animation*) calloc(1, sizeof(Animation));
	if (NULL == anim){
		fprintf(stderr, "Erreur d'allocation d'une animation\n" );
		exit(EXIT_FAILURE);
	}
	anim->x = x;
	anim->y = y;
	anim->diameter = diameter;
	anim->index = 0;

	return anim;
}

void swap_animation(Animation** a, Animation** b){
	Animation* tmp;
	tmp = (*a);
	(*a) = (*b);
	(*b) = tmp;
}
