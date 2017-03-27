#ifndef __ANIMATION__
#define __ANIMATION__ 

#include <stdio.h>
#include <stdlib.h>


typedef struct{
	int x;
	int y;
	int diameter;
	int index;
}Animation;

Animation* create_animation(int x, int y, int diameter);

void destroy_animation();
void swap_animation(Animation** a, Animation** b);

#endif