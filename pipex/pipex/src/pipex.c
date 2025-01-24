/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moritzknoll <moritzknoll@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 09:19:33 by mknoll            #+#    #+#             */
/*   Updated: 2025/01/24 09:12:25 by moritzknoll      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


void parent_process(char *argv[], int *fds, char *env[])
{
	int outfile;

	outfile = open_fd(argv[4], 1);
	dup2(outfile, STDOUT_FILENO);
	dup2(fds[0], STDIN_FILENO);
	close(outfile);
	close(fds[0]);
	close(fds[1]); // Schließe ungenutzte Deskriptoren
	ft_exec(argv[3], env);
}

void child_process(char *argv[], int *fds, char *env[])
{
	int infile;

	infile = open_fd(argv[1], 0);
	dup2(infile, STDIN_FILENO);
	dup2(fds[1], STDOUT_FILENO);
	close(infile);
	close(fds[0]); // Schließe ungenutzte Deskriptoren
	close(fds[1]);
	ft_exec(argv[2], env);
}


int main(int argc, char *argv[], char *env[])
{
	int fds[2];
	pid_t pid;

	if (argc != 5)
		error_handling(1);
	if (pipe(fds) == -1)
	{
		perror("pipe error");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork error");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		child_process(argv, fds, env);
	else
	{
		parent_process(argv, fds, env);
		waitpid(pid, NULL, 0);
		close(fds[0]); // Schließe ungenutzte Deskriptoren im Elternprozess
		close(fds[1]);
	}
	return (0);
}
