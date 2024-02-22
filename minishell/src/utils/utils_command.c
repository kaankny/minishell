/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkanyilm <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 17:55:42 by fduvan            #+#    #+#             */
/*   Updated: 2024/02/13 18:50:40 by kkanyilm         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	command_count(t_cmd **cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
		i++;
	return (i);
}

int	content_count(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->content && cmd->content[i].content)
		i++;
	return (i);
}

int	flag_count(t_cmd *cmd)
{
	int	flag_count;

	flag_count = 0;
	while (cmd->flags_array && cmd->flags_array[flag_count])
		flag_count++;
	return (flag_count);
}
