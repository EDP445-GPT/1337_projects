/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaarafi <mmaarafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 12:19:13 by mmaarafi          #+#    #+#             */
/*   Updated: 2025/07/30 13:07:20 by mmaarafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdbool.h>

typedef struct s_parameters
{
	int				number_of_philos;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	int				must_eat;
	char			**av;
	int				ac;
	unsigned long	start;
	bool			all_alive;
	pthread_mutex_t	all_alive_mutex;
	pthread_mutex_t	*forks;
	pthread_t		monitor;
}	t_param;

typedef struct s_philos
{
	pthread_mutex_t	last_meal_mutex;
	pthread_t		philos_thread;
	int				id;
	int				left_fork;
	int				right_fork;
	unsigned long	last_meal;
	int				meals_eaten;
	pthread_mutex_t	meals_eaten_mutex;
	t_param			*param;
}	t_philos;

long long		ft_atoi(char *str);
int				is_number(char *str);
int				check_number(char *str);
int				check_parameter(int ac, char **av, t_param *param);
void			initialize_all_variables(t_param *param, int ac, char **av);
void			create_threads(t_param *param);
unsigned long	get_time();
void			ft_sleep(unsigned long target, t_philos *philo);
void			destroy_forks_mutxes(pthread_mutex_t *ptr, t_param *param, t_philos *philos);
pthread_mutex_t	*initialize_forks_mutxes(t_param *param);
int				check_if_alive(t_philos *philo);

#endif