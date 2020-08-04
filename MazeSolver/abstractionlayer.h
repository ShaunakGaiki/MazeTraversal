#pragma once
#include"traversal.h"
#include"virtualmap.h"
#include"traversal.h"
#include"globaldeclarations.h"

#define STATE 1 //This means that it is a simulation

#if STATE==1
int row_pos=0, col_pos=0;//inizitialize with starting placement of the robot
char** fullmap;
FILE* mapfile;

void readMap()
{
	//read in the text map
	int r, c;
	mapfile = fopen("map.txt", "r");
	fscanf(mapfile, "%d %d", &r, &c);

	fullmap = (char**)malloc(sizeof(char*) * (2*r+1));
	for (int i = 0; i < 2*r+1; i++)
	{
		fullmap[i] = (char*)malloc(sizeof(char) * (2*c+2));
	}
	fscanf(mapfile, "%*[\n]");
	for (int i = 0; i < 2*r+1; i++)
	{
		fscanf(mapfile, "%*[\n]");
		fgets(fullmap[i],2*c+2,mapfile);
		fscanf(mapfile, "%*[\n]");
	}
	fclose(mapfile);
	return;
}

int getRobotStatus()
{
	//this will give the surrounding walls, in real life or the pre map
	//The values range from 0-15, the bits go: N E S W
	int ret=0;
	if (fullmap[2*row_pos+1][2*col_pos] == '|')
		ret += 1;
	if (fullmap[2*row_pos+2][2*col_pos+1] == '_')
		ret += 2;
	if (fullmap[2*row_pos+1][2*col_pos + 2] == '|')
		ret += 4;
	if (fullmap[2*row_pos][2*col_pos+1] == '_')
		ret += 8;
	return ret;
}

void move(int dir)
{
	//this will move the robot, whether it be in real life or on the simulator map
	//also changes curr_dir
	curr_dir = dir;
	if (updrow(dir) < 0 || updrow(dir)>size_rows-1)
		virtualmap = expand_map(dir);
	if (updcol(dir) < 0 || updcol(dir) > size_cols-1)
		virtualmap = expand_map(dir);
	dirconv(dir).Vis = 1;
	counter++;
	dirconv(dir).tag = counter;
	curr_col = updcol(dir);
	curr_row = updrow(dir);
	row_pos -= (dir & 1) * (-1 + ((dir >> 1) << 1));
	col_pos -= ((dir + 1) & 1) * (1 - ((dir >> 1) << 1));
	printMap();
	return;
}
#endif