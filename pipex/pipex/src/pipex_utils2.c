/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moritzknoll <moritzknoll@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:32:42 by moritzknoll       #+#    #+#             */
/*   Updated: 2025/01/24 09:12:57 by moritzknoll      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_tab(char **tab)
{
	int i;

	if (!tab)
		return;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}



char *get_env_path(char *env[])
{
	int i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0) // Suchen in env[] nach PATH=
		{
			return (env[i] + 5); // Überspringe "PATH=" und gebe den Rest zurück
		}
		i++;
	}
	return (NULL); // Falls nicht gefunden
}

char **split_path(char *envp[])
{
	char *envp_path;
	char **all_paths;

	envp_path = get_env_path(envp);
	all_paths = ft_split(envp_path, ":");

	return (all_paths);
}

char *get_path(char *cmd, char *all_paths[])
{
	int i;
	char *full_path;
	char *temp;

	i = 0;
	while (all_paths && all_paths[i]) // Fehlerprüfung für NULL
	{
		temp = ft_strjoin(all_paths[i], "/");
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(full_path, F_OK | X_OK) == 0) // Prüfen, ob Datei existiert und ausführbar ist
		{
			ft_free_tab(all_paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	ft_free_tab(all_paths);
	return (NULL); // Wenn kein gültiger Pfad gefunden wurde
}
