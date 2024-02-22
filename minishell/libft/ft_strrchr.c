/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduvan <fduvan@student.42kocaeli.com.tr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:51:09 by fduvan            #+#    #+#             */
/*   Updated: 2023/10/09 17:08:45 by fduvan           ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	char	*lastpos;
	int		i;

	lastpos = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			lastpos = (char *)&s[i];
		i++;
	}
	if ((char) c == s[i])
		return ((char *)&s[i]);
	return (lastpos);
}
