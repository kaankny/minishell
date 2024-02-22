/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduvan <fduvan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:08:38 by fduvan            #+#    #+#             */
/*   Updated: 2024/02/15 17:01:52 by fduvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../libft/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <readline/readline.h>

static void	_heredoc(t_cmd *cmd, int *fd, int i)
{
	char	*line;

	close(fd[0]);
	g_signal = FT_SIGHEREDOC;
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(line, cmd->input_file[i].name,
				ft_strlen(cmd->input_file[i].name) + 1) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd[1]);
		free(line);
	}
	close(fd[1]);
}

static int	heredoc_fork_err(void)
{
	print_error(SHELL_NAME, "fork error");
	return (FT_FAILURE);
}

int	heredoc(t_cmd *cmd, int i)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	if (pipe(fd) == -1)
		return (FT_FAILURE);
	pid = fork();
	if (pid == 0)
	{
		if (g_signal == FT_SIGEXIT)
			exit (FT_SIGEXIT);
		_heredoc(cmd, fd, i);
		exit(0);
	}
	else if (pid < 0)
		return (heredoc_fork_err());
	else
	{
		waitpid(pid, &status, 0);
		g_signal = status / 256;
		close(fd[1]);
		cmd->input_file[0].fd = fd[0];
	}
	return (0);
}
