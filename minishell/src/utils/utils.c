/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkanyilm <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 15:25:48 by kkanyilm          #+#    #+#             */
/*   Updated: 2024/02/19 14:52:44 by kkanyilm         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../libft/libft.h"

void	free_double_char(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	env_count(t_env *env)
{
	int	i;

	i = 0;
	while (env && env[i].name)
		i++;
	return (i);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*new_str;

	new_str = ft_strjoin(s1, s2);
	free(s1);
	return (new_str);
}

char	**get_env_arr(t_env *env)
{
	int		i;
	char	**env_arr;

	i = 0;
	env_arr = ft_calloc(sizeof(char *), (env_count(env) + 1));
	if (!env_arr)
		return (NULL);
	while (env && env[i].name)
	{
		env_arr[i] = ft_strdup(env[i].name);
		if (!env_arr[i])
			return (free_double_char(env_arr), NULL);
		env_arr[i] = ft_strjoin_free(env_arr[i], "=");
		if (!env_arr[i])
			return (free_double_char(env_arr), NULL);
		env_arr[i] = ft_strjoin_free(env_arr[i], env[i].value);
		if (!env_arr[i])
			return (free_double_char(env_arr), NULL);
		i++;
	}
	env_arr[i] = 0;
	return (env_arr);
}

int	get_total_command_count(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->command)
		i++;
	if (cmd->flags_array)
		i += flag_count(cmd);
	if (cmd->content)
		i += content_count(cmd);
	return (i);
}
