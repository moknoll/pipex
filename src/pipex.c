/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mknoll <mknoll@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 09:19:33 by mknoll            #+#    #+#             */
/*   Updated: 2025/03/18 12:27:32 by mknoll           ###   ########.fr       */
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

int	pipex(char *argv[], char *env[])
{
	int		fds[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status2;

	if (pipe(fds) == -1)
		exit(1);
	pid1 = fork();
	if (pid1 == -1)
		exit(1);
	if (pid1 == 0)
		child_process(argv, fds, env);
	pid2 = fork();
	if (pid2 == -1)
		exit(1);
	if (pid2 == 0)
		parent_process(argv, fds, env);
	close(fds[0]);
	close(fds[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &status2, 0);
	if (WIFEXITED(status2))
		return (WEXITSTATUS(status2));
	return (1);
}

int	main(int argc, char *argv[], char *env[])
{
	if (argc != 5)
		error_handling(1);
	return (pipex(argv, env));
}


