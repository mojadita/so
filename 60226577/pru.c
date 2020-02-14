#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h> 

pid_t my_fork()
{
	pid_t chld = fork();
	if (chld > 0) {
		/* only the parent shows this */
		printf("[pid=%d, child=%d] forked!\n",
			getpid(), chld);
	}
	return chld;
}

int main() 
{ 
	printf("[pid=%d] Hello, world\n", getpid());

    if (my_fork() && (!my_fork())) { 
        if (my_fork() || my_fork()) {
            my_fork(); 
        } 
    } 

	pid_t pid;
	int status;

	while((pid = wait(&status)) >= 0) {
    	printf("[pid=%d, child=%d]: child ended with status=%d\n",
			getpid(), pid, status);
	}
	printf("[pid=%d]: Hello friend!\n", getpid());

    return 0; 
}
