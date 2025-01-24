/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moritzknoll <moritzknoll@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 09:11:48 by moritzknoll       #+#    #+#             */
/*   Updated: 2025/01/24 09:13:06 by moritzknoll      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "pipex.h"

void error_handling(int code)
{
	if (code == 1)
	{
		ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 outfile\n", 2);
		exit(EXIT_FAILURE);
	}
}

int	open_fd(char *file, int in_or_out)
{
	int result;

	// result = 0;
	if (in_or_out == 0)
		result = open(file, O_RDONLY);
	else if (in_or_out == 1)
		result = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (result == -1)
	{
		perror("open error");
		exit(EXIT_FAILURE);
	}
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

void ft_exec(char *cmd, char *env[])
{
	char *path;
	char **args;

	args = ft_split(cmd, ' '); // Zerlege die Kommandozeile in Befehle und Argumente
	path = get_path(args[0], env); // Finde den vollständigen Pfad des Befehls
	if (!path || execve(path, args, env) == -1)
	{
		perror("execve error");
		ft_free_tab(args); // Speicher freigeben
		free(path);
		exit(EXIT_FAILURE); // Prozess beenden, wenn execve fehlschlägt
	}
	ft_free_tab(args); // Speicher freigeben
	free(path);
}
