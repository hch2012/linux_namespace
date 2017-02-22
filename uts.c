#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sched.h>
#include <stdlib.h>

#define STACK_SIZE (1024*1024)


int child_main(void* args){
	printf("子进程开始\n");
	execv("/bin/bash",{"/bin/bash",NULL});
	return 1;
}

int main(int argc, char const *argv[])
{
	void* stack;
	stack=malloc(STACK_SIZE);
	printf("主进程开始\n");
	int pid=clone(child_main,stack+STACK_SIZE,CLONE_NEWUTS | SIGCHLD,NULL);
	waitpid(pid,NULL,0);
	return 0;
}