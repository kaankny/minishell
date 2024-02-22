/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkanyilm <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 02:04:32 by kkanyilm          #+#    #+#             */
/*   Updated: 2024/02/13 17:02:46 by kkanyilm         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../libft/libft.h"
#include <stdlib.h>

static t_token	*first_token(char *c, enum e_token_type t, int is_append)
{
	t_token	*new_tokens;

	new_tokens = malloc(sizeof(t_token) * 2);
	if (!new_tokens)
		return (free(c), NULL);
	new_tokens[0].content = ft_strdup(c);
	if (!new_tokens[0].content)
		return (free(c), free(new_tokens), NULL);
	new_tokens[0].type = t;
	new_tokens[0].is_append = is_append;
	new_tokens[1].content = NULL;
	new_tokens[1].type = 0;
	new_tokens[1].is_append = 0;
	free(c);
	return (new_tokens);
}

static void	free_new_tokens(t_token *new_tokens, int limit)
{
	int	i;

	i = 0;
	while (i < limit)
	{
		free(new_tokens[i].content);
		i++;
	}
	free(new_tokens);
}

static int	add_old_tokens(t_token **ts, t_token *new_tokens)
{
	int	i;

	i = 0;
	while ((*ts)[i].content)
	{
		new_tokens[i].content = ft_strdup((*ts)[i].content);
		if (!new_tokens[i].content)
			return (free_new_tokens(new_tokens, i), 0);
		new_tokens[i].type = (*ts)[i].type;
		new_tokens[i].is_append = (*ts)[i].is_append;
		i++;
	}
	return (1);
}

t_token	*add_token(t_token **ts, char *c, enum e_token_type t, int is_append)
{
	t_token	*new_tokens;
	int		i;

	i = 0;
	if (!*ts)
		return (first_token(c, t, is_append));
	while ((*ts)[i].content)
		i++;
	new_tokens = malloc(sizeof(t_token) * (i + 2));
	if (!new_tokens)
		return (free_tokens(ts), free(c), NULL);
	if (!add_old_tokens(ts, new_tokens))
		return (free(c), NULL);
	new_tokens[i].content = ft_strdup(c);
	if (!new_tokens[i].content)
		return (free_tokens(ts), free(c), free_new_tokens(new_tokens, i), NULL);
	new_tokens[i].type = t;
	new_tokens[i].is_append = is_append;
	new_tokens[i + 1].content = NULL;
	new_tokens[i + 1].type = 0;
	new_tokens[i + 1].is_append = 0;
	return (free_tokens(ts), free(c), new_tokens);
}
