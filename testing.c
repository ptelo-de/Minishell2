#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int ac, char **av, char **envp)
{
	int pid;
	int fd[2];
	char *args[]= {"cat", NULL};

	pid = fork();
	waitpid(pid, NULL, 0);
	//fd[0] = open("a.txt", O_RDONLY | O_WRONLY);
	fd[0] = open("a.txt", O_RDONLY);
	//fd[1] = open("b.txt", O_RDONLY | O_WRONLY);
	fd[1] = open("b.txt", O_WRONLY);
	if (!fd[0] < 0  || fd[1] < 0)
		printf("OPEN RAISED ERROR");
	printf("before witpid call pid: %d\n", pid);
	printf("after witpid call pid: %d\n", pid);
	if (pid == 0) 
	{
		printf("IN CHILD PROCESS\n");
		dup2(fd[0], 0);
		dup2(fd[1], 1);
		execve("/bin/cat", args, envp);
	}


}