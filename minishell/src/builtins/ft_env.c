/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduvan <fduvan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 18:37:12 by fduvan            #+#    #+#             */
/*   Updated: 2024/02/13 15:18:59 by fduvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../libft/libft.h"

int	ft_env(t_env *env)
{
	int	i;

	i = 0;
	while (env && env[i].name)
	{
		if (env[i].value && env[i].value[0] == 0)
		{
			ft_putstr_fd(env[i].name, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd("\n", 1);
		}
		else if (env[i].value && env[i].value[0] != '\0')
		{
			ft_putstr_fd(env[i].name, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(env[i].value, 1);
			ft_putstr_fd("\n", 1);
		}
		i++;
	}
	return (0);
}
