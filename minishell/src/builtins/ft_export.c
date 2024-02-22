/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduvan <fduvan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 18:37:29 by fduvan            #+#    #+#             */
/*   Updated: 2024/02/19 15:01:21 by fduvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../libft/libft.h"

static int	_get_envs(t_cmd *cmd, t_env *env, int i)
{
	env[i].name = ft_strndup(cmd->content[i].content,
			ft_strchr(cmd->content[i].content, '=') - cmd->content[i].content);
	if (!env[i].name)
		return (free_env(env), FT_FAILURE);
	env[i].value = ft_strdup(ft_strchr(cmd->content[i].content, '=') + 1);
	if (!env[i].value)
		return (free_env(env), FT_FAILURE);
	return (0);
}

static t_env	*get_envs(t_cmd *cmd)
{
	int		i;
	t_env	*env;

	i = 0;
	env = ft_calloc(sizeof(t_env), (ft_env_arr_len(cmd->content) + 1));
	if (!env)
		return (NULL);
	while (cmd->content && cmd->content[i].content)
	{
		if (ft_strchr(cmd->content[i].content, '='))
		{
			if (_get_envs(cmd, env, i) == FT_FAILURE)
				return (NULL);
		}
		else
		{
			env[i].name = ft_strdup(cmd->content[i].content);
			if (!env[i].name)
				return (free_env(env), NULL);
			env[i].value = NULL;
		}
		i++;
	}
	env[i].name = NULL;
	return (env[i].value = NULL, env);
}

static void	_ft_export(t_env **env, t_env *new_envs, int i)
{
	if (new_envs[i].name[0] == '\0'
		|| (check_valid_name(new_envs[i].name) == 0))
	{
		ft_exit_value(EXIT_SET, 1, 0);
		print_error(SHELL_NAME, "not a valid identifier");
	}
	else
	{
		if (is_exist_env(new_envs[i].name, *env))
		{
			if (new_envs[i].value)
				change_env(*env, new_envs[i].name, new_envs[i].value);
			else
				change_env(*env, new_envs[i].name, 0);
		}
		else
		{
			if (new_envs[i].value)
				*env = add_env(*env, new_envs[i].name, new_envs[i].value);
			else
				*env = add_env(*env, new_envs[i].name, 0);
		}
	}
}

int	ft_export(t_cmd *cmd, t_env **env)
{
	t_env	*new_envs;
	int		i;

	i = 0;
	if (!cmd->content || !cmd->content[0].content)
	{
		ft_only_export(*env);
		return (0);
	}
	else
	{
		new_envs = get_envs(cmd);
		if (!new_envs)
			return (print_error(SHELL_NAME, ERR_MALLOC), 0);
		while (new_envs[i].name)
		{
			_ft_export(env, new_envs, i);
			i++;
		}
	}
	return (free_env(new_envs), 0);
}
