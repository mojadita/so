#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void paint_line(char *s, int n)
{
	int l = strlen(s);
	while (n >= l) {
		fputs(s, stdout);
		n -= l;
    }
    /* n < l */
	if (n > 0)
    printf("%.*s", n, s);
}

void paint_tie(int n)
{
	int row;
	for(row = 1; row <= n; row++) {
		paint_line("*******", row);
		paint_line("       ", 2*(n-row) + 1);
		paint_line("*******", row);
		printf("\n");
	}
	for (row = n-1; row > 0; row--) {
		paint_line("*******", row);
		paint_line("       ", 2*(n-row) + 1);
		paint_line("*******", row);
		printf("\n");
	}
}

int main(int argc, char **argv)
{
	int i;
	for (i = 1; i < argc; i++) {
		int n = atoi(argv[i]);
		paint_tie(n);
	}
}

