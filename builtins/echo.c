/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutahi <mboutahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 02:20:45 by mboutahi          #+#    #+#             */
/*   Updated: 2025/07/15 02:20:46 by mboutahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	is_valid_flag(char *str)
{
	int	i;

	if (!str)
		return (2);
	if (*str != '-')
		return (-1);
	else
	{
		i = 1;
		while (str[i] == 'n' && str[i])
			i++;
		if (str[i] == 0)
			return (1);
		else
			return (0);
	}
}

void	print_echo(char **str, int i)
{
	while (str[i])
	{
		printf("%s", str[i]);
		if (str[i + 1])
			printf(" ");
		i++;
	}
}

void	ft_echo(char **argument)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (!argument[i])
		printf("\n");
	else
	{
		if ((is_valid_flag(argument[i])) == 1)
			flag = 1;
		while ((is_valid_flag(argument[i])) == 1)
			i++;
		if (flag == 1)
		{
			print_echo(argument, i);
		}
		else if (flag == 0)
		{
			print_echo(argument, i);
			printf("\n");
		}
	}
}
