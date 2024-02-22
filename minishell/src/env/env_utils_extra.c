/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_extra.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduvan <fduvan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:19:29 by kkanyilm          #+#    #+#             */
/*   Updated: 2024/02/13 17:58:44 by fduvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../libft/libft.h"
#include <stdlib.h>

int	ft_strlen3(t_env *env)
{
	int	i;

	i = 0;
	while (env[i].name)
		i++;
	return (i);
}

void	free_env(t_env *env)
{
	int	i;

	i = 0;
	while (env[i].name)
	{
		free(env[i].name);
		if (env[i].value)
			free(env[i].value);
		i++;
	}
	free(env);
}

int	add_old_env_to_new_env(t_env *env, t_env *new_env, int *i)
{
	new_env[*i].name = ft_strdup(env[*i].name);
	if (!new_env[*i].name)
		return (print_error(SHELL_NAME, ERR_MALLOC), 1);
	if (env[*i].value)
	{
		new_env[*i].value = ft_strdup(env[*i].value);
		if (!new_env[*i].value)
			return (print_error(SHELL_NAME, ERR_MALLOC), 1);
	}
	else
		new_env[*i].value = 0;
	(*i)++;
	return (0);
}

t_env	*add_env(t_env *env, char *name, char *value)
{
	t_env	*new_env;
	int		i;

	i = 0;
	new_env = (t_env *)ft_calloc(sizeof(t_env), ft_strlen3(env) + 2);
	if (!new_env)
		return (print_error(SHELL_NAME, ERR_MALLOC), NULL);
	while (env[i].name)
		if (add_old_env_to_new_env(env, new_env, &i))
			return (free_env(new_env), NULL);
	new_env[i].name = ft_strdup(name);
	if (!new_env[i].name)
		return (free_env(new_env), print_error(SHELL_NAME, ERR_MALLOC), NULL);
	if (value)
	{
		new_env[i].value = ft_strdup(value);
		if (!new_env[i].value)
			return (free_env(new_env),
				print_error(SHELL_NAME, ERR_MALLOC), NULL);
	}
	else
		new_env[i].value = 0;
	free_env(env);
	return (new_env);
}

int	add_old_env_to_new_env_delete(t_env *env, t_env *n_enw, t_check *check)
{
	if (ft_strncmp(env[check->i].name, check->name, ft_strlen(check->name) + 1))
	{
		n_enw[check->j].name = ft_strdup(env[check->i].name);
		if (!n_enw[check->j].name)
			return (print_error(SHELL_NAME, ERR_MALLOC), 1);
		if (env[check->i].value)
		{
			n_enw[check->j].value = ft_strdup(env[check->i].value);
			if (!n_enw[check->j].value)
				return (print_error(SHELL_NAME, ERR_MALLOC), 1);
		}
		else
			n_enw[check->j].value = 0;
	}
	else
		check->j--;
	check->i++;
	check->j++;
	return (0);
}
