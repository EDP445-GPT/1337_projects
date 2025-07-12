/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaarafi <mmaarafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 19:18:08 by mmaarafi          #+#    #+#             */
/*   Updated: 2024/11/08 10:50:28 by mmaarafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char		x;
	char		y;
	long int	overflow_case;

	if (fd < 0)
		return ;
	overflow_case = n;
	if (overflow_case < 0)
	{
		write(fd, "-", 1);
		overflow_case = -overflow_case;
	}
	if (overflow_case < 10)
	{
		x = overflow_case + '0';
		write(fd, &x, 1);
	}
	else
	{
		ft_putnbr_fd(overflow_case / 10, fd);
		y = (overflow_case % 10) + '0';
		write(fd, &y, 1);
	}
}
