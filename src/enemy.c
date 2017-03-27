#include "../include/enemy.h"

Enemy * initialize_enemy (double x, double y, double radius, double speed,int sniper, int homing, int health_max, int index, int enemy_move){
	Enemy* e = NULL;
	MLV_Image* ship = NULL;


	e = (Enemy*) malloc (sizeof(Enemy));

	e->c.x = x;
	e->c.y = y;
	e->c.radius = radius;
	e->health_max = health_max;
	e->health = health_max;
	e->speed = speed;
	e->enemy_move = enemy_move;

	e->sniper = sniper;
	e->homing = homing;

	e->last_shoot_time = 0;
	initialize_vector(&(e->vect_dir));

	switch (enemy_move){
		case RECT :
			ship = MLV_load_image ("src/img/enemyBlack1.png");
			break;

		case SINUS :
			ship = MLV_load_image ("src/img/enemyBlue2.png");
			break;

		default : 
			ship = MLV_load_image ("src/img/enemyRed5.png");
			break;
	}
	if (ship == NULL){
		printf("%d\n",enemy_move);
		fprintf(stderr, "No image was found\n");
		exit(EXIT_FAILURE);
	}
	MLV_resize_image(ship, e->c.radius * 2, e->c.radius * 2);
	e->ship = ship;

	return e;
}

int is_dead_enemy (Enemy *e){
	return (e->health <= 0);
}

int enemy_type (FILE * file){
	int ret, type;
	ret = fscanf(file, "%d\n", &type);
	if (ret == EOF){
		rewind (file);
	}
	return type;
}

void bounce_enemy(Enemy* e){
	static int var_x = 1;
	static int var_y = 1;

	if( e->c.x + e->c.radius >= WIDTH || e->c.x - e->c.radius <= 0  )
		var_x *= -1;

	if( e->c.y + e->c.radius >= HEIGHT || e->c.y - e->c.radius <= 0)
		var_y *= -1;

	e->c.x += e->speed * var_x;
	e->c.y += e->speed * var_y;
}

void move_sinusoide_enemy(Enemy* e){
	e->c.x -= e->speed;
	e->c.y += 5 * sin(e->c.x / 150 ) ;
}

void move_affine_neg_enemy (Enemy * e){
	e->c.x -= e->speed;
	e->c.y += e->c.x / 500;
}

void move_affine_pos_enemy (Enemy * e){
	e->c.x -= e->speed;
	e->c.y += -1 * e->c.x / 500;
}

void move_left_enemy(Enemy* e){
	e->c.x -= e->speed;
} 