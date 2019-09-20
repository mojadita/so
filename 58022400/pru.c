/* pru.c -- program to show raw input from the terminal.
 * Author: Luis Colorado <luiscoloradourcola@gmail.comª
 * Date: Fri Sep 20 08:46:06 EEST 2019
 * Copyright: (C) 2019 Luis Colorado.  All rights reserved.
 * License: BSD.
 */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>  /* see termios(3) for a description on terminal conf */

#define F(_fmt) __FILE__":%d:%s: " _fmt, __LINE__, __func__

/* this function switches the terminal into raw mode and returns a malloc(3)ed
 * terminal configuration, so it can be later restored. BEWARE that the returned
 * configuration info must be deallocated by free(3) once it's not needed anymore.
 * In case of failure of any system call, the function returns NULL, and errno is
 * set to the failing cause.  */
struct termios *set_raw(int fd)
{
    struct termios *ret = malloc(sizeof *ret), cfg;
    if (!ret) return NULL;

    int res = tcgetattr(fd, &cfg);
    if (res < 0) goto error;

    *ret = cfg; /* save it for return */

    cfmakeraw(&cfg);

    /* set it after all buffered characters in the driver have drained out */
    res = tcsetattr(fd, TCSADRAIN, &cfg);
    if (res < 0) goto error;

    return ret;

error:
    free(ret);
    return NULL;
} /* set_raw */

/* restores the configuration back to the associated file descriptor */
int restore_cfg(int fd, struct termios *cf)
{
    /* set it after all buffered characters in the driver have drained out */
    return tcsetattr(fd, TCSADRAIN, cf);
} /* restore_cfg */ 

int main()
{
    struct termios *cfg = set_raw(fileno(stdin));
    if (!cfg) {
        fprintf(stderr, F("stdin: %s\n"),
                strerror(errno));
    }

    setbuf(stdin, NULL); /* stdin unbuffered */
    setbuf(stdout, NULL); /* stdout unbuffered */

    /* BEWARE that raw mode doesn't process any characters, so no Ctrl-C(interrupt), Ctrl-D(EOF), etc.
     * will be available, only if you read from a file, you'll get EOF, but you'll not be able to produce
     * that on the terminal, you'll need to swith to another console and kill the process. */
    int c;
    while ((c = getchar()) != EOF && c != '\033') {  /* ESCAPE key('\033') is a safeguard to end input */
        /* print the input char as an hex number */
        printf("[%02x]", c);
    }

    if (cfg) { /* if we were able to set the terminal to raw mode */
        /* restore config */
        restore_cfg(fileno(stdin), cfg);

        /* and free it */
        free(cfg);
    }

    exit(EXIT_SUCCESS);
} /* main */
