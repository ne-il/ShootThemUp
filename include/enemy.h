#ifndef __ENEMY__
#define __ENEMY__

#include <MLV/MLV_all.h>

#include "cercle.h"

typedef struct {
	Cercle c;
	Vector vect_dir;
	double speed;
	int enemy_move;
	
	int health_max;
	int health;

	int sniper;
	int homing;

	MLV_Image* ship;

	int index;
	int last_shoot_time;

}Enemy;

Enemy * initialize_enemy (double x, double y, double radius, double speed,int sniper, int homing, int health_max, int index, int enemy_move);

int is_dead_enemy (Enemy *e);

int enemy_type (FILE * file);

void bounce_enemy(Enemy* e);

void move_left_enemy(Enemy* e);

void move_affine_pos_enemy (Enemy * e);

void move_affine_neg_enemy (Enemy * e);

void move_sinusoide_enemy(Enemy* e);

#endif