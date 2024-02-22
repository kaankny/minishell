/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduvan <fduvan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:08:36 by kkanyilm          #+#    #+#             */
/*   Updated: 2024/02/15 15:10:35 by fduvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../libft/libft.h"
#include <stdlib.h>

static int	check_ascii(char c)
{
	if ((c >= 'A' && c <= 'Z' ) || (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9') || c == '_')
		return (1);
	return (0);
}

static int	ft_get_dollar(char **tmp2, char **tmp, char **res)
{
	*tmp2 = ft_itoa(ft_exit_value(EXIT_GET, 0, 0));
	if (!tmp2)
		return (free(*res),
			print_error(SHELL_NAME, ERR_MALLOC), FT_FAILURE);
	*tmp = ft_strjoin(*res, *tmp2);
	if (!tmp)
		return (free(*res), free(*tmp2),
			print_error(SHELL_NAME, ERR_MALLOC), FT_FAILURE);
	free(*tmp2);
	return (0);
}

static int	ft_get_others(t_check check, char **tmp2, char **tmp, char **res)
{
	*tmp2 = ft_substr(check.name, check.i + 1, check.j - 1);
	if (!*tmp2)
		return (free(*res),
			print_error(SHELL_NAME, ERR_MALLOC), FT_FAILURE);
	*tmp = ft_strjoin(*res, read_env(*tmp2, *check.env));
	if (!*tmp)
		return (free(*res), free(*tmp2),
			print_error(SHELL_NAME, ERR_MALLOC), FT_FAILURE);
	free(*tmp2);
	return (0);
}

int	_get_env(t_check *check, char **res, char **tmp, char **tmp2)
{
	check->j = 1;
	while (check->name[check->i + check->j]
		&& check_ascii(check->name[check->i + check->j]))
		check->j++;
	if (check->name[check->i + check->j - 1] == '$'
		&& check->name [check->i + check->j++] == '?')
	{
		if (ft_get_dollar(tmp2, tmp, res) == FT_FAILURE)
			return (FT_FAILURE);
	}
	else
	{
		if (ft_get_others(*check, tmp2, tmp, res) == FT_FAILURE)
			return (FT_FAILURE);
	}
	if (!*tmp)
		return (print_error(SHELL_NAME, ERR_MALLOC), FT_FAILURE);
	free(*res);
	*res = *tmp;
	check->i += check->j - 1;
	return (0);
}

char	*get_env(t_env *env, char *name)
{
	char	*res;
	char	*tmp;
	char	*tmp2;
	t_check	check;

	check = init_check();
	check.name = name;
	check.env = &env;
	res = ft_strdup("");
	if (!res)
		return (print_error(SHELL_NAME, ERR_MALLOC), NULL);
	while (name[check.i])
	{
		if (name[check.i] != '$')
		{
			res = ft_strjoin_char(res, name[check.i]);
			if (!res)
				return (NULL);
		}
		else
			if (_get_env(&check, &res, &tmp, &tmp2) == FT_FAILURE)
				return (NULL);
		check.i++;
	}
	return (res);
}
