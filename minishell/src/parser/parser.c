/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkanyilm <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:07:56 by kkanyilm          #+#    #+#             */
/*   Updated: 2024/02/19 14:52:20 by kkanyilm         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	reset_check(t_check *check)
{
	check->is_command = 1;
	check->check_flag = 1;
	check->j++;
	check->i++;
}

static int	get_cmd(t_cmd **cmds, t_token *tokens, t_check *check)
{
	if (tokens[check->i].type == WORD || tokens[check->i].type == SINGLE_QUOTE
		|| tokens[check->i].type == DOUBLE_QUOTE)
		return (get_cmd_word(cmds, tokens, check));
	else if (tokens[check->i].type == REDIR_IN)
		return (get_cmd_redir_in(cmds, tokens, check));
	else if (tokens[check->i].type == REDIR_OUT)
		return (get_cmd_redir_out(cmds, tokens, check));
	return (1);
}

static t_cmd	**content_null(t_cmd **cmds)
{
	print_error(SHELL_NAME, "syntax error: incomplete pipe");
	free_cmds(cmds);
	return (NULL);
}

static int	_parser(t_token *tokens, t_cmd **cmds, t_check *check)
{
	while (tokens[check->i].content)
	{
		if (tokens[check->i].type == PIPE)
		{
			reset_check(check);
			break ;
		}
		if (get_cmd(cmds, tokens, check) == FT_FAILURE)
			return (1);
		check->i++;
	}
	return (0);
}

t_cmd	**parser(t_token *tokens)
{
	t_cmd	**cmds;
	t_check	check;

	check = init_check();
	cmds = init_cmd(tokens, check);
	if (!cmds)
		return (NULL);
	while (check.k < ft_count_pipe(tokens) + 1)
	{
		if (!tokens[check.i].content)
			return (content_null(cmds));
		if (_parser(tokens, cmds, &check))
			return (NULL);
		check.k++;
	}
	return (cmds);
}
