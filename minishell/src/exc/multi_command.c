/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduvan <fduvan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:05:52 by fduvan            #+#    #+#             */
/*   Updated: 2024/02/15 17:41:30 by fduvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <unistd.h>
#include <stdlib.h>

static int	ft_multi_heredoc(t_cmd **cmds, int i)
{
	int	j;

	j = -1;
	if (cmds[i]->input_file)
	{
		while (cmds[i]->input_file[++j].name)
		{
			if (cmds[i]->input_file[j].double_op == 1)
			{
				if (heredoc(cmds[i], j) == FT_FAILURE)
				{
					ft_exit_value(EXIT_SET, 1, 0);
					return (FT_FAILURE);
				}
			}
		}
	}
	if (g_signal == FT_SIGEXIT)
	{
		ft_exit_value(EXIT_SET, 1, 0);
		return (FT_FAILURE);
	}
	return (0);
}

static int	multi_command_success(t_cmd **cmds, t_check check, int ori_fd,
	int ori_fd_in)
{
	int	j;

	j = -1;
	while (cmds[check.i] && cmds[check.i]->output_file
		&& cmds[check.i]->output_file[++j].name)
		close(cmds[check.i]->output_file[j].fd);
	set_default_fd(ori_fd, ori_fd_in);
	exit (0);
}

static int	multi_command_error(t_cmd **cmds, int original_fd,
	int original_fd_in, int i)
{
	set_default_fd(original_fd, original_fd_in);
	print_error_command_not_found(cmds[i]->command);
	exit(127);
}

static int	ft_child_process(t_cmd **cmds, t_check check,
	int original_fd, int original_fd_in)
{
	dup2(check.fd_in, 0);
	if (cmds[check.i + 1])
		dup2(check.fd[1], 1);
	close(check.fd[0]);
	if (execute_builtin(cmds[check.i], check.env, cmds) != FT_INVALID)
		multi_command_success(cmds, check, original_fd, original_fd_in);
	else if (execute_command(cmds[check.i], *(check.env)) != 127)
		multi_command_success(cmds, check, original_fd, original_fd_in);
	else
		multi_command_error(cmds, original_fd, original_fd_in, check.i);
	return (ft_exit_value(EXIT_GET, 0, 0));
}

int	execute_multi_command(t_cmd **cmds, t_env **env,
	int original_fd, int original_fd_in)
{
	t_check	check;

	check = init_check();
	check.env = env;
	while (cmds[check.i])
	{
		if (ft_multi_heredoc(cmds, check.i) == FT_FAILURE)
			return (FT_FAILURE);
		pipe(check.fd);
		check.pid = fork();
		if (check.pid == 0)
			ft_child_process(cmds, check, original_fd, original_fd_in);
		else if (check.pid < 0)
			return (print_error(SHELL_NAME, "fork error"), FT_FAILURE);
		else
		{
			waitpid(check.pid, &(check.status), 0);
			ft_exit_value(EXIT_SET, check.status / 256, 0);
			close(check.fd[1]);
			check.fd_in = check.fd[0];
			check.i++;
		}
	}
	return (check.status / 256);
}
