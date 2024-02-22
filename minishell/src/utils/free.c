/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkanyilm <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 14:30:07 by kkanyilm          #+#    #+#             */
/*   Updated: 2024/02/19 14:52:53 by kkanyilm         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <stdlib.h>

void	free_contents(t_content **contents)
{
	int	i;

	i = 0;
	while ((*contents)[i].content)
	{
		free((*contents)[i].content);
		i++;
	}
	free(*contents);
}

void	free_cmds(t_cmd **cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
	{
		if (cmds[i]->command)
			free(cmds[i]->command);
		if (cmds[i]->flags_array)
			free_double_char(cmds[i]->flags_array);
		if (cmds[i]->content)
			free_contents(&cmds[i]->content);
		if (cmds[i]->input_file)
			free_files(&cmds[i]->input_file);
		if (cmds[i]->output_file)
			free_files(&cmds[i]->output_file);
		free(cmds[i]);
		i++;
	}
	free(cmds);
}

void	free_tokens(t_token **tokens)
{
	int	i;

	i = 0;
	while (*tokens && (*tokens)[i].content)
	{
		free((*tokens)[i].content);
		i++;
	}
	if (*tokens)
		free(*tokens);
}
