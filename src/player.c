#include "../include/player.h"

Player* initialize_player( double x, double y, double radius, double speed, int health_max){
	Player* p =NULL;
	MLV_Image* tmp_ship = NULL;

	p = (Player*) malloc (sizeof(Player));
	p->c.x = x;
	p->c.y = y;
	p->c.radius = radius;
	initialize_vector(&(p->vect_dir));
	p->speed = speed;
	p->weapon_lvl = 1;
	p->score = 0;
	
	p->health_max = health_max;
	p->health = health_max;
	p->last_shoot_time = 0;
	create_bullets(&p->bullets);

	p->is_invincible = FALSE;
	p->invincible_time_left = 0;

	tmp_ship = MLV_load_image ("src/img/playerRight.png");
	if (tmp_ship == NULL){
		fprintf(stderr, "No image was found\n");
		exit(EXIT_FAILURE);
	}
	MLV_resize_image(tmp_ship, p->c.radius * 2, p->c.radius * 2);
	p->ship = tmp_ship;

	return p;
}

void active_invincibility(Player* p){
	p->is_invincible = TRUE;
	p->invincible_time_left = 1000;
}

void check_border_collision(Player* p ){
	int futur_x = 0;
	int futur_y = 0;

	futur_x = ( p->c.x ) + ( p->vect_dir.x );
	futur_y = ( p->c.y ) - ( p->vect_dir.y );

	if( (futur_x - p->c.radius) < 0 || ( futur_x + p->c.radius ) > WIDTH ){
		 p->vect_dir.x = 0;
	}
	if( (futur_y - p->c.radius) < 0 || ( futur_y + p->c.radius ) > HEIGHT ){
		p->vect_dir.y = 0;
	}

}

void update_player (Player* p){
	static int last_time = 0;
	int delta = 0;

	delta = MLV_get_time() ;
	if(p->is_invincible == TRUE){
		p->invincible_time_left -= delta - last_time;
		if ( p->invincible_time_left < 0){
			p->invincible_time_left = 0;
			p->is_invincible = FALSE;
		}
	}
	
	/*If the ship fly in diagonal, it could be too fast. So we divide the coordinates of the vector by squareroot(2) so the norme of the diagonal vector would be the same than horizontal or vertical*/
	if(p->vect_dir.x && p->vect_dir.y ){
		p->vect_dir.x /= sqrt(2);
		p->vect_dir.y /= sqrt(2);		
	}

	check_border_collision(p);
	
	p->c.x += p->vect_dir.x ;
	p->c.y -= p->vect_dir.y ;

	last_time = delta;
}


int is_dead_player (Player *p){
	return (p->health <= 0);
}

void destroy_player(Player* p){

	destroy_bullets(&p->bullets);
	MLV_free_image(p->ship);
	free(p);
}