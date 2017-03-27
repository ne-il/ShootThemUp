#ifndef __ENEMIES__
#define __ENEMIES__

#include "enemy.h"
#include "player.h"

typedef struct {
	Enemy** ship_tab;
	int size_real;
	int size_max;
	Bullets bullets;
}Enemies;

void create_ennemies(Enemies* enemies);

void destroy_enemies(Enemies* enemies);

void realloc_enemies(Enemies* enemies);

void add_enemy(Enemies* enemies, Enemy* e);

int is_enemies_full(Enemies* enemies);

void enemy_shoot(Enemies* es, Enemy* e, Player* p);

void bounce_enemies(Enemies* enemies);

void swap_e(Enemy ** a, Enemy ** b);

Enemy* get_closest_enemy(Cercle* b_pos, Enemies* enemies );

void destroy_enemy(Enemies* enemies, int index_e);

void check_enemies_out_of_screen(Enemies* enemies, Player* p );

void move_enemies(Enemies * enemies);

void generate_random_enemy_right_border(Enemies* enemies, FILE * file_patern);

void update_all_bullets (Player *p, Enemies *e);

#endif