/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduvan <fduvan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 18:02:53 by fduvan            #+#    #+#             */
/*   Updated: 2023/12/05 13:00:46 by fduvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_find_digit_count(int n)
{
	int			i;

	i = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char		*str_num;
	int			len;
	long		nbr;

	nbr = n;
	len = ft_find_digit_count(nbr);
	if (n < 0)
	{
		len++;
		nbr = -nbr;
	}
	str_num = malloc(len + 1);
	if (!str_num)
		return (0);
	str_num[len] = '\0';
	while (nbr > 0)
	{
		str_num[--len] = nbr % 10 + 48;
		nbr /= 10;
	}
	if (n < 0)
		str_num[0] = '-';
	if (n == 0)
		str_num[0] = '0';
	return (str_num);
}
