#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sched.h>
#include <stdlib.h>

#define STACK_SIZE (1024*1024)

char* const child_args[]={"/bin/bash",NULL};

int child_main(void* args){
	printf("子进程开始\n");
	execv(child_args[0],child_args);
	printf("子进程结束\n");
	return 1;
}

int main(int argc, char const *argv[])
{
	void* stack;
	stack=malloc(STACK_SIZE);
	printf("主进程开始\n");
	int pid=clone(child_main,stack+STACK_SIZE,CLONE_NEWIPC | SIGCHLD,NULL);
	printf("%d\n",pid);
	waitpid(pid,NULL,0);
	printf("退出\n");
	return 0;
}