/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_add_content.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkanyilm <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 02:39:01 by kkanyilm          #+#    #+#             */
/*   Updated: 2024/02/13 15:38:17 by kkanyilm         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../libft/libft.h"
#include <stdlib.h>

static void	free_contents(t_content **contents)
{
	int	i;

	i = 0;
	while (*contents && (*contents)[i].content)
	{
		free((*contents)[i].content);
		i++;
	}
	free(*contents);
}

static void	free_new_contents(t_content *new_content, int limit)
{
	int	i;

	i = 0;
	while (i < limit)
	{
		free(new_content[i].content);
		i++;
	}
	free(new_content);
}

static t_content	*first_content(char *content, enum e_token_type type,
	int is_append)
{
	t_content	*new_content;

	new_content = malloc(sizeof(t_content) * 2);
	if (!new_content)
		return (free(content), NULL);
	new_content[0].content = ft_strdup(content);
	if (!new_content[0].content)
		return (free(content), free(new_content), NULL);
	new_content[0].type = type;
	new_content[0].is_append = is_append;
	new_content[1].content = NULL;
	new_content[1].type = 0;
	new_content[1].is_append = 0;
	free(content);
	return (new_content);
}

static int	add_all_contents(t_content **cs, t_content *new_content)
{
	int	i;

	i = 0;
	while ((*cs)[i].content)
	{
		new_content[i].content = ft_strdup((*cs)[i].content);
		if (!new_content[i].content)
			return (free_new_contents(new_content, i), 0);
		new_content[i].type = (*cs)[i].type;
		new_content[i].is_append = (*cs)[i].is_append;
		i++;
	}
	return (1);
}

t_content	*add_content(t_content **cs, char *c, enum e_token_type type,
	int is_append)
{
	t_content	*new_content;
	int			i;

	i = 0;
	if (!*cs)
		return (first_content(c, type, is_append));
	while ((*cs)[i].content)
		i++;
	new_content = malloc(sizeof(t_content) * (i + 2));
	if (!new_content)
		return (free_contents(cs), free(c), NULL);
	if (!add_all_contents(cs, new_content))
		return (free(c), NULL);
	new_content[i].content = ft_strdup(c);
	if (!new_content[i].content)
		return (free_contents(cs), free(c),
			free_new_contents(new_content, i), NULL);
	new_content[i].type = type;
	new_content[i].is_append = is_append;
	new_content[i + 1].content = NULL;
	new_content[i + 1].type = 0;
	new_content[i + 1].is_append = 0;
	return (free_contents(cs), free(c), new_content);
}
