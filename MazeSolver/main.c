#include "queue.h"
#include"traversal.h"
#include"abstractionlayer.h"
#include"virtualmap.h"

/*void doInToPost()
{
	char initial[] = " ( ( (6 + 4) * ( 25 - 20 )) * 9) / ((10 + 20) / 30))";

	char endChar = '#';
	char* final;
	float val;
	int x = sizeof(initial);
	final = intopost(initial, sizeof(initial));
	strncat(final, &endChar, 1);
	val = evalPostfix(final, 2 * sizeof(initial));
	printf("\n%f", val);
	return 0;
}
*/

int main()
{
	traverseMaze();
	return 0;
}