#include "../include/collision.h"

int is_collision(Cercle* c1, Cercle* c2){
	if( fabs( (c1->x - c2->x) ) <= (c1->radius + c2->radius) && fabs( (c1->y - c2->y) ) <= (c1->radius + c2->radius) )
		return TRUE;
	else{
		return FALSE;
	}
}

static void collision_bullets_p_enemies(Player* player, Enemies* enemies, Bonuses * bses, Animations* anims, MLV_Sound* explosion_sound){
	int i = 0;
	int j = 0;
	int explosion_x = 0;
	int explosion_y = 0;
	Enemy* e_tmp = NULL;

	for(i = 0; i < player->bullets.size_real; i++){
		for (j = 0; j < enemies->size_real; j++){

			e_tmp = enemies->ship_tab[j];
			explosion_x = e_tmp->c.x - e_tmp->c.radius;
			explosion_y = e_tmp->c.y - e_tmp->c.radius;

			if ( is_collision(&player->bullets.tab_b[i]->c, &e_tmp->c) ){

				destroy_bullet(&player->bullets, i);
				e_tmp->health -= player->bullets.tab_b[i]->damage;

				if( is_dead_enemy(e_tmp) ){
					
					bonus (bses, &e_tmp->c);
					MLV_play_sound(explosion_sound, 0.3);
					add_animation(anims, explosion_x, explosion_y, e_tmp->c.radius * 2);
					destroy_enemy(enemies, j);
					player->score += 250;
				}
				break;
			}
		}
	}
}

static void collision_bonuses_player(Bonuses * bses, Player * p){
	int i = 0;

	for (i = 0; i < bses->size_real; i++){
		if (is_collision(&bses->bonuses[i]->c, &p->c)){
			destroy_bonus_in_bonuses(bses, i);
			apply_bonus(bses->bonuses[i], p);
		}
	}
}

static void collision_bullets_e_player(Bullets* bullets_e, Player* p){
	int i = 0;
	Bullet* bullet_tmp = NULL;
	
	for(i = 0; i < bullets_e->size_real; i++){
		bullet_tmp = bullets_e->tab_b[i];

		if (is_collision(&bullet_tmp->c, &p->c) ){
			destroy_bullet(bullets_e, i);
			if (p->is_invincible == FALSE){
				p->health -= bullet_tmp->damage;
				if( p->weapon_lvl > 1)
					p->weapon_lvl --;
				active_invincibility(p);
			}
			break;
		}
		if(bullets_e->tab_b[i]->tracking == TRUE){
			if (bullets_e->tab_b[i]->timer_tracking <= 0){
				destroy_bullet(bullets_e, i);
			}
			else {
				bullets_e->tab_b[i]->angle = get_angle_shot(&bullets_e->tab_b[i]->c, &p->c); 	/*On donne les cercles de la balle et de la cible;*/
				bullets_e->tab_b[i]->timer_tracking -= 1;
			}
		}
	}
	
}

static void collision_ship_p_ship_e(Player* p, Enemies* enemies){
	int i = 0;
	int colision_damage = 10;

	for(i = 0; i < enemies->size_real ; i++){
		if (is_collision(&p->c, &enemies->ship_tab[i]->c)){
			p->health -= colision_damage;
			enemies->ship_tab[i]->health -= colision_damage;
		}
	}	
}

void check_all_collision(Player *p, Enemies *es, Bonuses * bses, Animations* anims, MLV_Sound* explosion_sound){
	collision_bullets_p_enemies(p, es, bses, anims, explosion_sound);
	collision_bullets_e_player(&es->bullets, p);
	collision_bonuses_player(bses, p);
	collision_ship_p_ship_e(p, es);
}
