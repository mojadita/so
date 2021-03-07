#include <stdio.h>
#include <stdlib.h>

#define F(_f) __FILE__":%d:%s: "_f, __LINE__, __func__

int main()
{
    char buffer[1000];
    int bs = 0;
    int last_char = '\n', c;
    unsigned long
        eliminated_spntabs = 0,
        eliminated_nl = 0;

    while((c = getchar()) != EOF) {
        switch(c) {

        case '\t': case ' ':
            if (bs >= sizeof buffer) {
                /* full buffer, cannot fit more */
                fprintf(stderr,
                    "we can only hold upto %d blanks in"
                    " sequence\n", (int)sizeof buffer);
                exit(1);
            }
            /* add to buffer */
            buffer[bs++] = c;
            break;

        default: /* normal char */
            /* print intermediate spaces, if any */
            if (bs > 0) {
                printf("%.*s", bs, buffer);
                bs = 0;
            }
            /* and the read char */
            putchar(c);
            /* we only update last_char on nonspaces and
             * \n's. */
            last_char = c;
            break;

        case '\n':
            /* eliminate the accumulated spaces */
            if (bs > 0) {
                eliminated_spntabs += bs;
                printf("<<%d>>", bs);
                bs = 0;
            }
            if (last_char != '\n') {
                putchar('\n');
            } else {
                eliminated_nl++;
            }
            last_char = '\n';
            break;

        } /* switch */
    } /* while */

    fprintf(stderr,
            F("Eliminated tabs: %lu\n"),
            eliminated_spntabs);
    fprintf(stderr,
            F("Eliminated newl: %lu\n"),
            eliminated_nl);

    return 0;
}

