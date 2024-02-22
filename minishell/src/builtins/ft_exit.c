/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduvan <fduvan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 14:27:05 by fduvan            #+#    #+#             */
/*   Updated: 2024/02/19 15:04:29 by fduvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../libft/libft.h"
#include <unistd.h>

static int	get_total_cmd_c(t_cmd *cmd)
{
	int	total_command_count;
	int	i;

	i = 0;
	total_command_count = 0;
	while (cmd->flags_array && cmd->flags_array[i])
	{
		total_command_count++;
		i++;
	}
	i = 0;
	while (cmd->content && cmd->content[i].content)
	{
		total_command_count++;
		i++;
	}
	return (total_command_count);
}

static void	ft_exit_error(t_cmd *cmd, int flag)
{
	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("minishell: exit: ", 2);
	if (!flag)
		ft_putstr_fd(cmd->content[0].content, 2);
	else
		ft_putstr_fd(cmd->flags_array[0], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	exit(255);
}

static void	ft_flag_exit(t_cmd *cmd, t_env **envp, t_cmd **cmds)
{
	int	i;
	int	return_value;

	i = 0;
	while (is_white_space(cmd->flags_array[0][i]))
		i++;
	if (cmd->flags_array[0][i] == '-')
		i++;
	while (cmd->flags_array[0][i])
	{
		if (ft_isdigit(cmd->flags_array[0][i]) == 0)
			ft_exit_error(cmd, 1);
		i++;
	}
	return_value = ft_atoi(cmd->flags_array[0]);
	ft_putstr_fd("exit\n", 1);
	free_env(*envp);
	free(envp);
	free_cmds(cmds);
	exit((256 + return_value) % 256);
}

static void	ft_content_exit(t_cmd *cmd, t_env **envp, t_cmd **cmds)
{
	int	i;
	int	return_value;

	i = 0;
	while (is_white_space(cmd->content[0].content[i]))
		i++;
	if (cmd->content[0].content[i] == '-'
		|| cmd->content[0].content[i] == '+')
		i++;
	while (cmd->content[0].content[i])
	{
		if (ft_isdigit(cmd->content[0].content[i]) == 0)
			ft_exit_error(cmd, 0);
		i++;
	}
	return_value = ft_atoi(cmd->content[0].content);
	ft_putstr_fd("exit\n", 1);
	free_env(*envp);
	free(envp);
	free_cmds(cmds);
	exit((256 + return_value) % 256);
}

int	ft_exit(t_cmd *cmd, t_env **envp, t_cmd **cmds)
{
	int	command_count;

	command_count = get_total_cmd_c(cmd);
	if (command_count == 0)
	{
		ft_putstr_fd("exit\n", 1);
		free_env(*envp);
		free(envp);
		free_cmds(cmds);
		exit(ft_exit_value(EXIT_GET, 0, 0));
	}
	if (command_count > 1)
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	if (cmd->flags_array && cmd->flags_array[0])
		ft_flag_exit(cmd, envp, cmds);
	else if (cmd->content && cmd->content[0].content)
		ft_content_exit(cmd, envp, cmds);
	return (0);
}
