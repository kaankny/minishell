/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_pro.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduvan <fduvan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:20:57 by kkanyilm          #+#    #+#             */
/*   Updated: 2024/02/13 17:59:04 by fduvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../libft/libft.h"
#include <stdlib.h>

t_env	*delete_env(t_env *env, char *name)
{
	t_env	*new_env;
	t_check	check;

	check = init_check();
	check.name = name;
	new_env = (t_env *)ft_calloc(sizeof(t_env), ft_strlen3(env));
	if (!new_env)
		return (print_error(SHELL_NAME, ERR_MALLOC), NULL);
	while (env[check.i].name)
	{
		if (add_old_env_to_new_env_delete(env, new_env, &check))
			return (free_env(new_env), NULL);
	}
	free_env(env);
	return (new_env);
}

t_env	*change_env(t_env *env, char *name, char *value)
{
	int		i;
	char	*old_value;

	i = 0;
	while (env[i].name)
	{
		if (!ft_strncmp(env[i].name, name, ft_strlen(name) + 1))
		{
			old_value = env[i].value;
			env[i].value = ft_strdup(value);
			if (!env[i].value)
				return (env[i].value = old_value,
					print_error(SHELL_NAME, ERR_MALLOC), NULL);
			free(old_value);
			return (env);
		}
		i++;
	}
	return (NULL);
}

char	*ft_strjoin_char(char *s1, char c)
{
	char	*res;
	int		i;

	i = 0;
	res = (char *)ft_calloc(sizeof(char), ft_strlen(s1) + 2);
	if (!res)
		return (free(s1), print_error(SHELL_NAME, ERR_MALLOC), NULL);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = c;
	free(s1);
	return (res);
}

char	*read_env(char *name, t_env *env)
{
	int	i;

	i = 0;
	while (env[i].name)
	{
		if (ft_strncmp(env[i].name, name, ft_strlen(name) + 1) == 0)
			return (env[i].value);
		i++;
	}
	return (NULL);
}

int	is_exist_env(char *name, t_env *env)
{
	int	i;

	i = 0;
	while (env[i].name)
	{
		if (ft_strncmp(env[i].name, name, ft_strlen(name) + 1) == 0)
			return (1);
		i++;
	}
	return (0);
}
