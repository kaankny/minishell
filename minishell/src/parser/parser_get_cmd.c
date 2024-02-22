/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_get_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkanyilm <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 02:14:10 by kkanyilm          #+#    #+#             */
/*   Updated: 2024/02/19 15:48:13 by kkanyilm         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../libft/libft.h"

int	_get_cmd_word(t_cmd **cmds, t_token *tokens, t_check *check)
{
	if (check->check_flag && tokens[check->i].content[0] == '-')
	{
		cmds[check->k]->flags_array = \
			add_flag(cmds[check->k]->flags_array, tokens[check->i].content);
		if (!cmds[check->k]->flags_array)
			return (print_error(SHELL_NAME, ERR_MALLOC), free_cmds(cmds),
				free_tokens(&tokens), FT_FAILURE);
	}
	else
	{
		cmds[check->k]->content = \
			add_content(&cmds[check->k]->content,
				ft_strdup(tokens[check->i].content), tokens[check->i].type,
				tokens[check->i].is_append);
		if (!cmds[check->k]->content)
			return (print_error(SHELL_NAME, ERR_MALLOC), free_cmds(cmds),
				free_tokens(&tokens), FT_FAILURE);
		check->check_flag = 0;
	}
	return (1);
}

int	get_cmd_word(t_cmd **cmds, t_token *tokens, t_check *check)
{
	if (check->is_command)
	{
		cmds[check->k]->command = ft_strdup(tokens[check->i].content);
		if (!cmds[check->k]->command)
			return (print_error(SHELL_NAME, ERR_MALLOC),
				free_cmds(cmds), free_tokens(&tokens), FT_FAILURE);
		check->is_command = 0;
	}
	else
	{
		if (_get_cmd_word(cmds, tokens, check) == FT_FAILURE)
			return (FT_FAILURE);
	}
	return (1);
}

int	get_cmd_redir_in(t_cmd **cmds, t_token *tokens, t_check *check)
{
	if (!tokens[check->i + 1].content)
		return (print_error(SHELL_NAME,
				"syntax error near unexpected token `newline'"),
			free_cmds(cmds), free_tokens(&tokens), FT_FAILURE);
	if (ft_strncmp(tokens[check->i + 1].content, "<", 1) == 0)
		return (print_error(SHELL_NAME,
				"syntax error near unexpected token `<'"),
			free_cmds(cmds), free_tokens(&tokens), FT_FAILURE);
	if (ft_strncmp(tokens[check->i].content, "<<", 3) == 0)
		cmds[check->k]->input_file = \
				add_file(&cmds[check->k]->input_file,
				ft_strdup(tokens[check->i + 1].content), 1);
	else if (ft_strncmp(tokens[check->i].content, "<", 2) == 0)
		cmds[check->k]->input_file = \
				add_file(&cmds[check->k]->input_file,
				ft_strdup(tokens[check->i + 1].content), 0);
	else
		return (print_error(SHELL_NAME,
				"syntax error near unexpected token `newline'"),
			free_cmds(cmds), free_tokens(&tokens), FT_FAILURE);
	if (!cmds[check->k]->input_file)
		return (print_error(SHELL_NAME, ERR_MALLOC),
			free_cmds(cmds), free_tokens(&tokens), FT_FAILURE);
	check->i++;
	return (0);
}

int	get_cmd_redir_out(t_cmd **cmds, t_token *tokens, t_check *check)
{
	if (!tokens[check->i + 1].content)
		return (print_error(SHELL_NAME,
				"syntax error near unexpected token `newline'"),
			free_cmds(cmds), free_tokens(&tokens), FT_FAILURE);
	if (ft_strncmp(tokens[check->i + 1].content, ">", 1) == 0)
		return (print_error(SHELL_NAME,
				"syntax error near unexpected token `>'"),
			free_cmds(cmds), free_tokens(&tokens), FT_FAILURE);
	if (ft_strncmp(tokens[check->i].content, ">>", 3) == 0)
		cmds[check->k]->output_file = \
				add_file(&cmds[check->k]->output_file,
				ft_strdup(tokens[check->i + 1].content), 1);
	else if (ft_strncmp(tokens[check->i].content, ">", 2) == 0)
		cmds[check->k]->output_file = \
				add_file(&cmds[check->k]->output_file,
				ft_strdup(tokens[check->i + 1].content), 0);
	else
		return (print_error(SHELL_NAME,
				"syntax error near unexpected token `newline'"),
			free_cmds(cmds), free_tokens(&tokens), FT_FAILURE);
	if (!cmds[check->k]->output_file)
		return (print_error(SHELL_NAME, ERR_MALLOC),
			free_cmds(cmds), free_tokens(&tokens), FT_FAILURE);
	check->i++;
	return (0);
}
