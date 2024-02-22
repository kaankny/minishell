/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduvan <fduvan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 10:02:49 by fduvan            #+#    #+#             */
/*   Updated: 2023/12/05 12:53:27 by fduvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*sb;

	if (n == 0)
		return ;
	sb = s;
	i = 0;
	while (i < n)
	{
		sb[i] = 0;
		i++;
	}
}
