#pragma once
#include "traversal.h"
#include"abstractionlayer.h"
#include"globaldeclarations.h"

void map_init()
{
	//makes the map
	virtualmap = (Cell**)malloc(sizeof(Cell*) * 10);
	for (int i = 0; i < 10; i++)
	{
		*(virtualmap + i) = (Cell*)malloc(sizeof(Cell) * 10);
		memset(virtualmap[i], 0, sizeof(Cell) * 10);
	}
	return;
}

Cell** expand_map(int dir)
{
	/*
		dir:
			1: more mem needed to the right //left
			2: more mem needed to the left //below
			3: more mem needed below //right
			4: more mem needed above //above
	*/

	//it will take in what direction to expand the map
	//realloc's the map
	//also memcpy's all the stuff into the new map
	Cell** newmap;
	newmap = (Cell**)malloc(sizeof(Cell*) *(size_rows+1));
	for (int i = 0; i < curr_row+1; i++)
	{
		newmap[i] =(Cell*)malloc(sizeof(Cell) * (size_cols + 1));
	}
	memset(newmap, 0, sizeof(int) * (size_rows + 1) * (size_cols + 1));
	switch (dir)
	{
		case 1:
			for (int i = 0; i < size_rows; i++)
			{
				memcpy(newmap[i], virtualmap[i], sizeof(Cell) * size_cols);
			}
			break;
			num_rows++;
		case 0:
			for (int i = 0; i < size_rows; i++)
			{
				memcpy(newmap[i] + 1, virtualmap[i], sizeof(Cell) * size_cols);
			}
			num_cols++;
			curr_col++;
			break;
		case 2:
			for (int i = 0; i < size_rows; i++)
			{
				memcpy(newmap[i], virtualmap[i], sizeof(Cell) * size_cols);
			}
			break;
			num_cols++;
		case 3:
			for (int i = 0; i < size_rows; i++)
			{
				memcpy(newmap[i + 1], virtualmap[i], sizeof(Cell) * size_cols);
			}
			num_rows++;
			curr_row++;
			break;
	}
	size_rows++;
	size_cols++;
	return newmap;
}

void printMap()
{
	//prints the location of the robot on the map as well as the nodes visited and the walls
	
	for (int i = 0; i <size_rows; i++)
	{
		printf(" ");
		for (int j = 0; j < size_cols; j++)
		{
			if (mapc(i, j).N)
				printf("_");
			else
				printf(" ");
			printf(" ");
		}
		printf("\n");
		for (int j = 0; j < size_cols; j++)
		{
			if (mapc(i, j).W)
				printf("|");
			else
				printf(" ");

			if (mapc(i, j).Vis)
				printf("V");
			else
				printf(".");
		}
		if (mapc(i, size_cols - 1).E)
			printf("|");
		printf("\n");
		if (i == size_rows - 1)
		{
			for (int k = 0; k < size_cols; k++)
			{
				if (mapc(i, k).S)
					printf(" _");
				else
					printf("   ");
			}
		}
	}
	printf("\n\n");
	return;
}