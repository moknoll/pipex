#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>



int main()
{
	int end[2];
	pid_t pid;
	char buf[30];

	if (pipe(end) == -1)
	{
		fprintf(stderr, "pipe");
	}
	pid = fork();
	if (pid < 0)
	{
		fprintf(stderr, "Fork failed\n");
		return 1;
	}
	else if(pid == 0)
	{
		close(end[0]);	// close the (unused) reading end of the pipe
		write(end[1], "this is a new message", 22);
		close(end[1]);	// close after writing 
			exit(EXIT_SUCCESS); 
	}
	else
	{
		close(end[1]);	// close unused writig end 
		read(end[0], buf, 22);
		printf("Parent received: %s\n", buf);
		close(end[0]);
		wait(NULL);		
	}
	return (EXIT_SUCCESS);
}  