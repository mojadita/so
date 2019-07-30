#include <assert.h>
#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define F(fmt) __FILE__":%d:%s: " fmt, __LINE__, __func__

char buffer[1024];

void process(FILE *f);

int flags = 0;
#define FLAG_NUMBER (1 << 0)
#define FLAG_COMMENTED (1 << 1)
char *fmt;

int
main(int argc, char **argv)
{
	int opt;

	while ((opt = getopt(argc, argv, "nc")) != EOF) {
		switch (opt) {
		case 'n': flags |= FLAG_NUMBER; break;
		case 'c': flags |= FLAG_COMMENTED | FLAG_NUMBER; break;
		}
	}

	argc -= optind;
	argv += optind;

	if (argc) {
		int i;
		for (i = 0; i < argc; i++) {
			FILE *f = fopen(argv[i], "rt");
			if (!f) {
				fprintf(stderr, F("ERROR: %s: %s (errno=%d)\n"),
					argv[i], strerror(errno), errno);
				continue;
			}
			printf("%s#%s\n\n",
				i ? "\n" : "",
				argv[i]);
			process(f);
			fclose(f);
		}
	} else {
		process(stdin);
	}
	return 0;
}

void process(FILE *f)
{
	int i = 0;
	while(fgets(buffer, sizeof buffer, f)) {
		char *s = strdup(buffer);
		assert(s != NULL);
		char *t = strtok(s, " \t\n");
		if (t) {
			if (flags & FLAG_NUMBER)
				if (flags & FLAG_COMMENTED)
					printf("    /* %05d */ %s", ++i, buffer);
				else
					printf("    %05d: %s", ++i, buffer);
			else
				printf("    %s", buffer);
		} else
			puts("");
		free(s);
	}
}
