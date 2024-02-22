/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkanyilm <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 02:05:27 by kkanyilm          #+#    #+#             */
/*   Updated: 2024/02/13 18:48:11 by kkanyilm         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../libft/libft.h"

int	ft_count_pipe(t_token *tokens)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (tokens[i].content)
	{
		if (tokens[i].type == PIPE)
			count++;
		i++;
	}
	return (count);
}

t_check	init_check(void)
{
	t_check	check;

	check.i = 0;
	check.j = 0;
	check.k = 0;
	check.is_command = 1;
	check.check_flag = 1;
	check.fd_out = 1;
	check.fd_in = 0;
	return (check);
}

t_cmd	**init_cmd(t_token *tokens, t_check check)
{
	t_cmd	**cmds;

	cmds = (t_cmd **)ft_calloc(sizeof(t_cmd *), ft_count_pipe(tokens) + 2);
	if (!cmds)
		return (print_error(SHELL_NAME, ERR_MALLOC),
			free_tokens(&tokens), NULL);
	while (check.i < ft_count_pipe(tokens) + 1)
	{
		cmds[check.i] = (t_cmd *)ft_calloc(sizeof(t_cmd), 1);
		if (!cmds[check.i])
			return (print_error(SHELL_NAME, ERR_MALLOC),
				free_cmds(cmds), free_tokens(&tokens), NULL);
		check.i++;
	}
	check.i = 0;
	return (cmds);
}
