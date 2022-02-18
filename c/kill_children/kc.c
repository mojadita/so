#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_CHILDREN 10

pid_t chld_pids[MAX_CHILDREN];
size_t chld_pids_sz = 0;

void kill_children(int sig, int delay);
void signal_handler(int sig);

int main()
{
    while (chld_pids_sz < MAX_CHILDREN) {
        pid_t chld_id = fork();
        if (chld_id < 0) { /* error in fork() */
            fprintf(stderr,
                    "Error in fork: %s (errno == %d)\n",
                    strerror(errno), errno);
            kill_children(SIGHUP, 0); /* kill all children with
                                       * no delay */
            break; /* stop processing */
        } else if (chld_id == 0) { /* child */
			/* avoid signal SIGHUP so no child is killed when the
			 * process group leader is killed.  This is sent
			 * automatically by the kernel to end a job. */
			signal(SIGHUP, SIG_IGN);
            for(;;) {
				/* print our pid on stdout each second to
				 * indicate we are alive. */
                printf("[%d]", getpid());
                fflush(stdout); /* force buffer flush */
                sleep(1);
            }
            /* NOTREACHED */
        } else { /* parent */
            printf("Parent: started child %d\n", chld_id);
            chld_pids[chld_pids_sz++] = chld_id;
        }
    }
    signal(SIGHUP, signal_handler);
    /* now we wait for all children to finish, no need to know
     * the pids, as we are waiting until wait(2) returns an error
     * (no children to wait for) */
    int chld_id, status;
    while ((chld_id = wait(&status)) >= 0) {
        if (WIFEXITED(status)) {
            printf("Child %d exited with status %d\n",
                    chld_id, WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Child %d was killed with signal %d\n",
                    chld_id, WTERMSIG(status));
            if (WCOREDUMP(status)) {
                printf("Child %d dumped a core file\n",
                    chld_id);
            }
        }
    }
} /* main */

void kill_children(int sig, int delay)
{
    printf("kill_children: Using delay %d\n", delay);
    for (int i = 0; i < chld_pids_sz; ++i) {
        if (delay > 0) { /* only sleep if delay > 0 */
            sleep(delay);
        }
        printf("Killing pid=%d\n", chld_pids[i]);
        int res = kill(chld_pids[i], sig);
        if (res < 0) {
            printf("Error killing pid %d: %s (errno = %d)\n",
                    chld_pids[i], strerror(errno), errno);
        }
    }
}

void signal_handler(int unused)
{
    kill_children(SIGINT, 3);
}
