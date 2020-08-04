#pragma once
#include "abstractionlayer.h"
#include "virtualmap.h"
#include"globaldeclarations.h"


int getOpenDir()
{
	//tells if the robot is backed, and has nowhere to go
	//checks for walls AND if the nearby nodes are visited
	int tempstate[4] = { 0 };//this will be used to find the final result of whether the robot is trapped or not
	int temp;
	int state = getRobotStatus();

	//first set up the tempstate array with the already existing walls
	tempstate[W] = (state >> 0) & 1;
	mapc(curr_row, curr_col).W = tempstate[W];
	tempstate[S] = (state >> 1) & 1;
	mapc(curr_row, curr_col).S = tempstate[S];
	tempstate[E] = (state >> 2) & 1;
	mapc(curr_row, curr_col).E = tempstate[E];
	tempstate[N] = (state >> 3) & 1;
	mapc(curr_row, curr_col).N = tempstate[N];

	//now go through the tempstate array and for any direction that doesn't have a wall check if it is visited, if so mark that on the tempstate array
	for (int i = W; i <= N; i++)
	{
		if (tempstate[i])
			continue;
		if (dirconv(i).Vis)
			tempstate[i] = 1;
	}
	//return as an int that the traversal() function can analyze
	return (1 * tempstate[W] + 2 * tempstate[S] + 4 * tempstate[E] + 8 * tempstate[N]);
}

void backTrack()
{
	//does BFS for the closest unvisited node
	Queue* next=createQueue();
	Stack* moves=createStack();
	int movet;
	pair coords,tcoords;
	pair* src;
	int* vis;
	vis = (int*)malloc(sizeof(int) * counter);
	memset(vis, 0, sizeof(int) * counter);
	src = (pair*)malloc(sizeof(pair) * counter);//makes it as large as the number of nodes there are
	coords.n1 = curr_row;
	coords.n2 = curr_col;
	next->front->value = malloc(sizeof(pair));
	memcpy(next->front->value, &coords, sizeof(pair));
	//this loop does BFS until it finds the first unvisited node
	do
	{
		memcpy(&coords, next->front->value, sizeof(pair));
		if (virtualmap[coords.n1][coords.n2].Vis == 0)
			break;
		if (curr_col > 0 && !mapc(coords.n1,coords.n2).W && vis[west(coords.n1, coords.n2).tag]!=1)
		{
			tcoords.n1 = coords.n1;
			tcoords.n2 = coords.n2 - 1;
			next = enqueue(next, &tcoords, sizeof(pair));
			src[west(coords.n1,coords.n2).tag] = coords;
			vis[west(coords.n1, coords.n2).tag] = 1;
		}
		if (curr_col < size_cols-1 && !mapc(coords.n1,coords.n2).E && vis[east(coords.n1, coords.n2).tag] != 1)
		{
			tcoords.n1 = coords.n1;
			tcoords.n2 = coords.n2 + 1;
			next = enqueue(next, &tcoords, sizeof(pair));
			src[east(coords.n1,coords.n2).tag] = coords;
			vis[east(coords.n1, coords.n2).tag] = 1;
		}
		if (curr_row > 0 && !mapc(coords.n1,coords.n2).N && vis[north(coords.n1, coords.n2).tag] != 1)
		{
			tcoords.n1 = coords.n1 -1;
			tcoords.n2 = coords.n2;
			next = enqueue(next, &tcoords, sizeof(pair));
			src[north(coords.n1,coords.n2).tag] = coords;
			vis[north(coords.n1, coords.n2).tag] = 1;
		}
		if (curr_row < size_rows - 1 && !mapc(coords.n1, coords.n2).S && vis[south(coords.n1, coords.n2).tag] != 1)
		{
			tcoords.n1 = coords.n1 + 1;
			tcoords.n2 = coords.n2;
			next = enqueue(next, &tcoords, sizeof(pair));
			src[south(coords.n1, coords.n2).tag] = coords;
			vis[south(coords.n1, coords.n2).tag] = 1;
		}
		next = dequeue(next);
	} while (next->front != NULL);

	//this loop uses the src array to have a stack for what moves to make
	while (mapc(coords.n1, coords.n2).tag != mapc(curr_row, curr_col).tag)
	{
		tcoords = src[mapc(coords.n1, coords.n2).tag];
		if (mapc(tcoords.n1, tcoords.n2).tag == west(coords.n1, coords.n2).tag && coords.n2>0)
		{
			movet = E;
			moves = stackPush(&movet, moves, sizeof(movet));
			coords = tcoords;
			continue;
		}
		if (mapc(tcoords.n1, tcoords.n2).tag == east(coords.n1, coords.n2).tag && coords.n2<size_cols-1)
		{
			movet = W;
			moves = stackPush(&movet, moves, sizeof(movet));
			coords = tcoords;
			continue;
		}
		if (coords.n1 < size_rows - 1 && mapc(tcoords.n1, tcoords.n2).tag == south(coords.n1, coords.n2).tag )
		{
			movet = N;
			moves = stackPush(&movet, moves, sizeof(movet));
			coords = tcoords;
			continue;
		}
		if (mapc(tcoords.n1, tcoords.n2).tag == north(coords.n1, coords.n2).tag && coords.n1>0)
		{
			movet = S;
			moves = stackPush(&movet, moves, sizeof(movet));
			coords = tcoords;
			continue;
		}
	}

	//actually takes the moves that are on the stack
	while (moves->next != NULL)
	{
		memcpy(&movet, moves->value, sizeof(int));
		move(movet);
		moves = stackPop(moves);
	}
	return;
}

bool isComplete()
{
	//checks if the whole virtual map is filled in AND the map is surrounded by walls
	
	int temp;
	int i, j;//these are made local for the whole function because I am travelling around the array

	//this loop goes until the top left corner of the maze
	for (i = 0; i < num_rows; i++)
	{
		for (j = 0; j < num_cols; j++)
		{
			if (virtualmap[i][j].N)
			{
				goto OUT;
			}
		}
	}
OUT:;
	//below code goes around in a rectangle checking for the correct walls and exits if even one side isn't filled
	//if this doesn't work use the approach when everytime you see a bad state (wall/not visited) you check the distance you have gone and decide when to return
	temp = j;
	for (; j < num_cols; j++)
	{
		if (!(virtualmap[i][j].N))
			break;
	}
	j--;
	if (!((j - temp+1) == num_cols))
	{
		return false;
	}
	temp = i;
	for (; i < num_rows; i++)
	{
		if (!(virtualmap[i][j].E))
			break;
	}
	i--;
	if (!((i - temp + 1) == num_rows))
		return false;
	temp = j;
	for (; j > 0; j--)
	{
		if (!(virtualmap[i][j].S))
			break;
	}
	if (!((temp - j + 1) == num_cols))
	{
		return false;
	}
	temp = i;
	for (; i > 0; i--)
	{
		if (!(virtualmap[i][j].W))
			break;
	}
	if (!((temp - i + 1) == num_rows))
	{
		return false;
	}
	
	//this will check row by row whether each node is visited
	temp = j;
	for (; i < num_rows; i++)
	{
		for (j=temp; j < num_cols; j++)
		{
			if (!virtualmap[i][j].Vis)
				break;
		}
		j--;
		if (!((j - temp + 1) == num_cols))
			return false;
	}

	printf("\n\n\n\nMAZE TRAVERSED\n\n\n\n");
	//the virtual map has passed all conditions so it it fully explored
	return true;
}

void initTag(int dir)
{
	switch (dir)
	{
		case W:
			if (curr_col == 0)
				expand_map(W);
			break;
		case S:
			if (curr_row == size_rows-1)
				expand_map(S);
			break;
		case E:
			if (curr_col == size_cols - 1)
				expand_map(S);
			break;
		case N:
			if (curr_row == 0)
				expand_map(N);
			break;
	}
	counter++;
	dirconv(dir).tag = counter;
	return;
}

void traverseMaze()
{
	//this is the main control function
	int opendir;
	int dir;
	
	readMap();
	map_init();

	mapc(curr_row, curr_col).Vis = 1;
	mapc(curr_row, curr_col).tag = counter;

	while (true)
	{
		int tempstate[4] = { 1,1,1,1 };
		opendir = getOpenDir();
		if (opendir==15)
		{
			if (isComplete())
				return;
			backTrack();
			continue;
		}

		//get the i'th bit of the dir state respective to each direction 
		tempstate[W] -= (opendir >> 0) & 1;
		tempstate[S] -= (opendir >> 1) & 1;
		tempstate[E] -= (opendir >> 2) & 1;
		tempstate[N] -= (opendir >> 3) & 1;
		tempstate[curr_dir] *= 2;//makes it so that if the curr_dir is open then it will have higher priority

		//goes through the tempstate array to find which direction to go in
		for (int i = 0; i < 4; i++)
		{
			if (tempstate[i] == 2)
			{
				dir = i;

				break;
			}
			if(tempstate[i]==1)
				dir = i;
		}

		for (int i = 0; i < 4; i++)
		{
			if (tempstate[i])
				initTag(i);
		}
		move(dir);
	}
	free(virtualmap);
	
	return;
}