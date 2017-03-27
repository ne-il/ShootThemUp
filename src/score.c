#include "../include/score.h"
  
void display_input_box(char ** name, MLV_Font* font){
	int width_box = 500 ; 
	int height_box = 50;
	int positionBoxX = (WIDTH-width_box)/2;
	int positionBoxY = (HEIGHT-height_box)/2;
	MLV_Color border_color = MLV_COLOR_BLACK;
	MLV_Color background_color = MLV_COLOR_RED;
	MLV_Color text_color = MLV_COLOR_WHITE;

	MLV_wait_input_box_with_font (positionBoxX, positionBoxY, width_box, height_box, border_color,  text_color, background_color, " Name : ", name, font);
	MLV_actualise_window();
}

void allocation_name(char ** name){
	*name = (char *) calloc (SMAX, sizeof(char));
	if (NULL == *name){
		fprintf(stderr, "Error : no more memory left\n");
		exit(EXIT_FAILURE);
	}
}

void display_high_score(High_Score * hg, MLV_Font* font){
	char text [64];
	char * high_score_text;
	int i;
	int width_box = 500 ; 
	int height_box = 900;

	MLV_Color border_color = MLV_COLOR_WHITE;
	MLV_Color background_color = MLV_COLOR_BLACK;
	MLV_Color text_color = MLV_COLOR_WHITE;

	int positionBoxX = (WIDTH-width_box)/2;
	int positionBoxY = (HEIGHT-height_box)/2;

	high_score_text = (char *)calloc (1024 , sizeof (char));
	for (i = 0; i <= SMAX; i++){
		sprintf(text, "%d)        %s        %d\n", i+1, hg->high_score[i].name, hg->high_score[i].score);
		high_score_text = strcat(high_score_text, text);
	}
	high_score_text = strcat(high_score_text, "\0");
    /*MLV_draw_text_box(
        10,280,
        450,600,
        high_score_text,
        10,
        MLV_COLOR_RED, MLV_COLOR_BLUE, MLV_COLOR_BLACK,
        MLV_TEXT_LEFT,
        MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER
	);*/
    MLV_draw_filled_rectangle(0,0,WIDTH,HEIGHT,MLV_COLOR_BLACK);
	MLV_draw_text_box_with_font(
			positionBoxX, positionBoxY, width_box, height_box,
			high_score_text, font,
			9,
			border_color, text_color, background_color,
			MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER
	);
	MLV_actualise_window();
	MLV_wait_seconds(5);

}

int compare(const void * a, const void * b){
	return ( (*(Score*) b).score - (*(Score*) a).score);
}

void read_score(High_Score *high_score, FILE * file){
	int i;
	int ret;

	for (i = 0; i <= SMAX;i++){
		allocation_name(&high_score->high_score[i].name);
		ret = fscanf(file, "%s %d\n", high_score->high_score[i].name, &high_score->high_score[i].score);
		if (ret == EOF){
			fprintf(stderr, "Error : no more score in the file\n");
			exit(EXIT_FAILURE);
		}
	}
	
}

void write_score(High_Score * high_score, FILE * file){
	int i;
	
	fseek(file, 0, SEEK_SET);
	for (i = 0; i <= SMAX;i++)
		fprintf(file, "%s %d\n",high_score->high_score[i].name, high_score->high_score[i].score);
}
