/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaarafi <mmaarafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 12:27:47 by mmaarafi          #+#    #+#             */
/*   Updated: 2025/07/30 14:34:06 by mmaarafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int check_if_alive(t_philos *philo)
{
	int return_value;

	pthread_mutex_lock(&philo->param->all_alive_mutex);
	return_value = philo->param->all_alive;
	pthread_mutex_unlock(&philo->param->all_alive_mutex);
	return (return_value);
}

void action_print(t_philos *philo, char *str)
{
	pthread_mutex_lock(&philo->param->all_alive_mutex);
	if (philo->param->all_alive)
		printf("%lu %d %s\n", (get_time() - philo->param->start), philo->id, str);
	pthread_mutex_unlock(&philo->param->all_alive_mutex);
}

void philo_think(t_philos *philo)
{
	action_print(philo, "is thinking");
}

void philo_eat(t_philos *philo)
{
	int	left_fork;
	int	right_fork;

	left_fork = philo->left_fork;
	right_fork = philo->right_fork;
	pthread_mutex_lock(&philo->param->forks[left_fork]);
	action_print(philo, "has taken a fork");
	pthread_mutex_lock(&philo->param->forks[right_fork]);
	action_print(philo, "has taken a fork");
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->last_meal_mutex);
	action_print(philo, "is eating");
	ft_sleep(philo->param->time_to_eat, philo);
	pthread_mutex_unlock(&philo->param->forks[left_fork]);
	pthread_mutex_unlock(&philo->param->forks[right_fork]);
}

void philo_sleep(t_philos *philo)
{
	action_print(philo, "is sleeping");
	ft_sleep(philo->param->time_to_sleep, philo);
}

void *monitor(void *ptr)
{
	t_philos *philos;
	int i;
	unsigned long last_meal;
	unsigned long last_meal_time_difference;
	int philo_count;

	philos = (t_philos *)ptr;
	while (1)
	{
		i = 0;
		philo_count = 0;
		
		while (i < philos->param->number_of_philos)
		{
			pthread_mutex_lock(&philos[i].meals_eaten_mutex);
			if (philos->param->must_eat != -1 && philos[i].meals_eaten >= philos->param->must_eat) 
			{
				pthread_mutex_unlock(&philos[i].meals_eaten_mutex); 
				philo_count++;
				i++;
				continue;
			} 
			pthread_mutex_unlock(&philos[i].meals_eaten_mutex);
			pthread_mutex_lock(&philos[i].last_meal_mutex);
			last_meal = philos[i].last_meal;
			pthread_mutex_unlock(&philos[i].last_meal_mutex);
			last_meal_time_difference = get_time() - last_meal;
			
			if (last_meal_time_difference >= philos->param->time_to_die)
			{
				pthread_mutex_lock(&philos->param->all_alive_mutex);
				philos->param->all_alive = false;
				pthread_mutex_unlock(&philos->param->all_alive_mutex);
				printf("%lu %d died\n", (get_time() - philos[i].param->start), philos[i].id);
				return (NULL);
			}
			i++;
		}
		if (philos->param->must_eat != -1 && philo_count == philos->param->number_of_philos)
			return (NULL);
	}
	return (NULL);
}

void *philos_routine(void *ptr)
{
	t_philos *philo;

	philo = (t_philos *)ptr;
	if (philo->id % 2 == 0)
		usleep(500);
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->last_meal_mutex);
	while (check_if_alive(philo))
	{
		philo_think(philo);
		philo_eat(philo);
		philo_sleep(philo);
		
		pthread_mutex_lock(&philo->meals_eaten_mutex);
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->meals_eaten_mutex);
		if (philo->param->must_eat != -1 && philo->meals_eaten >= philo->param->must_eat)
			return (NULL);
	}
	return (NULL);
}

void sleep_1(unsigned long target)
{
	unsigned long time;

	time = get_time();
	while((get_time() - time) < target)
		usleep(100);
}

void create_threads(t_param *param)
{
	t_philos philos[param->number_of_philos];
	int i;

	philos->param = param;
	i = 0;
	param->forks = initialize_forks_mutxes(param);
	while (i < param->number_of_philos)
	{
		pthread_mutex_init(&philos[i].last_meal_mutex, NULL);
		pthread_mutex_init(&philos[i].meals_eaten_mutex, NULL);
		philos[i].id = i + 1;
		philos[i].left_fork = i;
		philos[i].right_fork = (i + 1) % param->number_of_philos;
		philos[i].param = param;
		philos[i].last_meal = param->start;
		philos[i].meals_eaten = 0;
		i++;
	}
	if (param->number_of_philos == 1)
	{
		printf("%lu %d %s\n", (get_time() - param->start), 1, "has taken a fork");
		sleep_1(param->time_to_die);
		printf("%lu %d %s\n", (get_time() - param->start), 1, "died");
		return ;
	}
	pthread_create(&param->monitor, NULL, monitor, (void *)&philos);
	i = -1;
	while (++i < param->number_of_philos)
		pthread_create(&philos[i].philos_thread, NULL, philos_routine, (void *)&philos[i]);
	i = -1;
	pthread_join(param->monitor, NULL);
	while (++i < param->number_of_philos)
		pthread_join(philos[i].philos_thread, NULL);
	destroy_forks_mutxes(param->forks, param, philos);
}
