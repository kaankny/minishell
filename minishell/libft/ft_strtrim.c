/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduvan <fduvan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:28:02 by fduvan            #+#    #+#             */
/*   Updated: 2023/12/05 12:57:53 by fduvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_check_set(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		len;
	char	*n_arr;

	len = ft_strlen(s1);
	if (len <= 0)
		return (ft_strdup(""));
	while (ft_check_set(s1[len - 1], set))
	{
		len--;
	}
	while (ft_check_set(*s1, set) && len != 0)
	{
		len--;
		s1++;
	}
	n_arr = malloc(len + 1);
	if (n_arr == 0)
		return (0);
	ft_memcpy(n_arr, s1, len);
	n_arr[len] = '\0';
	return (n_arr);
}
