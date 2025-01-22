/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mknoll <mknoll@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 09:19:33 by mknoll            #+#    #+#             */
/*   Updated: 2025/01/22 15:49:56 by mknoll           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <unistd.h>


char *get_full_path(const char *cmd, char *env)
{
	int i;
	char *path_env;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		path_env = env[i]
	}
}

int	ft_exec(char *args[])
{
	
	execve("/usr/bin/ls", args, envp);
	perror("execve");
		exit(EXIT_FAILURE);
}

void	child_process(char *argv[], int *ends, char *env[])
{
	int outfile;

	outfile = open(argv[4], O_RDONLY, 0777);
	close(ends[1]);
	dup2(outfile, 1);
	close(outfile);
	dup2(ends[0], 0);
	close(ends[0]);
	ft_exec(argv[3]);
}

void	parent_process(char *argv[], int *ends, char *env[])
{
	int infile;
	
	infile = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	close(ends[0]);
	dup2(infile, 0);
	close(infile);
	dup2(ends[1], 1);
	close(ends[1]);
	ft_exec(argv[2]);
}

int main(int argc, char *argv[], char *env[])
{
	int end[2];
	pid_t pid;
	
	pipe(end);
	if (pipe(end) == -1)
		perror("pipe");
	pid = fork();
	if (pid == -1)
		exit(-1);
	if (pid == 0)
		child_process(argv, end, env);
	parent_process(argv, end, env);
}

int main()
{
	printf("PID before the execve is: %d\n", getpid());
	char *const args[] = {"ls", NULL};
	char *const envp[] = { NULL };
	
	execve("/usr/bin/ls", args, envp);
	perror("execve");
	printf("PID after the execve is: %d\n", getpid());
	return 1;
}