/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduvan <fduvan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:57:42 by fduvan            #+#    #+#             */
/*   Updated: 2023/12/05 12:55:10 by fduvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*bn;

	bn = (unsigned char *) b;
	i = 0;
	while (i < len)
	{
		bn[i] = (unsigned char) c;
		i++;
	}
	return (b);
}
