/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkanyilm <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 16:17:55 by kkanyilm          #+#    #+#             */
/*   Updated: 2024/02/13 18:46:32 by kkanyilm         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../libft/libft.h"

int	add_token_app_two(t_token *tokens, t_token **new_tokens, int i)
{
	char	*tmp;

	tmp = ft_strdup(tokens[i].content);
	if (!tmp)
		return (print_error(SHELL_NAME, ERR_MALLOC),
			free_tokens(&tokens), 1);
	*new_tokens = add_token(new_tokens, tmp,
			tokens[i].type, tokens[i].is_append);
	if (!*new_tokens)
		return (print_error(SHELL_NAME, ERR_MALLOC),
			free_tokens(&tokens), 1);
	return (0);
}

int	add_token_app(t_token *tokens, t_token **new_tokens, int i, int j)
{
	char	*tmp;
	char	*tmp2;
	int		k;

	tmp = ft_strdup(tokens[i].content);
	if (!tmp)
		return (print_error(SHELL_NAME, ERR_MALLOC),
			free_tokens(&tokens), 1);
	k = j;
	while (j > 0)
	{
		tmp2 = ft_strjoin(tmp, tokens[i + k - j + 1].content);
		if (!tmp2)
			return (print_error(SHELL_NAME, ERR_MALLOC),
				free_tokens(&tokens), 1);
		free(tmp);
		tmp = tmp2;
		j--;
	}
	*new_tokens = add_token(new_tokens, tmp,
			tokens[i].type, tokens[i].is_append);
	if (!*new_tokens)
		return (print_error(SHELL_NAME, ERR_MALLOC),
			free_tokens(&tokens), 1);
	return (0);
}

int	_appender(t_token *tokens, int *i, t_token **new_tokens)
{
	int	j;
	int	k;

	j = 0;
	while (tokens[*i + j + 1].is_append)
		j++;
	k = j;
	if (j > 0)
	{
		if (add_token_app(tokens, new_tokens, *i, j))
			return (1);
	}
	else
		if (add_token_app_two(tokens, new_tokens, *i))
			return (1);
	*i += k + 1;
	return (0);
}

t_token	*appender(t_token *tokens)
{
	t_token	*new_tokens;
	int		i;

	i = 0;
	new_tokens = NULL;
	while (tokens[i].content)
		if (_appender(tokens, &i, &new_tokens))
			return (NULL);
	free_tokens(&tokens);
	return (new_tokens);
}
