/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moritzknoll <moritzknoll@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:32:42 by moritzknoll       #+#    #+#             */
/*   Updated: 2025/01/18 11:36:21 by moritzknoll      ###   ########.fr       */
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
