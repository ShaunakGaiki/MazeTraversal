#pragma once
#include<stdbool.h>
#include<stdio.h>
#include"queue.h"
#include"stack.h"

//bunch of macros to get easy access to the virtualmap without the use of multiple switch cases/if statements
#define west(x,y) virtualmap[x][y-1]
#define south(x,y) virtualmap[x+1][y]
#define east(x,y) virtualmap[x][y+1]
#define north(x,y) virtualmap[x-1][y]
#define dirconv(n) virtualmap[curr_row-(n&1)*(-1+((n>>1)<<1))][curr_col-((n+1)&1)*(1-((n>>1)<<1))]//takes in number 0-3 used in the direction enum to turn it into array, no if statements needed
#define updrow(n) curr_row-(n&1)*(-1+((n>>1)<<1))
#define updcol(n) curr_col-((n+1)&1)*(1-((n>>1)<<1))
#define mapc(x,y) virtualmap[x][y]

int num_rows = 10, num_cols = 10;//current number of rows/cols seen in the map, NOT the size of the map in memory
int size_rows = 10, size_cols = 10;
int curr_row = 0, curr_col = 0;//current position
int curr_dir = 3;//the current direction that the robot is travelling in
int counter = 1;//this is a counter for the tags to put on the tiles
enum index { W, S, E, N };//used to do easy indexing of the tempstate array

typedef struct Cell {
	unsigned int N : 1;
	unsigned int E : 1;
	unsigned int S : 1;
	unsigned int W : 1;
	unsigned int Vis : 1;
	unsigned int Vic : 1;
	unsigned int : 0;
	int tag;
}Cell;

typedef struct pair
{
	int n1, n2;
}pair;

Cell** virtualmap;
