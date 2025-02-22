/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaarafi <mmaarafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 15:17:36 by mmaarafi          #+#    #+#             */
/*   Updated: 2025/02/22 09:13:03 by mmaarafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	signal_handler(int sig)
{
	static char	c;
	static int	i;

	c = c << 1;
	if (sig == SIGUSR1)
		c = c | 1;
	if (sig == SIGUSR2)
		c = c | 0;
	i++;
	if (i == 8)
	{
		write(1, &c, 1);
		i = 0;
		c = 0;
	}
}

int	main(void)
{
	pid_t	pid;
	char	*str;

	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	pid = getpid();
	str = ft_itoa(pid);
	write(1, "pid: ", 5);
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	while (1);
		pause();
}
