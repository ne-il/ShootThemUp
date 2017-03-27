#include "../include/input.h"

static void shoot_pattern_1(Player* p){
	int small_rad;
	double x1, y1;

	double speed = 15;

	small_rad = 10;
	x1 = p->c.x + p->c.radius ;
	y1 = p->c.y;

	create_bullet(&p->bullets, x1, y1, small_rad, speed, 0, 2*M_PI, FALSE, 100, GOOD_GUYS, p->bullets.size_real, 1) ;
}

static void shoot_pattern_2(Player* p){
	int decal_y, small_rad;
	double x1, y1, x2, y2;

	double speed = 15;

	small_rad = 10;
	decal_y = 10;

	x1 = p->c.x + p->c.radius ;
	y1 = p->c.y - decal_y;

	x2 = x1;
	y2 = p->c.y + decal_y;


	create_bullet(&p->bullets, x1, y1, small_rad, speed, 0, 2*M_PI, FALSE, 100, GOOD_GUYS, p->bullets.size_real, 1) ;
	create_bullet(&p->bullets, x2, y2, small_rad, speed, 0, 2*M_PI, FALSE, 100, GOOD_GUYS, p->bullets.size_real, 1) ;
}

static void shoot_pattern_3(Player* p){
	int decal_y, small_rad;
	double x1, y1, x2, y2, x3, y3;

	double speed = 15;

	small_rad = 10;
	decal_y = 15;

	x1 = p->c.x + p->c.radius ;
	y1 = p->c.y - decal_y;

	x2 = x1;
	y2 = p->c.y;

	x3 = x1;
	y3 = p->c.y + decal_y;


	create_bullet(&p->bullets, x1, y1, small_rad, speed, 0, 2*M_PI, FALSE, 100, GOOD_GUYS, p->bullets.size_real, 1) ;
	create_bullet(&p->bullets, x2, y2, small_rad, speed, 0, 2*M_PI, FALSE, 100, GOOD_GUYS, p->bullets.size_real, 1) ;
	create_bullet(&p->bullets, x3, y3, small_rad, speed, 0, 2*M_PI, FALSE, 100, GOOD_GUYS, p->bullets.size_real, 1) ;

}

static void shoot_pattern_4(Player* p){
	int decal_y, big_rad;
	double x1, y1, x2, y2;

	double speed = 15;

	big_rad = 20;
	decal_y = 15;

	x1 = p->c.x + p->c.radius ;
	y1 = p->c.y - decal_y;

	x2 = x1;
	y2 = p->c.y + decal_y;


	create_bullet(&p->bullets, x1, y1, big_rad, speed, 0, 2*M_PI, FALSE, 200, GOOD_GUYS, p->bullets.size_real, 1) ;
	create_bullet(&p->bullets, x2, y2, big_rad, speed, 0, 2*M_PI, FALSE, 200, GOOD_GUYS, p->bullets.size_real, 1) ;
}

static void shoot_pattern_5(Player* p){
	int very_big_rad;
	double x1, y1;

	double speed = 15;

	very_big_rad = 40;
	

	x1 = p->c.x + p->c.radius*3 ;
	y1 = p->c.y ;



	create_bullet(&p->bullets, x1, y1, very_big_rad, speed, 0, 2*M_PI, FALSE, 150, GOOD_GUYS, p->bullets.size_real, 1) ;
}



static void shoot_pattern_6(Player* p){
	int big_rad;
	double x1, y1, x2, y2, x3, y3;

	double speed = 15;

	big_rad = 15;

	x1 = p->c.x + p->c.radius ;
	y1 = p->c.y ;

	x2 = p->c.x;
	y2 = p->c.y + p->c.radius;

	x3 =  x2;
	y3 = p->c.y - p->c.radius;

	
	create_bullet(&p->bullets, x1, y1, big_rad, speed, 0, 2*M_PI, FALSE, 100, GOOD_GUYS, p->bullets.size_real, 1) ;
	create_bullet(&p->bullets, x2, y2, big_rad, speed, 0, 2*M_PI, TRUE, 100, GOOD_GUYS, p->bullets.size_real, 0) ;
	create_bullet(&p->bullets, x3, y3, big_rad, speed, 0, 2*M_PI, FALSE, 100, GOOD_GUYS, p->bullets.size_real, 0) ;
}

void read_input(Player* p, MLV_Sound* shoot_sound){
	int tms = 0;
	int shoot_cadency = 100;

	set_vect_nul(&(p->vect_dir));

	if ( MLV_get_keyboard_state( MLV_KEYBOARD_s ) == MLV_PRESSED){				
		add_vect(&(p->vect_dir) , 0 , -(p->speed) );				
	}

	if ( MLV_get_keyboard_state( MLV_KEYBOARD_z ) == MLV_PRESSED){
		add_vect(&(p->vect_dir) , 0 , (p->speed) );
	}


	if ( MLV_get_keyboard_state( MLV_KEYBOARD_d ) == MLV_PRESSED){			
		add_vect(&(p->vect_dir) , (p->speed) , 0 );			
	}

	if ( MLV_get_keyboard_state( MLV_KEYBOARD_q ) == MLV_PRESSED){		
		add_vect(&(p->vect_dir) , -(p->speed) , 0 );	
	}

	/* GERER LA CADENCE DES TIRS DANS LA CONDITION EN DESSOUS!!! UTILISER MEMOISATION POUR LA VARIABLE DE TEMPS ???*/

	if (MLV_get_keyboard_state( MLV_KEYBOARD_SPACE ) == MLV_PRESSED){

		tms = MLV_get_time();
		if ((tms - p->last_shoot_time) > shoot_cadency){
			
			MLV_play_sound(shoot_sound, 0.3);

			if ( is_bullets_full(&(p->bullets)) )
				realloc_bullets( &(p->bullets) );
			
			switch(p->weapon_lvl){
				case 1:
					shoot_pattern_1(p);				
					break;

				case 2:
					shoot_pattern_2(p);					
					break;

				case 3:
					shoot_pattern_3(p);					
					break;

				case 4:
					shoot_pattern_4(p);					
					break;	

				case 5:
					shoot_pattern_5(p);
					break;

				case 6:
					shoot_pattern_6(p);					
					break;

			
			}
			p->last_shoot_time = tms;
		}
	}
}

int quit(){
	if ( MLV_get_keyboard_state( MLV_KEYBOARD_ESCAPE ) == MLV_PRESSED){
		return FALSE;
	}
	return TRUE;
}