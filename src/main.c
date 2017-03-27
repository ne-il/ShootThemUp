#include <time.h>

#include "../include/input.h"
#include "../include/score.h"


void files_open (FILE ** file_wave, FILE ** file_patern1, FILE ** file_patern2, FILE ** file_patern3, FILE ** file_type){
	*file_wave = fopen ("src/.wave_enemy", "r+");
	if (*file_wave == NULL){
		fprintf(stderr, "Error : the file doen't exist or can't be opened\n");
		exit(EXIT_FAILURE);
	}
	
	*file_patern1 = fopen ("src/.patern_enemy1.pat", "r");
	*file_patern2 = fopen ("src/.patern_enemy2.pat", "r");
	*file_patern3 = fopen ("src/.patern_enemy3.pat", "r");	
	if (NULL == *file_patern1 ||NULL == *file_patern2 ||NULL == *file_patern3){
		fprintf(stderr, "Error : Patern files can't be opened.\n");
		exit(EXIT_FAILURE);
	}

	*file_type = fopen ("src/.script_enemy_wave_easy.pat", "r");
	if (NULL == *file_type){
		fprintf(stderr, "Error : Script can't be opended\n");
		exit(EXIT_FAILURE);
	}
}

void files_close (FILE * file_wave, FILE * file_patern1, FILE * file_patern2, FILE * file_patern3, FILE * file_type){
	fclose (file_wave);
	fclose (file_patern1);
	fclose (file_patern2);
	fclose (file_patern3);
}

int display_menu(){
	MLV_Music* music_menu = NULL;
	MLV_Keyboard_button touche;
	MLV_Font* font = NULL;

	const char *text1 = "NEW GAME";
	const char *text2 = "EXIT GAME";

	MLV_Color border_color = MLV_COLOR_WHITE;
	MLV_Color background_color = MLV_COLOR_RED;
	MLV_Color text_color = MLV_COLOR_WHITE;


	int width_box = 500 ; 
	int height_box = 100;
	int size_interligne = 9;
	int positionBoxX = (WIDTH-width_box)/2;
	int positionBoxY = (HEIGHT-height_box)/2;
	int vertical_space = 140;
	int choice = 1;

	font = MLV_load_font( "src/font/induction.ttf" , 35 );
	if(NULL == font){
		fprintf(stderr, "ERROR WHILE LOADING THE FONT\n" );
		exit(EXIT_FAILURE);
	}

	music_menu = MLV_load_music("src/sounds/menu.ogg");
	if(NULL == music_menu){
		fprintf(stderr, "ERROR WHILE LOADING THE MUSIC MENU\n" );
		exit(EXIT_FAILURE);
	}
	MLV_play_music(music_menu,1.0, -1);

	MLV_flush_event_queue();

	while(TRUE){
		MLV_draw_filled_rectangle(0,0,WIDTH,HEIGHT, MLV_COLOR_BLACK);
		positionBoxY = (HEIGHT-height_box)/2;

		positionBoxY -= vertical_space;
		text_color = (choice == 1)? MLV_COLOR_WHITE: MLV_COLOR_BLACK;
		MLV_draw_text_box_with_font(
			positionBoxX, positionBoxY, width_box, height_box,
			text1, font,
			size_interligne,
			border_color, text_color, background_color,
			MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER
		);
		positionBoxY += vertical_space;

			

		text_color = (choice == 2)? MLV_COLOR_WHITE: MLV_COLOR_BLACK;
		MLV_draw_text_box_with_font(
			positionBoxX, positionBoxY, width_box, height_box,
			text2, font,
			size_interligne,
			border_color, text_color, background_color,
			MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER
		);


		MLV_actualise_window();
		MLV_wait_keyboard(&touche, NULL, NULL );
		if (touche == MLV_KEYBOARD_UP || touche == MLV_KEYBOARD_z){
			if(choice > 1){
		 		choice--;
			}
		}
		if (touche == MLV_KEYBOARD_DOWN || touche == MLV_KEYBOARD_s){
			if(choice < 2){
		 		choice++;
			}
		}

		if (touche == MLV_KEYBOARD_RETURN)
			break;

	}
	MLV_free_font(font);
	MLV_stop_music();
	MLV_free_music(music_menu);
	return choice;
}

void game(){
	MLV_Image* background = NULL;
	MLV_Music* music = NULL;
	MLV_Sound* shoot_sound = NULL;
	MLV_Sound* explosion_sound = NULL;
	MLV_Font* font = NULL;

	Player* p;
	Enemies es;
	Bonuses bses;
	Animations anims;


	FILE * file = NULL;
	FILE * file_wave = NULL;

	High_Score hg;

	int number_ennemies_wave = 0;
	int wave = 1;

	FILE * file_patern1 = NULL;
	FILE * file_patern2 = NULL;
	FILE * file_patern3 = NULL;

	FILE * file_type = NULL;

	int enemy_generation_speed = 300;
	int delta, t_last_gen = 0;
	int i = 0;
	int ret;

	p = initialize_player(500., 500., 25., 10.,500);
	create_ennemies(&es);
	create_bonuses(&bses);
	initialize_animations(&anims);


	files_open(&file_wave, &file_patern1, &file_patern2, &file_patern3, &file_type);
	
	ret = fscanf (file_wave ,"%d\n", &number_ennemies_wave);
	if (ret == EOF){
		fprintf(stderr, "Error : the file can't be opened\n");
		exit(EXIT_FAILURE);
	}

	if( NULL == ( background = MLV_load_image("src/img/background.png") ) ) {
		fprintf(stderr, "background INTROUVABLE\n" );
		exit(EXIT_FAILURE);
	}

	if( MLV_init_audio() ){
		fprintf(stderr, " Error while initializing MLV_audio\n");
	}
	if( NULL == (music = MLV_load_music( "src/sounds/music_shoot.ogg") ) ) {
		fprintf(stderr, "MUSIC INTROUVABLE\n" );
		exit(EXIT_FAILURE);
	}
	if( NULL == (shoot_sound = MLV_load_sound( "src/sounds/shoot_sound.wav") ) ) {
		fprintf(stderr, "shoot_sound.wav INTROUVABLE\n" );
		exit(EXIT_FAILURE);
	}
	if( NULL == (explosion_sound = MLV_load_sound( "src/sounds/explosion.wav") ) ) {
		fprintf(stderr, "explosion.wav INTROUVABLE\n" );
		exit(EXIT_FAILURE);
	}

	font = MLV_load_font( "src/font/induction.ttf" , 15 );
	if(NULL == font){
		fprintf(stderr, "ERROR WHILE LOADING THE FONT\n" );
		exit(EXIT_FAILURE);
	}

	MLV_play_music(music, 1.0, -1);	


	

	while ( quit() && !is_dead_player(p) ){
		delta = MLV_get_time();

		if(delta - t_last_gen > enemy_generation_speed ) {
			if (number_ennemies_wave && es.size_real < 5){
				switch (enemy_type(file_type)){
					case EASY :
						generate_random_enemy_right_border(&es, file_patern1);
						break;

					case MEDIUM :
						generate_random_enemy_right_border(&es, file_patern2);
						break;

					case HARD :
						generate_random_enemy_right_border(&es, file_patern3);
						break;
				}
				t_last_gen = MLV_get_time();
				number_ennemies_wave -= 1;
			}
			else{
				if (!es.size_real){
					wave += 1;
					rewind (file_type);
					ret = fscanf (file_wave ,"%d\n", &number_ennemies_wave);
					if (ret == 0)
						fprintf(stderr, "Error : Can't read the next number of enemies in the next wave.\n");
					switch (wave){
						case 4:
							file_type = fopen ("src/.script_enemy_wave_medium.pat", "r");
							if (NULL == file_type){
								fprintf(stderr, "Error : Script can't be opended\n");
								exit(EXIT_FAILURE);
							}
							break;

						case 7:
							file_type = fopen ("src/.script_enemy_wave_hard.pat", "r");
							if (NULL == file_type){
								fprintf(stderr, "Error : Script can't be opended\n");
								exit(EXIT_FAILURE);
							}
							break;

						default :
							break;
					}
				}
			}
		}

		for(i = 0; i < es.size_real ; i++){
			enemy_shoot(&es, es.ship_tab[i], p);
		}


		read_input(p, shoot_sound);

		update_player(p);	/*On bouge le joueur, on l'empeche de sortir de l'écran, on met a jour son invincibilité*/
		move_enemies(&es);

		update_all_bullets(p, &es);
		update_bonuses(&bses);
	
		check_all_collision(p, &es, &bses, &anims, explosion_sound);
		check_enemies_out_of_screen(&es, p);

		display_all(p, &es, &bses, background, font);
		display_animations(&anims);

		MLV_delay_according_to_frame_rate ();
		MLV_actualise_window();

	}

	file = fopen("src/.high_score.hg", "r+");
	if (NULL != file){
		read_score(&hg, file);
		if (p->score < hg.high_score[SMAX].score)
			printf("Not enought strong you are to be in the TOP 10\n");
		else{
			display_input_box(&hg.high_score[SMAX].name, font);
			hg.high_score[SMAX].score = p->score;
			qsort(hg.high_score, 10, sizeof(Score), compare);
			write_score(&hg, file);
		}
		display_high_score(&hg, font);
	}




	fclose (file);	
	files_close(file_wave, file_patern1, file_patern2, file_patern3, file_type);

	destroy_player(p);
	destroy_enemies(&es);
	destroy_bonuses(&bses);
	destroy_animations(&anims);

	MLV_stop_music();
	MLV_free_music( music);
	MLV_free_sound( shoot_sound);
	MLV_free_sound( explosion_sound);

	MLV_free_image(background);
	MLV_free_font(font);
	return ;

}

int main(int argc, char const *argv[]){

	int end = FALSE;

	MLV_create_window("Shoot'em Up", "Shoot'em Up", WIDTH, HEIGHT);
	MLV_init_audio();
	MLV_change_frame_rate(60);

	

	while(end == FALSE){

		switch( display_menu() ){
			case 1:
				game();
				break;
				
			case 2:
				end = TRUE;
				break;	
		}
	}
	
	MLV_free_audio();
	MLV_free_window();

	return 0;
}