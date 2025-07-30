/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaarafi <mmaarafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:29:56 by mmaarafi          #+#    #+#             */
/*   Updated: 2025/07/28 21:07:09 by mmaarafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

unsigned long	get_time()
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void ft_sleep(unsigned long target, t_philos *philo)
{
	unsigned long time;

	time = get_time();
	while((get_time() - time) < target && check_if_alive(philo))
		usleep(100);
}

void destroy_forks_mutxes(pthread_mutex_t *ptr, t_param *param, t_philos *philos)
{
	int	i;

	i = 0;
	while(i < param->number_of_philos)
	{
		pthread_mutex_destroy(&ptr[i]);
		i++;
	}
	while(i < param->number_of_philos)
	{
		pthread_mutex_destroy(&philos[i].last_meal_mutex);
		pthread_mutex_destroy(&philos[i].meals_eaten_mutex);
		i++;
	}
	pthread_mutex_destroy(&param->all_alive_mutex);
}

pthread_mutex_t *initialize_forks_mutxes(t_param *param)
{
	pthread_mutex_t	*ptr;
	int	i;

	ptr = malloc(sizeof(pthread_mutex_t) * param->number_of_philos);
	i = 0;
	while(i < param->number_of_philos)
	{
		pthread_mutex_init(&ptr[i], NULL);
		i++;
	}
	return (ptr);
}
