/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaarafi <mmaarafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 15:15:27 by mmaarafi          #+#    #+#             */
/*   Updated: 2025/02/02 16:17:17 by mmaarafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	signal_sender(int pid, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 7;
	while (str[i])
	{
		while (j >= 0)
		{
			if (((str[i] >> j) & 1) == 1)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			usleep(100);
			j--;
		}
		j = 7;
		i++;
	}
}
#include <stdio.h>

int	main(int ac, char **av)
{
	int	pid;

	if(ac == 3)
	{
		printf("this is ac%d", ac);
		pid = ft_atoi(av[1]);
		signal_sender(pid, av[2]);
	}
	return (0);
}
