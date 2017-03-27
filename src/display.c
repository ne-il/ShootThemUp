#include "../include/display.h"

static void display_score(Player* p, MLV_Font* font){
	char buffer1[524];

	sprintf(buffer1, "Score: %d ", p->score);

	MLV_draw_text_with_font(3,10, buffer1, font, MLV_COLOR_RED);
}

static void display_life_bar(Cercle pos, int health_max, int health, int team){
	MLV_Color life_color;

	int width_life_bar = pos.radius * 3;
	int height_life_bar = 10;
	int width_remeining;

	int x_corner;
	int y_corner;

	x_corner = pos.x - pos.radius;
	y_corner = pos.y - (pos.radius +15);

	life_color = (team == GOOD_GUYS? MLV_COLOR_GREEN: MLV_COLOR_RED);

	MLV_draw_filled_rectangle(x_corner, y_corner , width_life_bar  , height_life_bar , MLV_COLOR_BLACK);
	width_remeining = width_life_bar *  (  (float)health  / (float) health_max)  ;
	MLV_draw_filled_rectangle(x_corner, y_corner + 2, width_remeining > 0? width_remeining :0 , height_life_bar-3 , life_color);
}

static void display_player(Player* p){
	static short i = 0;
	short condition = TRUE;

	if (p->is_invincible == TRUE){
		i++;
		if(i == 5)
			i = 0;
		condition = i;
	}

	if (condition)
		MLV_draw_image(p->ship, (p->c.x -p->c.radius ), (p->c.y - p->c.radius ) );

	display_life_bar(p->c, p->health_max, p->health, GOOD_GUYS);
}

static void display_enemy(Enemy* e){
	MLV_draw_image(e->ship, (e->c.x - e->c.radius), (e->c.y - (e->c.radius)) );
	display_life_bar(e->c, e->health_max, e->health, BAD_GUYS);
}

static void display_enemies(Enemies* enemies){
	int i = 0;

	for(i = 0; i < enemies->size_real ; i++)
		display_enemy(enemies->ship_tab[i]);
}

static void display_bullet(Bullet* b){
	MLV_draw_image(b->img, (b->c.x -b->c.radius ), (b->c.y - b->c.radius /2 ) );
}

static void display_bullets (Bullets* bullets) {
	int i; 
	for (i = 0; i < bullets->size_real; i++)
		display_bullet(bullets->tab_b[i]);
}

static void display_bonus(Bonus * bs){
	MLV_draw_image(bs->img, (bs->c.x - bs->c.radius), (bs->c.y - bs->c.radius) );
}

static void display_bonuses(Bonuses * bses){
	int i;
	for (i = 0; i < bses->size_real; i++)
		display_bonus(bses->bonuses[i]);
}

static void display_background(MLV_Image* background){
	static int init = 1;
	int scroll_speed = 3;
	
	static int img_w;
	static int x_source = 0;
	static int truc = 0;

	if(init){
		img_w = MLV_get_image_width(background);
		img_w = (img_w < WIDTH)? WIDTH: img_w;	
		MLV_resize_image(background, img_w, HEIGHT);
		init = 0;
	}

	if (x_source >= (img_w - WIDTH)){
		MLV_draw_partial_image(background, 0, 0, WIDTH, HEIGHT, WIDTH - truc, 0);
		truc += scroll_speed;
	}

	if (x_source >= img_w ){
		truc = 0;
		x_source = 0; 
	}

	MLV_draw_partial_image(background, x_source, 0, WIDTH, HEIGHT, 0, 0);

	x_source += scroll_speed;
}

void display_all(Player *p, Enemies * e, Bonuses * bses, MLV_Image * bg, MLV_Font* font){
	display_background(bg);
	display_player(p);
	display_enemies(e);
	display_bonuses(bses);
	display_bullets(&p->bullets);
	display_bullets(&e->bullets);
	display_score(p, font);

}