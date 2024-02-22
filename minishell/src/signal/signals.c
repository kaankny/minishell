/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduvan <fduvan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:37:50 by kkanyilm          #+#    #+#             */
/*   Updated: 2024/02/15 17:55:48 by fduvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include "../../inc/minishell.h"

static void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		if (g_signal == FT_SIGHEREDOC)
		{
			exit(FT_SIGEXIT);
		}
		else
		{
			ft_exit_value(EXIT_SET, 1, 0);
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
}

void	signal_init(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigint_handler);
}
