#include<stdio.h>
#include<stdlib.h>
#include<string.h>

FILE* map;
FILE* config;

int rows, cols, segments;
int cell_r, cell_c;

char* mapString;

void charcat(char* dest, char cat)
{
	char* append;
	append = (char*)malloc(1);
	*append = cat;
	strncat(dest, append, 1);
	return;
}

void makeWall(char type, int start_r, int start_c, int end_r, int end_c)
{
	int len;
	int offset = 2 * (cols + 1);//Number of characters in each row, including the newline
	offset *= (2 * start_r) + 1;//Number of rows in the text file to go down
	offset += (2 * start_c) + 1;//Number of columns before the index


	if (type == 'V')
	{
		offset--;
		len = end_r - start_r;
		len += 1;
		for (int i = 0; i < len; i++)
		{
			*(mapString+offset)='|';
			offset += (4 * cols) + 4;
		}
	}
	else
	{
		offset += 2 * (cols + 1);
		len = end_c - start_c;
		len += 1;
		for (int i = 0; i < len; i++)
		{
			*(mapString + offset) = '_';
			offset += 2;
		}
	}
	return;
}

int main()
{
	int r, c, r1, c1;
	char type;
	//This will read the config file and set up the map accordingly
	printf("FORMAT OF THE CONFIG FILE\n(num of rows) (num of columns) (num of wall segments)\n(type of wall segment : V or H) (starting row) (starting col)[end row][end col]\n.\n.\n.\n.\n\nFor vertical walls the segment is to the left of the cell you specify\nFor horizontal walls the segment is below the cell you specify\nThe last 2 arguments on the wall segment specifier lines are optional, only to be used for wall segments longer than 1");

	//Open the files
	config = fopen("config.txt", "r");
	map = fopen("map.txt", "w");

	fscanf(config, "%d %d %d", &rows, &cols, &segments);

	//INITIALIZE THE MAP

	mapString = (char*)malloc(4*cols*rows);
	memset(mapString, '\0', 4 * cols * rows);

	for (int i = 0; i < ((2 * rows) + 1); i++)
	{
		for (int j = 0; j < ((2 * cols) + 1); j++)
		{
			if ((i % 2) == 0 && (j % 2) == 0)
			{
				charcat(mapString, ' ');
				continue;
			}
			if ((i % 2) == 1 && (j % 2) == 1)
			{
				charcat(mapString,'.');
				continue;
			}
			if ((i == 0 && (j % 2) == 1) || ((i == 2 * rows) && (j % 2) == 1))
			{
				charcat(mapString,'_');
				continue;
			}
			if ((j == 0 && (i % 2) == 1) || (j == 2 * rows && (i % 2) == 1))
			{
				charcat(mapString, '|');
				continue;
			}
			charcat(mapString, ' ');
		}
		charcat(mapString,'\n');
	}

	for (int i = 0; i < segments; i++)
	{
		
		fscanf(config, " %c %d %d", &type, &r, &c);//do not remove space before %c
		int val = fscanf(config, "%d %d", &r1, &c1);
		if (val >= 1)
		{
			printf("\n\nworked at %d", i);
			makeWall(type, r, c, r1, c1);
		}
		else
		{

			makeWall(type, r, c, r, c);
		}
	}

	printf("\n\n\nMaze has been generated. It is in the map.txt file");
	printf("\n\n\n%s", mapString);
	fprintf(map, "%s", mapString);
	fclose(map);
	fclose(config);
	return 0;
}