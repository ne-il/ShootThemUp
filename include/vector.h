#ifndef __VECTOR__
#define __VECTOR__

#include <math.h>

#include "const.h"

typedef struct {
	double x;
	double y;
}Vector;


void initialize_vector(Vector* v);

void add_vect(Vector* v, double x, double y);

double get_speed (Vector v);

void set_vect_nul(Vector* v);

#endif