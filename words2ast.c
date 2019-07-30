#include <stdio.h>
#include <ctype.h>

#define IDLE	(0)
#define FIRST	(1)
#define NEXT	(2)

int main()
{
	int status = IDLE;
	int c;
	while ((c = getchar()) != EOF) {
		if (isupper(c)) {
			switch (status) {
			case IDLE:
				status = FIRST;
				printf("***");
				break;
			case FIRST: case NEXT:
				status = NEXT;
				break;
			} /* switch */
		} else if (islower(c)) {
			switch (status) {
			case IDLE:
				putchar(c);
				break;
			case FIRST: case NEXT:
				status = NEXT;
			} /* switch */
		} else {
			switch (status) {
			case IDLE:
				putchar(c);
				break;
			case FIRST: case NEXT:
				putchar(c);
				status = IDLE;
				break;
			} /* switch */
		} /* if */
	} /* while */
} /* main */
