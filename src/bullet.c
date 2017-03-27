#include "../include/bullet.h"

void create_bullets(Bullets* bullets){	
	bullets->size_max = 10;

	bullets->tab_b = (Bullet **) malloc ( bullets->size_max * sizeof(Bullet*));

	if ( bullets->tab_b == NULL){
		fprintf(stderr, "No more memory left\n");
		exit(EXIT_FAILURE);
	}

	bullets->size_real = 0;
	bullets->size_max = 10;
}

void add_bullet(Bullets* bullets, Bullet* b ){

	if ( is_bullets_full( bullets) )
		realloc_bullets( bullets );

	bullets->tab_b[bullets->size_real] = b;
	bullets->size_real ++;
}

void realloc_bullets(Bullets* bullets){
 	Bullet** tmp = NULL;
 	int new_size_max = bullets->size_max * 2;
 	

 	tmp = (Bullet **) realloc (bullets->tab_b, new_size_max * sizeof (Bullet*));
 	if (NULL == tmp){
 		fprintf(stderr, "No memory left for realloc bullets\n" );
 		exit(EXIT_FAILURE);
 	}
 	
 	bullets->tab_b = tmp;
 	bullets->size_max = new_size_max;
}

void destroy_bullets(Bullets* bullets){
	int i = 0;
	for (i = bullets->size_real - 1; i >= 0 ; i--){
		MLV_free_image( bullets->tab_b[i]->img );
		free( bullets->tab_b[i] ) ;
	}
	free (bullets->tab_b);
}

int is_bullets_full(Bullets* bullets){
	return (bullets->size_real >= bullets->size_max);
}


/*-----------------------------------------------------------------------------------------------------*/




void create_bullet(Bullets* bullets, double x, double y, double radius, double speed, double accel, double angle, int tracking, int dammage, int team, unsigned int index, int bullet_type){
	Bullet* b = NULL;

	b = (Bullet*) malloc( sizeof(Bullet));
	if (NULL == b){
		fprintf(stderr, "No more memory left for more bullets\n");
		exit(EXIT_FAILURE);
	}

	b->c.x = x;
	b->c.y = y;
	b->c.radius = radius;
	
	b->speed = (tracking) ? speed / 2 : speed;
	b->accel = accel;
	
	b->angle = angle;
	b->tracking = tracking;
	b->damage = dammage;
	b->team = team;
	b->index = index;

	b->timer_tracking = (tracking) ? 180 : 0;

	switch(tracking){
		case TRUE:
			b->img = MLV_load_image("src/img/laserPurple.png");
			break;	

		case  FALSE:
			switch (team) {
				case GOOD_GUYS :
					b->img = MLV_load_image("src/img/laserBlue.png");
					break;

				case BAD_GUYS :
					b->img = MLV_load_image("src/img/laserRed.png");
					break;
			}
	}
	if (b->img == NULL){
		fprintf(stderr, "Error : Image can't be opened\n");
		exit(EXIT_FAILURE);
	}

	MLV_resize_image(b->img, b->c.radius * 2, b->c.radius );

	add_bullet(bullets, b);
}

double get_angle_shot(Cercle* src, Cercle* target){
	double correction = 0;
	if( src->x - target->x > 0)
		correction = M_PI;

	return atan( -(src->y - target->y) / (src->x - target->x) ) + correction ;
}

void update_bullets(Bullets* bullets, Cercle* c){
	int i;

	for (i = 0; i < bullets->size_real;){

		if ( is_out_of_screen(bullets->tab_b[i]->c) ){	/*Si la balle sort de l'ecran on la retire*/
			destroy_bullet(bullets, i);
		}

		else{

			if(bullets->tab_b[i]->tracking == TRUE){
				if (bullets->tab_b[i]->timer_tracking <= 0){
					destroy_bullet(bullets, i);
printf("On detruit la chercheuse\n");
				}
				else {
					bullets->tab_b[i]->angle = get_angle_shot(&bullets->tab_b[i]->c, c); 	/*On donne les cercles de la balle et de la cible;*/
					bullets->tab_b[i]->timer_tracking -= 1;
				}			
			}

			move_bullet(bullets->tab_b[i]);
			i++;
		}
	}
}




void move_bullet(Bullet* b){
	b->c.x += cos(b->angle) * b->speed;
	b->c.y -= sin(b->angle) * b->speed;
}

void swap_b(Bullet ** a, Bullet ** b){
	Bullet* tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void destroy_bullet(Bullets* bullets, int index_b){

	int last_bullet = bullets->size_real-1;

	swap_b(&bullets->tab_b[index_b], &bullets->tab_b[last_bullet]);
	MLV_free_image(bullets->tab_b[last_bullet]->img);
	free( bullets->tab_b[last_bullet] ) ;
	bullets->size_real -= 1;

}