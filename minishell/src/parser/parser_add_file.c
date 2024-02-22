/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_add_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkanyilm <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 14:01:24 by kkanyilm          #+#    #+#             */
/*   Updated: 2024/02/13 14:52:42 by kkanyilm         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../libft/libft.h"
#include <stdlib.h>

void	free_files(t_file **files)
{
	int	i;

	i = 0;
	while (*files && (*files)[i].name)
	{
		free((*files)[i].name);
		i++;
	}
	free(*files);
}

static void	free_new_files(t_file *new_files, int limit)
{
	int	i;

	i = 0;
	while (i < limit)
	{
		free(new_files[i].name);
		i++;
	}
	free(new_files);
}

t_file	*first_file(char *name, int double_op)
{
	t_file	*new_files;

	new_files = malloc(sizeof(t_file) * 2);
	if (!new_files)
		return (free(name), NULL);
	new_files[0].name = ft_strdup(name);
	if (!new_files[0].name)
		return (free(name), free(new_files), NULL);
	new_files[0].fd = -1;
	new_files[0].double_op = double_op;
	new_files[1].name = NULL;
	new_files[1].fd = -1;
	free(name);
	return (new_files);
}

static int	add_old_files(t_file **fs, t_file *new_files)
{
	int	i;

	i = 0;
	while ((*fs)[i].name)
	{
		new_files[i].name = ft_strdup((*fs)[i].name);
		if (!new_files[i].name)
			return (free_files(fs), free_new_files(new_files, i), 0);
		new_files[i].fd = (*fs)[i].fd;
		new_files[i].double_op = (*fs)[i].double_op;
		i++;
	}
	return (1);
}

t_file	*add_file(t_file **files, char *name, int double_op)
{
	t_file	*new_files;
	int		i;

	i = 0;
	if (!*files)
		return (first_file(name, double_op));
	while ((*files)[i].name)
		i++;
	new_files = malloc(sizeof(t_file) * (i + 2));
	if (!new_files)
		return (free_files(files), free(name), NULL);
	if (!add_old_files(files, new_files))
		return (free(name), NULL);
	new_files[i].name = ft_strdup(name);
	if (!new_files[i].name)
		return (free_files(files), free(name),
			free_new_files(new_files, i), NULL);
	new_files[i].fd = -1;
	new_files[i].double_op = double_op;
	new_files[i + 1].name = NULL;
	new_files[i + 1].fd = -1;
	new_files[i + 1].double_op = 0;
	return (free_files(files), free(name), new_files);
}
