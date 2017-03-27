#include "../include/animations.h"

void initialize_animations(Animations* anims){
	anims->size_max = 10;
	anims->size_real = 0;

	 if( NULL == (anims->anim_tab = (Animation**) calloc(anims->size_max, sizeof(Animations*) ) ) ){
	 	fprintf(stderr, "Error while initializing anim_tab\n" );
	 	exit(EXIT_FAILURE);

	 }

	 if ( NULL == (anims->spritesheet = MLV_load_image("src/img/explosions_decoupe.png")) ) {
	 	fprintf(stderr, "Error while loading explosion spritesheet\n" );
	 	exit(EXIT_FAILURE);
	 }
}

void add_animation(Animations* anims, int x, int y, int diameter){
	if (is_anim_tab_full(anims))
		realloc_anim_tab(anims);
	anims->anim_tab[ anims->size_real ] = create_animation(x, y, diameter);
	anims->size_real++;

}

int is_anim_tab_full(Animations* anims){
	return (anims->size_real >= anims->size_max);
}

void realloc_anim_tab(Animations* anims){
	Animation** tmp = NULL;
	int new_size_max = anims->size_max *2;

	tmp = (Animation**) realloc( anims->anim_tab, new_size_max * sizeof(Animation*));
	if (tmp == NULL){
		fprintf(stderr, "Error during reallocation of the anim_tab\n" );
		exit(EXIT_FAILURE);
	}
	anims->anim_tab = tmp;
	anims->size_max = new_size_max;

}

/*Cette fonciton parcourt anim_tap[] le tableau qui contient toute les animation en cours.
Elle affiche l'image qui correspond à la phase dans laquelle se trouve l'animaiton.
Elle fait avancer l'horloge interne de l'animation : index++
*/
void display_animations(Animations* anims){
	int i = 0;
	Animation* tmp = NULL;

	int w = 95;
	int h = 90;
	int x_source = 0, y_source = 0;
	int total_duration = 27;
	int frame_duration = 3;

	for (i = 0; i < anims->size_real; i++){


		tmp = anims->anim_tab[i]; 

		if( tmp->index < total_duration){

			if ( tmp->index > 0 && tmp->index < frame_duration){
				x_source = 0;
			}

			else if ( tmp->index < (frame_duration)*2){
				x_source = w;
			}

			else if ( tmp->index < (frame_duration)*3){
				x_source = w*2;
			}

			else if ( tmp->index < (frame_duration)*4){
				x_source = w*3;
			}

			else if ( tmp->index < (frame_duration)*5){
				x_source = w*4;
			}

			else if(tmp->index < (frame_duration)*6){
				y_source = h;
				x_source = 0;
			}
			else if(tmp->index < (frame_duration)*7){
				y_source = h;
				x_source = w;
			}
			else if(tmp->index < (frame_duration)*8){
				y_source = h;
				x_source = w*2;
			}
			else if(tmp->index < (frame_duration)*9){
				y_source = h;
				x_source = w*3;
			}
			else if(tmp->index < (frame_duration)*10){
				y_source = h;
				x_source = w*4;
			}

		
			MLV_draw_partial_image(anims->spritesheet, x_source, y_source, w, h, tmp->x, tmp->y );
			anims->anim_tab[i]->index++;
		
		}
		else{
			destroy_animation(anims , i);
			
		}

	}

	MLV_actualise_window();
}

void destroy_animations(Animations* anims){
	int i = 0;
	for( i = anims->size_real-1; i >= 0; i-- ){
		free (anims->anim_tab[i]);
	}
	free ( anims->anim_tab);

	MLV_free_image( anims->spritesheet);
}

void destroy_animation(Animations* anims, int index ){
	int last_a = anims->size_real - 1;

	swap_animation( &anims->anim_tab[ index ], &anims->anim_tab[ last_a ]);
	free(anims->anim_tab[ last_a] );
	anims->size_real --;
}