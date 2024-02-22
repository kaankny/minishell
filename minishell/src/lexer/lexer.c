/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkanyilm <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 15:02:10 by kkanyilm          #+#    #+#             */
/*   Updated: 2024/02/19 15:55:54 by kkanyilm         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../inc/minishell.h"

static t_token	*tokens_init_error(void)
{
	return (print_error(SHELL_NAME,
			"syntax error near unexpected token `newline'"), NULL);
}

static t_token	*tokens_init(char *input)
{
	t_token	*tokens;
	int		i;

	i = 0;
	tokens = NULL;
	while (input && input[i])
	{
		if (get_token_pipe(input, &i, &tokens) == FT_FAILURE)
			break ;
		if (get_token_bracket(input, &i, &tokens) == FT_FAILURE)
			break ;
		if (get_token_redirection(input, &i, &tokens) == FT_FAILURE)
			break ;
		if (get_token_quote(input, &i, &tokens) == FT_FAILURE)
			break ;
		if (get_token_text(input, &i, &tokens) == FT_FAILURE)
			break ;
		while (input[i] && ft_strchr(" \t\n", input[i]))
			i++;
	}
	if (input[i] != '\0')
		return (free_tokens(&tokens), NULL);
	if (tokens && tokens[0].type == PIPE)
		return (free_tokens(&tokens), tokens_init_error());
	return (tokens);
}

t_token	*lexer(char *input)
{
	t_token	*tokens;

	tokens = tokens_init(input);
	return (tokens);
}
