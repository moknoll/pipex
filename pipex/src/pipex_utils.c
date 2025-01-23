/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mknoll <mknoll@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:32:42 by moritzknoll       #+#    #+#             */
/*   Updated: 2025/01/23 13:41:31 by mknoll           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_handling(int n_exit)
{
	if (n_exit == 1)
		ft_putstr_fd("Not the correct amount of arguments", 2);
	exit(0);
}

void	open_fd(char *file, int in_or_out)
{
	int result;

	if (in_or_out == 0)
		result = open(file, O_RDONLY, 0777);
	if (in_or_out == 1)
		result = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (result == -1)
		exit(0);
	return (result);
}

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

void	ft_free_tab(char *path[])
{
	int i;

	i = 0;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
	return;
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