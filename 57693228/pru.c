#include <assert.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct client {
	char *id;
	struct client *next;
} client;

void del(client **l, char *n)
{
    assert(l != NULL);

	/* first advance the reference to the n-esim pointer,
	 * (zero meaning the first node) We decrement n after
	 * checking, and test goes on while *l is also non null
	 */
	while (*l && strcmp((*l)->id,  n))
		l = &(*l)->next; /* move the reference to a reference
						  * to the pointer in the next node.
						  */
	client *q = *l; /* temporary link to the node being unlinked */
	if (q) {
		*l = q->next; /* make *l point to the next node. */
		free(q);      /* free the client node */
	}
} /* del */

void ins(client **l, char *n)
{
    assert(l != NULL);

    client *c = malloc(sizeof *c);
    assert(c != NULL);

    c->id = n;
    c->next = *l;
    *l = c;
} /* ins */

void print(client **l)
{
    client *p;
    char *sep = "";
    for (p = *l; p; p = p->next) {
        printf("%s%s", sep, p->id);
        sep = ", ";
    }
    printf("\n");
} /* print */

int
main(int argc, char **argv)
{
    int opt;
    client *the_list;
    while ((opt = getopt(argc, argv, "i:d:p")) != -1) {
        switch(opt) {
        case 'i': ins(&the_list, optarg); break;
        case 'd': del(&the_list, optarg); break;
        case 'p': print(&the_list); break;
        } /* switch */
    } /* while */
    exit(EXIT_SUCCESS);
} /* main */
