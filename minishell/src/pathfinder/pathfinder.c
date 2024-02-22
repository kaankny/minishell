/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkanyilm <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 14:46:33 by fduvan            #+#    #+#             */
/*   Updated: 2024/02/13 18:49:01 by kkanyilm         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../libft/libft.h"
#include <stdlib.h>

char	*_get_path(char **paths, int i, char *command)
{
	char	*path;

	while (paths && paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		if (!path)
			return (free_double_char(paths), NULL);
		path = ft_strjoin_free(path, command);
		if (!path)
			return (free_double_char(paths), NULL);
		if (access(path, F_OK) == 0)
			return (free_double_char(paths), path);
		free (path);
		i++;
	}
	return (NULL);
}

char	*get_path(char *command, t_env *env)
{
	int		i;
	char	**paths;
	char	*path;

	i = 0;
	while (env[i].name)
	{
		if (ft_strncmp(env[i].name, "PATH", ft_strlen("PATH") + 1) == 0)
			break ;
		i++;
	}
	if (!is_exist_env("PATH", env))
		return (ft_strdup(""));
	paths = ft_split(env[i].value, ':');
	if (!paths)
		return (NULL);
	i = 0;
	path = _get_path(paths, i, command);
	if (path)
		return (path);
	return (free_double_char(paths), ft_strdup(command));
}
