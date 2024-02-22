/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkanyilm <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:10:51 by fduvan            #+#    #+#             */
/*   Updated: 2024/02/13 18:44:10 by kkanyilm         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	set_default_fd(int original_fd, int original_fd_in)
{
	dup2(original_fd, 1);
	dup2(original_fd_in, 0);
	close(original_fd);
	close(original_fd_in);
}
