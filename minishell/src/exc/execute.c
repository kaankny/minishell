/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduvan <fduvan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 14:24:21 by fduvan            #+#    #+#             */
/*   Updated: 2024/02/15 17:15:10 by fduvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../libft/libft.h"
#include <unistd.h>

static int	execute_heredoc_single(t_cmd **cmds)
{
	int	i;

	i = 0;
	while (cmds[0]->input_file && cmds[0]->input_file[i].name)
	{
		if (cmds[0]->input_file[i].double_op == 1)
		{
			if (heredoc(cmds[0], i) == FT_FAILURE)
			{
				ft_exit_value(EXIT_SET, 1, 0);
				return (FT_FAILURE);
			}
		}
		i++;
	}
	if (g_signal == FT_SIGEXIT)
	{
		ft_exit_value(EXIT_SET, 1, 0);
		return (FT_FAILURE);
	}
	return (0);
}

static int	builtin_succes(t_cmd **cmds, int ofd, int oifd)
{
	int	i;

	i = 0;
	while (cmds[0] && cmds[0]->output_file && cmds[0]->output_file[i].name)
	{
		close(cmds[0]->output_file[i].fd);
		i++;
	}
	i = 0;
	while (cmds[0] && cmds[0]->input_file && cmds[0]->input_file[i].name)
	{
		close(cmds[0]->input_file[i].fd);
		i++;
	}
	set_default_fd(ofd, oifd);
	return (0);
}

static int	execute_single_command(t_cmd **cmds, t_env **env)
{
	int	i;
	int	original_fd;
	int	original_fd_in;

	original_fd = dup(1);
	original_fd_in = dup(0);
	if (execute_heredoc_single(cmds) == FT_FAILURE)
		return (FT_FAILURE);
	i = 0;
	if (execute_builtin(cmds[0], env, cmds) != FT_INVALID)
		return (builtin_succes(cmds, original_fd, original_fd_in));
	else if (execute_command(cmds[0], *env) != 127)
	{
		set_default_fd(original_fd, original_fd_in);
		return (0);
	}
	else
	{
		set_default_fd(original_fd, original_fd_in);
		ft_exit_value(EXIT_SET, 127, 0);
		print_error_command_not_found(cmds[0]->command);
		return (FT_FAILURE);
	}
	return (0);
}

int	execute_commands(t_cmd **cmds, t_env **env)
{
	int	i;
	int	original_fd;
	int	original_fd_in;

	i = 0;
	g_signal = FT_SIGST;
	if (cmds[0]->command && ft_strncmp(cmds[0]->command,
			"exit", ft_strlen("exit") + 1) != 0)
		ft_exit_value(EXIT_SET, 0, 0);
	if (!cmds)
		return (0);
	original_fd = dup(1);
	original_fd_in = dup(0);
	if (command_count(cmds) == 1)
	{
		if (execute_single_command(cmds, env) == FT_FAILURE)
			return (FT_FAILURE);
	}
	else
		return (execute_multi_command(cmds, env, original_fd, original_fd_in));
	return (0);
}
