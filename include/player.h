#ifndef __PLAYER__
#define __PLAYER__

#include "bullet.h"

typedef struct { 
	Cercle c;
	Vector vect_dir;
	double speed;

	int health;
	int health_max;

	int score;

	MLV_Image * ship;

	Bullets bullets;	/*Tableau d'adresse de balles*/
	unsigned int size_real;
	unsigned int size_max;

	int weapon_lvl;
	int last_shoot_time;

	short is_invincible;
	int invincible_time_left;

}Player;

Player* initialize_player( double x, double y, double radius, double speed, int health_max);

void update_player (Player* p);

int is_dead_player (Player *p);

void destroy_player(Player* p);

void active_invincibility(Player* p);

#endif