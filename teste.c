#include <stdio.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h> //readline
#include <unistd.h> //getcwd, chdir
#include <stdlib.h> //exit malloc
#include <string.h>
#include <errno.h>  //for errno
#include <limits.h> //for PATH_MAX
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>

int main()
{
	char *args[] = {"/bin/ls", "", "src", NULL};

	execve(args[0], args, NULL); // Execute /bin/echo with "Hello, World!"
    perror("execve"); // Print error if execve fails
    return 1; // Return error code if execve fails
}