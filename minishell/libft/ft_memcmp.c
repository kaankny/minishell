/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduvan <fduvan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 11:13:47 by fduvan            #+#    #+#             */
/*   Updated: 2023/12/05 12:54:53 by fduvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1char;
	unsigned char	*s2char;

	if (n == 0)
		return (0);
	s1char = (unsigned char *) s1;
	s2char = (unsigned char *) s2;
	i = 0;
	while (i < n)
	{
		if (s1char[i] != s2char[i])
			return (s1char[i] - s2char[i]);
		i++;
	}
	return (0);
}
