#ifndef __ANIMATIONS__
#define __ANIMATIONS__ 

#include <MLV/MLV_all.h>
#include "animation.h"

typedef struct{
	Animation** anim_tab;
	
	int size_real;
	int size_max;

	MLV_Image* spritesheet;

} Animations;

void initialize_animations(Animations * anims);

void add_animation(Animations* anims, int x, int y, int diameter);

int is_anim_tab_full(Animations* anims);

void realloc_anim_tab(Animations* anims);

void display_animations(Animations* anims);

void destroy_animations(Animations* anims);

void destroy_animation(Animations* anims, int index );
#endif
