/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaarafi <mmaarafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:14:16 by mmaarafi          #+#    #+#             */
/*   Updated: 2024/12/13 10:35:03 by mmaarafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (*(str + i) != '\0')
	{
		i++;
	}
	return (i);
}

int	base_correctness(char *base)
{
	int	i;
	int	j;

	i = 0;
	if (base == NULL || ft_strlen(base) == 1)
		return (0);
	i = 0;
	j = 0;
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-' || base[i] <= 32 || base[i] == 127)
			return (0);
		if (base[i] >= 9 && base[i] <= 13)
			return (0);
		while (base[i + j + 1])
		{
			if (base[i] == base[i + j + 1])
				return (0);
			j++;
		}
		j = 0;
		i++;
	}
	return (i);
}

int	fun(unsigned long nbr, char *base)
{
	unsigned long	overflow_case;
	int				bytes_written;

	bytes_written = 0;
	overflow_case = nbr;
	if (overflow_case < 0)
	{
		write(1, "-", 1);
		bytes_written++;
		overflow_case = -overflow_case;
	}
	if (overflow_case < 16)
	{
		write(1, &base[overflow_case], 1);
		bytes_written++;
	}
	else
	{
		bytes_written += fun(overflow_case / 16, base);
		write(1, &base[overflow_case % 16], 1);
		bytes_written++;
	}
	return (bytes_written);
}
