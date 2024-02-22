/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduvan <fduvan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 14:23:50 by fduvan            #+#    #+#             */
/*   Updated: 2024/02/19 15:02:46 by fduvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../libft/libft.h"
#include <unistd.h>

static int	_ft_cd(t_cmd *cmd, char *oldpwd)
{
	if (cmd->flags_array && cmd->flags_array[0][0] == '-')
	{
		if (!oldpwd)
		{
			ft_exit_value(EXIT_SET, 1, 0);
			return (print_error(SHELL_NAME, "OLDPWD not set"));
		}
		if (chdir(oldpwd) == -1)
		{
			ft_exit_value(EXIT_SET, 1, 0);
			return (print_error(SHELL_NAME, "No such file or directory"));
		}
	}
	else
	{
		if (chdir(cmd->content[0].content) == -1)
		{
			ft_exit_value(EXIT_SET, 1, 0);
			return (print_error(SHELL_NAME, "No such file or directory"));
		}
	}
	return (0);
}

int	ft_cd(t_cmd *cmd, t_env *env)
{
	char	*oldpwd;
	char	*pwd;
	char	getcwdbuf[1024];

	oldpwd = read_env("OLDPWD", env);
	pwd = read_env("PWD", env);
	if (content_count(cmd) + flag_count(cmd) == 0)
	{
		if (chdir(read_env("HOME", env)) == -1)
			return (ft_exit_value(EXIT_SET, 1, 0),
				print_error(SHELL_NAME, "HOME not set"));
	}
	else
	{
		if (_ft_cd(cmd, oldpwd) == FT_FAILURE)
			return (ft_exit_value(EXIT_SET, 1, 0), FT_FAILURE);
	}
	if (change_env(env, "OLDPWD", pwd) == 0)
		return (-1);
	if (change_env(env, "PWD", getcwd(getcwdbuf, sizeof(getcwdbuf))) == 0)
		return (-1);
	return (0);
}
