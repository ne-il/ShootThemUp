#ifndef __INFO__
#define __INFO__

#include "vector.h"

typedef struct {
	double x;
	double y;
	double radius;
}Cercle;

int is_out_of_screen(Cercle c);

double get_distance(Cercle* c1, Cercle* c2 ); 

#endif
