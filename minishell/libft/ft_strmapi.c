/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduvan <fduvan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 11:49:02 by fduvan            #+#    #+#             */
/*   Updated: 2023/12/05 12:57:14 by fduvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char				*n_str;
	unsigned int		i;

	i = 0;
	n_str = ft_strdup(s);
	if (!n_str)
		return (0);
	while (s[i])
	{
		n_str[i] = f(i, s[i]);
		i++;
	}
	return (n_str);
}
