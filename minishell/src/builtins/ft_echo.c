/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkanyilm <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 16:33:48 by fduvan            #+#    #+#             */
/*   Updated: 2024/02/13 18:38:59 by kkanyilm         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../libft/libft.h"
#include <unistd.h>

static int	flag_is_valid(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static int	valid_flag_count(char **flags)
{
	int	i;

	i = 0;
	while (flags && flags[i])
	{
		if (flag_is_valid(flags[i]) == 0)
			break ;
		i++;
	}
	return (i);
}

static void	ft_echo_write(t_cmd *cmd, int fd)
{
	int		i;
	int		flag_count;
	char	**flags;

	flags = cmd->flags_array;
	flag_count = valid_flag_count(flags);
	i = flag_count;
	while (flags && flags[i])
	{
		ft_putstr_fd(flags[i], fd);
		if (flags[i + 1] || cmd->content)
			ft_putchar_fd(' ', fd);
		i++;
	}
	i = 0;
	while (cmd->content && cmd->content[i].content)
	{
		ft_putstr_fd(cmd->content[i].content, fd);
		if (cmd->content[i + 1].content)
			ft_putchar_fd(' ', fd);
		i++;
	}
	if (flag_count == 0)
		ft_putchar_fd('\n', fd);
}

int	ft_echo(t_cmd *cmd)
{
	ft_echo_write(cmd, STDOUT_FILENO);
	return (0);
}
