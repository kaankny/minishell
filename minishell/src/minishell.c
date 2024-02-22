/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkanyilm <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:34:14 by kkanyilm          #+#    #+#             */
/*   Updated: 2024/02/19 15:48:30 by kkanyilm         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int	g_signal;

void	print_welcome(void)
{
	printf("\033[1mMinishell\033[0m - 42 Project Edition\n");
	printf("Step into the world of command lines with this custom shell ");
	printf("by [\033[36mkkanyilm\033[0m] & [\033[33mfduvan\033[0m]");
	printf("\nHappy scripting!\n\n");
}

static int	input_init_two(t_token **tokens, t_cmd ***cmds)
{
	*tokens = appender(*tokens);
	if (!*tokens)
	{
		ft_exit_value(EXIT_SET, 1, 0);
		return (1);
	}
	*cmds = parser(*tokens);
	if (*cmds)
		free_tokens(tokens);
	if (!*cmds)
	{
		ft_exit_value(EXIT_SET, 1, 0);
		return (1);
	}
	return (0);
}

static void	input_init(char *input, t_env **env)
{
	t_token	*tokens;
	t_cmd	**cmds;

	g_signal = FT_SIGST;
	tokens = lexer(input);
	if (!tokens)
	{
		ft_exit_value(EXIT_SET, 1, 0);
		return ;
	}
	tokens = expand(tokens, *env);
	if (!tokens)
	{
		ft_exit_value(EXIT_SET, 1, 0);
		return ;
	}
	if (input_init_two(&tokens, &cmds))
		return ;
	execute_commands(cmds, env);
	free_cmds(cmds);
}

void	get_input(t_env **env)
{
	char	*input;

	while (1)
	{
		input = readline(PROMPT);
		if (!input)
		{
			printf("exit\n");
			free_env(*env);
			free(env);
			exit(ft_exit_value(EXIT_GET, 0, 0));
		}
		if (!*input)
		{
			continue ;
		}
		add_history(input);
		input_init(input, env);
		free(input);
	}
}

int	main(int argc, char **argv, char **environ)
{
	t_env	**env;
	int		exit_value;

	(void)argv;
	if (argc != 1)
		return (print_error(SHELL_NAME, "too many arg."), 1);
	ft_exit_value(EXIT_FIRST, 0, &exit_value);
	env = malloc(sizeof(t_env *));
	if (!env)
		return (print_error(SHELL_NAME, ERR_MALLOC), 1);
	*env = env_init(environ);
	if (!*env)
		return (1);
	print_welcome();
	signal_init();
	get_input(env);
	return (0);
}
