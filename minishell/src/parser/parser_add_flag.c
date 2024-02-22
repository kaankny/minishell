/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_add_flag.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkanyilm <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:49:09 by kkanyilm          #+#    #+#             */
/*   Updated: 2024/02/19 14:50:04 by kkanyilm         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../libft/libft.h"

char	**add_flag(char **flags, char *flag)
{
	char	**new_flags;
	int		i;

	i = 0;
	while (flags && flags[i])
		i++;
	new_flags = malloc(sizeof(char *) * (i + 2));
	if (!new_flags)
		return (NULL);
	i = 0;
	while (flags && flags[i])
	{
		new_flags[i] = flags[i];
		i++;
	}
	new_flags[i] = ft_strdup(flag);
	if (!new_flags[i])
	{
		free(new_flags);
		return (NULL);
	}
	new_flags[i + 1] = NULL;
	if (flags)
		free(flags);
	return (new_flags);
}
