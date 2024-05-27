#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

#include <unistd.h>
#include <sched.h>

int g = 2;

int sub_func(void *arg)
{
	g++;
	printf("PID(%d): Child g = %d\n", getpid(), g);


	return 0;
}

int main(void)
{
	int pid, cpid;
	int child_stack[4096];

	int l = 3;

	printf("PID(%d): Parent g = %d, l = %d\n",
		getpid(), g, l);

	if ((cpid = clone(sub_func, (void *) (child_stack + 4095),
		   CLONE_NEWNS | SIGCHLD, NULL)) == -1)
		perror("failed to clone(): ");


	waitpid(cpid, NULL, 0);
	printf("PID(%d): Parent g = %d, l = %d\n",
		getpid(), g, l);

	return 0;
}