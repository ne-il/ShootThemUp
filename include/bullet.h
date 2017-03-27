#ifndef __BULLET__
#define __BULLET__ 

#include "cercle.h"
#include <MLV/MLV_all.h>

#ifndef M_PI
#    define M_PI 3.14159265358979323846
#endif

typedef struct {
	Cercle c;
	double speed;
	double angle;	/*in radian*/

	unsigned int index;
	double accel;
	
	int tracking;	/* Yes or No*/
	int timer_tracking;
	int damage; /* -100hp ou -150 hp etc...*/
	int team; /* GOOD_GUYS or BAD_GUYS si deux tab inutile car il faut parcourir les deux dans tout les cas. */
	MLV_Image* img;
}Bullet;

typedef struct {
	Bullet** tab_b;
	int size_real;
	int size_max;
}Bullets; 


double get_angle_shot(Cercle* src, Cercle* target);

void add_bullet(Bullets* bullets, Bullet* b );

void destroy_bullets(Bullets* bullets);

void create_bullets(Bullets* bullets);

int is_bullets_full(Bullets* bullets);

void create_bullet(Bullets* bullets, double x, double y, double radius, double speed, double accel, double angle, int tracking, int dammage, int team, unsigned int index, int bullet_type);

void realloc_bullets(Bullets* bullets);

void swap_b(Bullet ** a, Bullet ** b);

void move_bullet(Bullet* b);

void update_bullets(Bullets* bullets, Cercle* c);

void destroy_bullet(Bullets* bullets, int index_b);

#endif