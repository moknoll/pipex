/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mknoll <mknoll@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 10:51:27 by mknoll            #+#    #+#             */
/*   Updated: 2025/01/23 13:44:04 by mknoll           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <string.h>
# include <stdio.h> 
# include <stdlib.h>
# include "libft.h"

void	child_process(char *argv[], int* fds, char *env[]);
void	parent_process(char *argv[], int* fds, char *env[]);
void	ft_exec(char *cmd, char *env[]);
void	error_handling(int n_exit);
void	open_fd(char *file, int in_or_out);
void	read_file(int fd);
void	ft_free_tab(char *path[]);
char	*get_path(char *cmd, char *env[]);
char	*get_env_path(char *env[]);

#endif