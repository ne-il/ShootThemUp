#ifndef __COLLISION__
#define __COLLISION__

#include "bonuses.h"
#include "animations.h"


int is_collision(Cercle* c1, Cercle* c2);

void check_all_collision(Player *p, Enemies *es, Bonuses * bses, Animations* anims, MLV_Sound* explosion_sound);

#endif