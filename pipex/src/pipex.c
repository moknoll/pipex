/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moritzknoll <moritzknoll@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 09:19:33 by mknoll            #+#    #+#             */
/*   Updated: 2025/01/22 12:39:52 by moritzknoll      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_exec(char *cmd, char *env[])
{
	
}

void	parent_process(char *argv[], int* fds, char *env[])
{
	int outfile;

	outfile = open_fd(argv[4], 1);
	dup2(outfile, 1);
	dup2(fds[1], 1);
	close(fds[1]);
	ft_exec(argv[3], env);
}

void	child_process(char *argv[], int* fds, char *env[])
{
	int infile;

	infile = open_fd(argv[1], 0);
	dup2(infile, 0);
	dup2(fds[0], 0);
	close(fds[0]);
	ft_exec(argv[2], env);
}

int main(int argc, char *argv[], char *env[])
{
	int fds[2];
	pid_t pid;

	pipe(fds);
	if (argc != 5)
		error_handling(1);
	if (pipe(fds) == -1)
		exit(-1);
	pid = fork();
	if (pid == -1)
		exit(-1);
	if (pid == 0)
		child_process(argv, fds, env);
	parent_process(argv, fds, env);
}
