#include "../include/vector.h"

void initialize_vector(Vector* v){
	v->x = 0;
	v->y = 0;

}

void add_vect(Vector* v, double x, double y){
	v->y += y;
	v->x += x;
}

void set_vect_nul(Vector* v){
	v->y = 0;
	v->x = 0;	
}

double get_speed (Vector v) {
	return sqrt( (v.x * v.x) + (v.y * v.y) );
}
