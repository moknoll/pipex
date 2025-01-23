/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mknoll <mknoll@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 09:19:33 by mknoll            #+#    #+#             */
/*   Updated: 2025/01/23 13:44:11 by mknoll           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void ft_exec(char *cmd, char *env[])
{
	char *path;
	char **args;

	// Zerlege die Kommandozeile in Befehle und Argumente
	args = ft_split(cmd, ' '); // Beispiel: cmd = "ls -l" -> args = {"ls", "-l", NULL}

	// Finde den vollständigen Pfad des Befehls
	path = get_path(args[0], env); // Sucht nach "/bin/ls", wenn cmd = "ls"
	if (!path || execve(path, args, env) == -1)
	{
		perror("Fehler bei execve");
		exit(EXIT_FAILURE); // Prozess beenden, wenn execve fehlschlägt
	}
}


void	parent_process(char *argv[], int* fds, char *env[])
{
	int outfile;

	outfile = open_fd(argv[4], 1);
	dup2(outfile, STDOUT_FILENO);
	dup2(fds[0], STDIN_FILENO);
	close(fds[0]);
	ft_exec(argv[3], env);
}

void	child_process(char *argv[], int* fds, char *env[])
{
	int infile;

	infile = open_fd(argv[1], 0);
	dup2(infile, STDIN_FILENO);
	dup2(fds[1], STDOUT_FILENO);
	close(fds[1]);
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
	else
	{
		parent_process(argv, fds, env);
		waitpid(pid, NULL, 0);
	}
}
