/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mknoll <mknoll@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:32:42 by moritzknoll       #+#    #+#             */
/*   Updated: 2025/01/24 10:08:18 by mknoll           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_tab(char **tab)
{
	int	i;

	if (!tab)
		perror("no tab");
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*get_env_path(char *env[])
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			return (env[i] + 5);
		}
		i++;
	}
	return (NULL);
}

char	**split_path(char *envp[])
{
	char	*envp_path;
	char	**all_paths;

	envp_path = get_env_path(envp);
	if (!envp_path)
		return (NULL);
	all_paths = ft_split(envp_path, ':');
	return (all_paths);
}

char	*get_path(char *cmd, char *envp[])
{
	int		i;
	char	*full_path;
	char	*temp;
	char	**all_paths;

	all_paths = split_path(envp);
	i = 0;
	while (all_paths && all_paths[i])
	{
		temp = ft_strjoin(all_paths[i], "/");
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(full_path, F_OK | X_OK) == 0)
		{
			ft_free_tab(all_paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	ft_free_tab(all_paths);
	return (NULL);
}
