/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaarafi <mmaarafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:59:37 by mmaarafi          #+#    #+#             */
/*   Updated: 2025/02/06 17:22:24 by mmaarafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

long long	ft_atoi(const char *str)
{
	long long	result;
	int			sign;

	sign = 1;
	result = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str++ == '-')
			sign = sign * -1;
	}
	while (*str >= '0' && *str <= '9')
	{
		if (result > (LONG_MAX - *str - '0') / 10)
		{
			if (sign == 1)
				return (-1);
			else
				return (0);
		}
		result = result * 10 + *str++ - '0';
	}
	return (result * sign);
}
