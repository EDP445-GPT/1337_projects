/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaarafi <mmaarafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:13:31 by mmaarafi          #+#    #+#             */
/*   Updated: 2024/12/13 10:47:00 by mmaarafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	fun1(long int nb)
{
	char	x;
	int		bytes_written;

	bytes_written = 0;
	if (nb < 0)
	{
		write(1, "-", 1);
		bytes_written++;
		nb = -nb;
	}
	if (nb < 10)
	{
		x = nb + '0';
		write(1, &x, 1);
		bytes_written++;
	}
	else
	{
		bytes_written += fun1(nb / 10);
		x = (nb % 10) + '0';
		write(1, &x, 1);
		bytes_written++;
	}
	return (bytes_written);
}
