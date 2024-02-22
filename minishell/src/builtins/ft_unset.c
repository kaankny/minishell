/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkanyilm <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 18:37:39 by fduvan            #+#    #+#             */
/*   Updated: 2024/02/13 18:40:03 by kkanyilm         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../libft/libft.h"

static int	is_valid_unset_cmd(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (!ft_isalnum(cmd[i]) && cmd[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	ft_unset(t_cmd *cmd, t_env **env)
{
	int	i;

	i = 0;
	while (cmd->content && cmd->content[i].content)
	{
		if (is_valid_unset_cmd(cmd->content[i].content))
		{
			if (is_exist_env(cmd->content[i].content, *env))
				*env = delete_env(*env, cmd->content[i].content);
		}
		else
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(cmd->content[i].content, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
		}
		i++;
	}
	return (0);
}
