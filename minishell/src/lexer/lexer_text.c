/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_text.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkanyilm <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 16:14:12 by kkanyilm          #+#    #+#             */
/*   Updated: 2024/02/12 17:13:18 by kkanyilm         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../inc/minishell.h"

static int	other_len(char *chr)
{
	if (*chr == '(' || *chr == ')')
		return (1);
	else if (*chr == '<' && *(chr + 1) != '<')
		return (1);
	else if (*chr == '<' && *(chr + 1) == '<')
		return (2);
	else if (*chr == '>' && *(chr + 1) != '>')
		return (1);
	else if (*chr == '>' && *(chr + 1) == '>')
		return (2);
	else if (*chr == '|' && *(chr + 1) != '|')
		return (1);
	else if (*chr == '|' && *(chr + 1) == '|')
		return (2);
	else if (*chr == '&' && *(chr + 1) == '&')
		return (2);
	return (0);
}

static int	text_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strchr(" \t\n", str[i]))
			break ;
		else if (other_len(&str[i]) > 0)
			break ;
		else if (ft_strchr("\'\"", str[i]))
			break ;
		i++;
	}
	return (i);
}

int	check_isappend(char *input, int *i)
{
	if (*i == 0)
		return (0);
	return (ft_strchr(" \t|", input[*i - 1]) == NULL);
}

int	get_token_text(char *input, int *i, t_token **token)
{
	int		start;
	int		len;
	char	*token_str;

	len = text_len(&input[*i]);
	if (len > 0)
	{
		start = *i;
		token_str = ft_substr(input, start, len);
		if (!token_str)
			return (print_error(SHELL_NAME, ERR_MALLOC));
		*token = add_token(token, token_str, WORD, check_isappend(input, i));
		*i = start + len;
		return (1);
	}
	return (0);
}
