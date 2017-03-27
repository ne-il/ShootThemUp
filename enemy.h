#ifndef __ENEMY__
#define __ENEMY__

#include "cercle.h"
#include "vector.h"
#include <MLV/MLV_all.h>
#include <math.h>
typedef struct {
	Cercle c;
	Vector vect_dir;
	double speed;
	
	int health_max;
	int health;

	int sniper;
	int homing;

	MLV_Image* ship;

	int index;

}Enemy;

Enemy * initialize_enemy (double x, double y, double radius, double speed, int sniper, int homing, int health_max, int index);

int is_dead_enemy (Enemy *e);

void bounce_enemy(Enemy* e);

void move_left_enemy(Enemy* e);


#endif