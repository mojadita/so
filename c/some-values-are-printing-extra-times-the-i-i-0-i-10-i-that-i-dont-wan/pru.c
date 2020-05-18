#include <stdio.h>

int main()
{
	int a = 1, line;
	for (line = 0; line < 10; line++) {
		int cube = a*a*a, item_in_line;
		char *sep = "";
		for (item_in_line = 0; item_in_line <= line; item_in_line++) {
			printf("%s%d", sep, cube);
			sep = ", ";
		}
		printf("\n");
		a += 2;
	}
}
