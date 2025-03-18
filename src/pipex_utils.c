/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mknoll <mknoll@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 09:11:48 by moritzknoll       #+#    #+#             */
/*   Updated: 2025/02/19 12:28:18 by mknoll           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_handling(int code)
{
	if (code == 1)
	{
		ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 outfile\n", 2);
		exit(1);
	}
	else
	{
		ft_putstr_fd("Usage: command not found\n", 2);
		exit(1);
	}
}

int	open_fd(char *file, int in_or_out)
{
	int	result;

	result = 0;
	if (in_or_out == 0)
		result = open(file, O_RDONLY);
	else if (in_or_out == 1)
		result = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (result == -1)
	{
		perror("open error");
		exit(1);
	}
	return (result);
}

void	read_file(int fd)
{
	char	buffer[1024];
	ssize_t	bytes_r;

	bytes_r = read(fd, buffer, sizeof(buffer));
	while (bytes_r > 0)
	{
		write(STDOUT_FILENO, buffer, bytes_r);
	}
	if (bytes_r == -1)
	{
		perror("reading error");
	}
}

void	ft_exec(char *cmd, char *env[])
{
	char	*path;
	char	**args;

	if (!cmd | !*cmd)
		error_handling(2);
	args = ft_split(cmd, ' ');
	if (!args | !args[0])
	{
		ft_free_tab(args);
		error_handling(2);
	}
	path = get_path(args[0], env);
	if (!path || execve(path, args, env) == -1)
	{
		perror("command not found");
		ft_free_tab(args);
		free(path);
		exit(127);
	}
	ft_free_tab(args);
	free(path);
}
