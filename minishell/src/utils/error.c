/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkanyilm <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 15:22:42 by kkanyilm          #+#    #+#             */
/*   Updated: 2024/02/13 18:50:38 by kkanyilm         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../libft/libft.h"

int	print_error_command_not_found(char *command)
{
	ft_putstr_fd("\033[31m", 2);
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd("\033[0m: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": command not found\n", 2);
	return (FT_FAILURE);
}

int	print_error(char *title, char *error_type)
{
	ft_putstr_fd("\033[31m", 2);
	ft_putstr_fd(title, 2);
	ft_putstr_fd("\033[0m: ", 2);
	ft_putstr_fd(error_type, 2);
	ft_putstr_fd("\n", 2);
	return (FT_FAILURE);
}
