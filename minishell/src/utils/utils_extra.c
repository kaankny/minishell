/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_extra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkanyilm <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:43:27 by kkanyilm          #+#    #+#             */
/*   Updated: 2024/02/19 14:52:39 by kkanyilm         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../libft/libft.h"

int	add_contents_to_args(char ***args, t_cmd *cmd, int *i)
{
	int	j;

	j = 0;
	while (cmd->content && cmd->content[j].content)
	{
		(*args)[*i] = ft_strdup(cmd->content[j].content);
		if (!(*args)[*i])
			return (0);
		(*i)++;
		j++;
	}
	return (1);
}

char	**get_args_cmd(t_cmd *cmd)
{
	int		i;
	int		j;
	char	**args;

	args = ft_calloc(sizeof(char *), get_total_command_count(cmd) + 1);
	i = 0;
	if (cmd->command)
	{
		args[i] = ft_strdup(cmd->command);
		i++;
	}
	if (cmd->flags_array)
	{
		j = 0;
		while (cmd->flags_array[j])
		{
			args[i] = ft_strdup(cmd->flags_array[j]);
			i++;
			j++;
		}
	}
	if (add_contents_to_args(&args, cmd, &i) == 0)
		return (free_double_char(args), NULL);
	return (args);
}

char	*ft_strndup(char *str, int n)
{
	char	*new_str;
	int		i;

	i = 0;
	new_str = malloc(sizeof(char) * (n + 1));
	if (!new_str)
		return (NULL);
	while (str[i] && i < n)
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

int	is_white_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f');
}

int	ft_exit_value(enum e_exit_vls exit_status, int value, int *ev)
{
	static int	*exit_value;

	if (exit_status == EXIT_FIRST)
		exit_value = ev;
	if (exit_status == EXIT_SET || exit_status == EXIT_FIRST)
		*exit_value = value;
	if (exit_status == EXIT_GET)
		return (*exit_value);
	return (0);
}
