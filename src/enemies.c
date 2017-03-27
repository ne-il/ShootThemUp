#include "../include/enemies.h"

void create_ennemies(Enemies* enemies){

	if( ( enemies->ship_tab = (Enemy **) malloc ( 10 * sizeof(Enemy*) ) ) == NULL){
		fprintf(stderr, "No memory left for malloc ship_tab\n" );
 		exit(EXIT_FAILURE);
 	}
 	enemies->size_real = 0;
 	enemies->size_max = 10;
 	create_bullets( &(enemies->bullets) );
}

void add_enemy(Enemies* enemies, Enemy* e){
	if ( is_enemies_full(enemies) )
		realloc_enemies(enemies);

	enemies->ship_tab[ enemies->size_real] = e;
	enemies->size_real++; 
}

void realloc_enemies(Enemies* enemies){
	Enemy** tmp = NULL;
	int new_size_max = enemies->size_max * 2;

	tmp = (Enemy **) realloc (enemies->ship_tab, new_size_max * sizeof (Enemy*));
	if ( tmp == NULL){
		fprintf(stderr, "No more memory left\n");
		exit(EXIT_FAILURE);
	}
	enemies->ship_tab = tmp;
	enemies->size_max = new_size_max;
}

int is_enemies_full(Enemies* enemies){
	return (enemies->size_real >= enemies->size_max);
}

void destroy_enemies(Enemies* enemies){
	int i = 0;

	for (i = 0; i < enemies->size_real; i++){
		MLV_free_image( enemies->ship_tab[i]->ship);
		free( enemies->ship_tab[i] ) ;
	}

	free(enemies->ship_tab);
	destroy_bullets(&enemies->bullets);
}



void bounce_enemies(Enemies* enemies){
	int i = 0;

	for( i = 0; i < enemies->size_real; i++)
		bounce_enemy(enemies->ship_tab[i]);
}

void move_enemies(Enemies * enemies){
	int i;
	for (i = 0; i < enemies->size_real; i++){	
		switch(enemies->ship_tab[i]->enemy_move){
			case RECT : 
				move_left_enemy(enemies->ship_tab[i]);
				break;

			case SINUS :
				move_sinusoide_enemy(enemies->ship_tab[i]);
				break;

			case AFFINE_POS :
				move_affine_pos_enemy (enemies->ship_tab[i]);
				break;

			case AFFINE_NEG :
				move_affine_neg_enemy(enemies->ship_tab[i]);
				break;

			default :
				fprintf(stderr, "Error the moveset of the enemy doesn't exist\n");
				break;
		}
	}
}

void enemy_shoot(Enemies* es, Enemy* e, Player* p){
	int tms = 0;

	double angle = 0;
	int shoot_cadency = 2000;	
	tms = MLV_get_time();

	if (( tms - e->last_shoot_time) > shoot_cadency){
		if(e->sniper == TRUE)
			angle = get_angle_shot ( &e->c, &p->c );
		else
			angle = M_PI;

		create_bullet(&es->bullets, e->c.x, e->c.y, 15, 10, 0, angle, e->homing, 100, BAD_GUYS, es->bullets.size_real, 1);
		e->last_shoot_time = tms;
	}
	
}

/*test swap void * */
void swap_e(Enemy ** a, Enemy ** b){
	Enemy* tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

Enemy* get_closest_enemy(Cercle* b_pos, Enemies* enemies ){
	int i = 0;
	double distance = 0;
	double min_distance = 0;
	int index_closest = 0;

	if(enemies->size_real > 0){
		min_distance = get_distance(b_pos, &enemies->ship_tab[0]->c);

		for ( i = 1; i < enemies->size_real; i++){
			distance = get_distance(b_pos, &enemies->ship_tab[i]->c);
			if (distance < min_distance){
				min_distance = distance;
				index_closest = i;
			}
		}

		return enemies->ship_tab[index_closest];
	}

	return NULL;
}

void destroy_enemy(Enemies* enemies, int index_e){
	int last_e = enemies->size_real-1;

	swap_e(&enemies->ship_tab[index_e], &enemies->ship_tab[last_e]);
	MLV_free_image( enemies->ship_tab[last_e]->ship);
	free( enemies->ship_tab[last_e] ) ;
	enemies->size_real -= 1;

}

void generate_random_enemy_right_border(Enemies* enemies, FILE * file_patern){
	int y_rand;
	Enemy* e = NULL;
	float radius, speed;
	int sniper, homing, health, moveset;
	int ret;
	ret = fscanf(file_patern, "%f\n%f\n%d\n%d\n%d\n%d\n", &radius, &speed, &sniper, &homing, &health, &moveset);
	rewind (file_patern);
	if (ret == EOF ){
		fprintf(stderr, "Error : \n" );
	}
	switch (moveset){
		case 0 :
			y_rand = MLV_get_random_integer(50, HEIGHT - 50);
			e = initialize_enemy(WIDTH, y_rand, radius, speed, sniper, homing, health, enemies->size_real, moveset);
			add_enemy(enemies, e);
			break;
		
		case 1 :
			y_rand = MLV_get_random_integer(250, HEIGHT - 250);
			e = initialize_enemy(WIDTH, y_rand, radius, speed, sniper, homing, health, enemies->size_real, moveset);
			add_enemy(enemies, e);
			break;
		
		case 2 :
			y_rand = MLV_get_random_integer(50, HEIGHT - 50);
			if (y_rand < (HEIGHT / 2))
				e = initialize_enemy(WIDTH, y_rand, radius, speed, sniper, homing, health, enemies->size_real, moveset);
			else
				e = initialize_enemy(WIDTH, y_rand, radius, speed, sniper, homing, health, enemies->size_real, AFFINE_POS);
			add_enemy(enemies, e);
			break;

		default : 
			break;
	}
}

void check_enemies_out_of_screen(Enemies* enemies, Player* p ){
	int i = 0;
	int damage_screen_border = 10;
	for( i = 0; i < enemies->size_real; i++){
		if (is_out_of_screen (enemies->ship_tab[i]->c)){
			destroy_enemy(enemies, i);
			p->health -= damage_screen_border;
		}
	}
}


static void update_enemies_bullets(Bullets* bullets_e, Player* p){
	int i;

	for (i = 0; i < bullets_e->size_real;){

		if ( is_out_of_screen(bullets_e->tab_b[i]->c) ){	/*Si la balle sort de l'ecran on la retire*/
			destroy_bullet(bullets_e, i);
		}

		else{
			if(bullets_e->tab_b[i]->tracking == TRUE){
				bullets_e->tab_b[i]->angle = get_angle_shot(&bullets_e->tab_b[i]->c, &p->c); 	/*On donne les cercles de la balle et de la cible;*/
			}

			move_bullet(bullets_e->tab_b[i]);
			i++;
		}
	}
}


static void update_player_bullets(Bullets* bullets_p, Enemies* enemies){
	int i;
	/* double old_angle = 0;*/
	Enemy* closest_enemy = NULL;

	for (i = 0; i < bullets_p->size_real;){

		if ( is_out_of_screen(bullets_p->tab_b[i]->c) ){	/*Si la balle sort de l'ecran on la retire*/
			destroy_bullet(bullets_p, i);
		}

		else{
			if(bullets_p->tab_b[i]->tracking == TRUE){
				/* old_angle = (bullets_p->tab_b[i]->angle * 180) / M_PI ; */
				closest_enemy = get_closest_enemy( &bullets_p->tab_b[i]->c, enemies);	/*On cherche l'enemy le plus proche de cette balle, renvoie NULL si tout les ennemies sont morts.*/
				if(closest_enemy != NULL)
					bullets_p->tab_b[i]->angle = get_angle_shot(&bullets_p->tab_b[i]->c, &closest_enemy->c); 	/*On donne les cercles de la balle et de la cible;*/
			}

			move_bullet(bullets_p->tab_b[i]);
			i++; 
		}
	}
}

void update_all_bullets (Player *p, Enemies *e){
	update_enemies_bullets(&e->bullets, p);
	update_player_bullets(&p->bullets, e);
}