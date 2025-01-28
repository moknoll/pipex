/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mknoll <mknoll@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 09:19:33 by mknoll            #+#    #+#             */
/*   Updated: 2025/01/27 13:51:14 by mknoll           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parent_process(char *argv[], int *fds, char *env[])
{
	int	outfile;

	outfile = open_fd(argv[4], 1);
	dup2(outfile, STDOUT_FILENO);
	dup2(fds[0], STDIN_FILENO);
	close(outfile);
	close(fds[0]);
	close(fds[1]);
	ft_exec(argv[3], env);
}

void	child_process(char *argv[], int *fds, char *env[])
{
	int	infile;

	infile = open_fd(argv[1], 0);
	dup2(infile, STDIN_FILENO);
	dup2(fds[1], STDOUT_FILENO);
	close(infile);
	close(fds[0]);
	close(fds[1]);
	ft_exec(argv[2], env);
}

int	main(int argc, char *argv[], char *env[])
{
	int		fds[2];
	pid_t	pid;

	if (argc != 5)
		error_handling(1);
	if (pipe(fds) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
		child_process(argv, fds, env);
	else
	{
		waitpid(-1, NULL, 0);
		parent_process(argv, fds, env);
	}
	return (0);
}
