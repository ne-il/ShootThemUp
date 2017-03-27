#include "../include/cercle.h"


int is_out_of_screen(Cercle c){
	return (c.x + c.radius <= 0 || c.x - c.radius >= WIDTH  || c.y + c.radius <= 0 || c.y - c.radius >= HEIGHT );
}

double get_distance(Cercle* c1, Cercle* c2 ){
	return ( (c1->x - c2->x) * (c1->x - c2->x) ) + ( (c1->y - c2->y) * (c1->y - c2->y) );
}