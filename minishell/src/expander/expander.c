/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkanyilm <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 15:54:12 by kkanyilm          #+#    #+#             */
/*   Updated: 2024/02/13 18:46:53 by kkanyilm         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../libft/libft.h"
#include <stdlib.h>

t_token	*expand(t_token *tokens, t_env *env)
{
	int		i;
	char	*tmp;

	i = 0;
	while (tokens[i].content)
	{
		if (tokens[i].type == WORD || tokens[i].type == DOUBLE_QUOTE)
		{
			if (!(i > 0 && ft_strncmp(tokens[i - 1].content, "<<", 3) == 0))
			{
				tmp = (get_env(env, tokens[i].content));
				if (!tmp)
					return (print_error(SHELL_NAME, ERR_MALLOC),
						free_tokens(&tokens), NULL);
				free(tokens[i].content);
				tokens[i].content = tmp;
			}
		}
		i++;
	}
	return (tokens);
}
