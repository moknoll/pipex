/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moritzknoll <moritzknoll@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 09:19:33 by mknoll            #+#    #+#             */
/*   Updated: 2025/01/23 12:45:11 by moritzknoll      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	read_file(int fd)
{
	char buffer[1024];
	ssize_t bytes_r;

	while ((bytes_r = read(fd, buffer, sizeof(buffer))) > 0)
	{
		write(STDOUT_FILENO, buffer, bytes_r);
	}
	if (bytes_r == -1)
	{
		perror("reading error");
	}
}

char *get_path(char *cmd, char *env[])
{
	int i = 0;
	char **paths = ft_split(get_path_env(env), ':'); // Zerlege PATH in einzelne Verzeichnisse
	char *full_path;
	char *temp;

	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/"); // Hänge "/" an das Verzeichnis an
		full_path = ft_strjoin(temp, cmd); // Füge den Befehl an, z. B. "/bin/ls"
		free(temp);
		if (access(full_path, F_OK | X_OK) == 0) // Prüfe, ob die Datei existiert und ausführbar ist
		{
			ft_free_tab(paths); // Speicher freigeben
			return (full_path); // Pfad zurückgeben, z. B. "/bin/ls"
		}
		free(full_path); // Speicher freigeben, wenn der aktuelle Pfad falsch ist
		i++;
	}
	ft_free_tab(paths); // Speicher freigeben, wenn kein Pfad gefunden wurde
	return (NULL); // Wenn kein gültiger Pfad gefunden wurde
}


char *get_env_path(char *env[])
{
	int i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)	// suchen in env[] nach PATH=
		{
			return (env[i] + 5); // Überspringe "PATH=" und gebe den rest zurück
		}
	}
	return (NULL);	// falls nicht gefunden
}
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
