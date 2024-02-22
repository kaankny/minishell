/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_get_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkanyilm <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:24:29 by kkanyilm          #+#    #+#             */
/*   Updated: 2024/02/13 18:46:54 by kkanyilm         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../inc/minishell.h"

int	get_token_pipe(char *input, int *i, t_token **token)
{
	char	*token_str;

	if (input[*i] == '|')
	{
		token_str = ft_strdup("|");
		if (!token_str)
			return (print_error(SHELL_NAME, ERR_MALLOC));
		*token = add_token(token, token_str, PIPE, 0);
		if (!*token)
			return (print_error(SHELL_NAME, ERR_MALLOC));
		(*i)++;
		return (1);
	}
	return (0);
}

int	get_token_bracket(char *input, int *i, t_token **token)
{
	char	*token_str;

	if (input[*i] == '(')
	{
		token_str = ft_strdup("(");
		if (!token_str)
			return (print_error(SHELL_NAME, ERR_MALLOC));
		*token = add_token(token, token_str, BRACKET_OPEN, 0);
		if (!*token)
			return (print_error(SHELL_NAME, ERR_MALLOC));
		(*i)++;
		return (1);
	}
	if (input[*i] == ')')
	{
		token_str = ft_strdup(")");
		if (!token_str)
			return (print_error(SHELL_NAME, ERR_MALLOC));
		*token = add_token(token, token_str, BRACKET_CLOSE, 0);
		if (!*token)
			return (print_error(SHELL_NAME, ERR_MALLOC));
		(*i)++;
		return (1);
	}
	return (0);
}

int	get_token_redirection(char *input, int *i, t_token **token)
{
	char	*token_str;
	int		len;

	len = 0;
	while (ft_isdigit(input[*i + len]))
		len++;
	if (input[*i + len] == '<' || input[*i + len] == '>')
	{
		if (input[*i + len + 1] == '<' || input[*i + len + 1] == '>')
			len++;
		len++;
		token_str = ft_substr(input, *i, len);
		if (!token_str)
			return (print_error(SHELL_NAME, ERR_MALLOC));
		if (input[*i + len - 1] == '>')
			*token = add_token(token, token_str, REDIR_OUT, 0);
		else if (input[*i + len - 1] == '<')
			*token = add_token(token, token_str, REDIR_IN, 0);
		if (!*token)
			return (print_error(SHELL_NAME, ERR_MALLOC));
		(*i) += len;
		return (1);
	}
	return (0);
}

static int	quote_len(char *str)
{
	char	mark;
	int		i;

	if (str == NULL || *str == '\0')
		return (0);
	if (ft_strchr("\'\"", str[0]) == NULL)
		return (0);
	mark = str[0];
	i = 1;
	while (str[i])
	{
		if (str[i] == mark)
			break ;
		i++;
	}
	if (str[i] != mark)
		return (print_error(SHELL_NAME, ERR_QUOTE));
	return (i + 1);
}

int	get_token_quote(char *input, int *i, t_token **token)
{
	char	*token_str;
	int		len;

	len = quote_len(input + *i);
	if (len == FT_FAILURE)
		return (FT_FAILURE);
	if (len > 0)
	{
		token_str = ft_substr(input, *i + 1, len - 2);
		if (!token_str)
			return (print_error(SHELL_NAME, ERR_MALLOC));
		if (input[*i] == '\'')
			*token = add_token(token, token_str, SINGLE_QUOTE,
					check_isappend(input, i));
		else if (input[*i] == '\"')
			*token = add_token(token, token_str, DOUBLE_QUOTE,
					check_isappend(input, i));
		if (!*token)
			return (print_error(SHELL_NAME, ERR_MALLOC));
		(*i) += len;
		return (1);
	}
	return (0);
}
