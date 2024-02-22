/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_execv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduvan <fduvan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:46:50 by fduvan            #+#    #+#             */
/*   Updated: 2024/02/15 17:40:22 by fduvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <unistd.h>
#include <stdlib.h>

static int	execute_fork(t_cmd *cmd, t_check check, t_env *env)
{
	if (!cmd->command)
		exit (1);
	if (access(cmd->command, F_OK) == 0 && access(cmd->command, X_OK) == 0)
	{
		if (execve(cmd->command, check.args_arr, 0) != 0)
			exit(127);
	}
	else if (!is_paths_define(env))
		exit(127);
	else if (execve(check.path, check.args_arr, check.env_arr) != 0)
		exit(127);
	exit(0);
}

static void	free_execute_args(char **args, char *path, char **env_arr)
{
	free_double_char(args);
	free(path);
	free_double_char(env_arr);
}

static int	_execute_command(t_cmd *cmd, t_env *env, t_check check)
{
	check.pid = fork();
	if (check.pid == 0)
	{
		file_duplicate(cmd);
		execute_fork(cmd, check, env);
	}
	else if (check.pid < 0)
	{
		free_execute_args(check.args_arr, check.path, check.env_arr);
		return (print_error(SHELL_NAME, "fork error"), FT_FAILURE);
	}
	else
	{
		waitpid(check.pid, &check.status, 0);
		ft_exit_value(EXIT_SET, check.status / 256, 0);
		return (free_execute_args(check.args_arr, check.path, check.env_arr),
			check.status / 256);
	}
	return (0);
}

int	execute_command(t_cmd *cmd, t_env *env)
{
	t_check	check;

	check.path = get_path(cmd->command, env);
	if (!check.path)
		return (print_error(SHELL_NAME, ERR_MALLOC), 0);
	check.args_arr = get_args_cmd(cmd);
	if (!check.args_arr)
		return (free(check.path), print_error(SHELL_NAME, ERR_MALLOC), 0);
	check.env_arr = get_env_arr(env);
	if (!check.env_arr)
		return (free_double_char(check.args_arr),
			free(check.path), print_error(SHELL_NAME, ERR_MALLOC), 0);
	if (file_define_fd(cmd) == 1)
		return (free_execute_args(check.args_arr, check.path, check.env_arr),
			1);
	return (_execute_command(cmd, env, check));
}
