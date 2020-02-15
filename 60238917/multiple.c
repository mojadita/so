/* SAME AS BEFORE :) */

#include <errno.h> /* for errno */
#include <stdio.h> /* for printf() and others */
#include <stdlib.h> /* for many standard functions */
#include <string.h> /* for strerror() */
#include <sys/wait.h> /* for wait() */
#include <unistd.h> /* for getpid() */
#include <getopt.h> /* for getopt() */

pid_t pid;

/* create the format string for printf with a pretty header,
 * showing pid, source file, source line, source function,
 * and the provided format string. */
#define F(_fmt) "[pid=%d]:"__FILE__":%d:%s: "_fmt,pid,__LINE__,__func__

/* fatal error macro */
#define ERROR(str) do {\
		fprintf(stderr, F("%s: %s\n"),\
			(str), strerror(errno));\
		exit(EXIT_FAILURE);\
	} while(0)

int main(int argc, char** argv)
{
	char *program = "./a.out";  /* defaults to a.out in local dir */
	int opt;

	/* getopt use.  See getopt(3) for instructions */
	while ((opt = getopt(argc, argv, "r:")) != EOF) {
		switch (opt) {
		case 'r': program = optarg; break;
		}
	}

	/* shift all the processed parameters out */
	argc -= optind; argv += optind;

	/* get our pid to use in traces */
	pid = getpid();

	if (argc == 1) {
		/* only one parameter, save the fork() call */
		printf(F("about to exec: %s %s\n"),
			program, argv[0]);
		execlp(program,
			program, argv[0], NULL);
		ERROR("execlp()");
		/* NOTREACHED */
	} else {
		pid_t chld;
		int i;
		for (i = 0; i < argc; i++) {
			chld = fork();
			if (chld < 0) {
				ERROR("fork()");
				/* NOTREACHED */
			}
			if (!chld) { /* child */
				printf(F("about to call: %s %s\n"),
					program, argv[i]);
				execlp(program,
					program, argv[i], NULL);
				ERROR("execlp()");
				/* NOTREACHED */
			}
		}
		/* NOW, AFTER ALL FORKS/EXECS HAVE BEEN DONE,
		 * JUST DO ALL THE WAITS.  wait() gives an
		 * error if no children exist to wait for, so
		 * we wait() until we get an error here.  */
		int status;
		while ((chld = wait(&status)) > 0) {
			/* just change this printf to a continue;
			 * if you don't want to print the result. */
			printf(F("wait() => child %d (status = %d)\n"),
				chld, status);
		}
	}
	printf("%d: END OF PROGRAM\n", pid);
}
