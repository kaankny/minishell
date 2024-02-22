/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkanyilm <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:07:30 by fduvan            #+#    #+#             */
/*   Updated: 2024/02/13 18:42:25 by kkanyilm         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../libft/libft.h"

static int	is_builtin(t_cmd *cmd)
{
	if (ft_strncmp(cmd->command, "echo", ft_strlen("echo") + 1) == 0)
		return (1);
	else if (ft_strncmp(cmd->command, "cd", ft_strlen("cd") + 1) == 0)
		return (1);
	else if (ft_strncmp(cmd->command, "pwd", ft_strlen("pwd") + 1) == 0)
		return (1);
	else if (ft_strncmp(cmd->command, "export", ft_strlen("export") + 1) == 0)
		return (1);
	else if (ft_strncmp(cmd->command, "unset", ft_strlen("unset") + 1) == 0)
		return (1);
	else if (ft_strncmp(cmd->command, "env", ft_strlen("env") + 1) == 0)
		return (1);
	else if (ft_strncmp(cmd->command, "exit", ft_strlen("exit") + 1) == 0)
		return (1);
	return (0);
}

int	execute_builtin(t_cmd *cmd, t_env **env, t_cmd **cmds)
{
	int	i;

	i = 0;
	if (!cmd->command)
		return (FT_INVALID);
	if (!is_builtin(cmd))
		return (FT_INVALID);
	if (file_define_fd(cmd) == FT_FAILURE)
		return (FT_FAILURE);
	file_duplicate(cmd);
	if (ft_strncmp(cmd->command, "echo", ft_strlen("echo") + 1) == 0)
		return (ft_echo(cmd));
	else if (ft_strncmp(cmd->command, "cd", ft_strlen("cd") + 1) == 0)
		return (ft_cd(cmd, *env));
	else if (ft_strncmp(cmd->command, "pwd", ft_strlen("pwd") + 1) == 0)
		return (ft_pwd());
	else if (ft_strncmp(cmd->command, "export", ft_strlen("export") + 1) == 0)
		return (ft_export(cmd, env));
	else if (ft_strncmp(cmd->command, "unset", ft_strlen("unset") + 1) == 0)
		return (ft_unset(cmd, env));
	else if (ft_strncmp(cmd->command, "env", ft_strlen("env") + 1) == 0)
		return (ft_env(*env));
	else if (ft_strncmp(cmd->command, "exit", ft_strlen("exit") + 1) == 0)
		return (ft_exit(cmd, env, cmds));
	return (FT_INVALID);
}
