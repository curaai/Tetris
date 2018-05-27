#ifndef _LIBRARY_
#define _LIBRARY_

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <process.h>

#define UP		  72
#define DOWN	  80
#define LEFT	  75
#define RIGHT	  77
#define SPACEBAR  32
#define KEY_CHECK 224

//set the screen
#define SCREEN_WIDTH 14
#define SCREEN_HEIGHT 26
#define SCREEN_LEFT_EDGE 0 
#define SCREEN_RIGHT_EDGE 13
#define SCREEN_DOWN_EDGE 25
#define SHAPES 9

typedef struct _BLOCK
{
	int block_x;
	int block_y;
	int shape;
	int next_shape;
	int direction;
}BLOCK;

enum shapes { Z = 0, S, I, J, L, O, T };

#endif // !_LIBRARY_	