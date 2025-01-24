/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mknoll <mknoll@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:29:21 by moritzknoll       #+#    #+#             */
/*   Updated: 2025/01/24 10:37:23 by mknoll           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>

void	error_handling(int code);
void	child_process(char *argv[], int *fds, char *env[]);
void	parent_process(char *argv[], int *fds, char *env[]);
void	ft_exec(char *cmd, char *env[]);
char	*get_path(char *cmd, char *env[]);
char	*get_env_path(char *env[]);
void	read_file(int fd);
int		open_fd(char *file, int in_or_out);
void	ft_free_tab(char **tab);
void	wait_for_child(int i);

#endif
