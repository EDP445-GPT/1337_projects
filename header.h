#ifndef HEADER_H
#define HEADER_H

#include "includes/libft/libft.h"
#include <sys/time.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

typedef struct s_parameters
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				ac;
	char			**av;
	pthread_mutex_t	*forks;
}	t_parameters;

typedef struct s_philosopher
{
	int				philo_id;
	int				thread_ret;
	int				left_fork;
	int				right_fork;
	int				last_meal;
	pthread_t		thread_id;
	t_parameters	*param;
}	t_philosopher;

void initialize_parameters(int ac, char **av, t_parameters *param);
int	check_parameter(int ac, char **av, t_parameters *param);
pthread_mutex_t *destroy_forks_mutxes(pthread_mutex_t *ptr, t_parameters *param);
pthread_mutex_t *initialize_forks_mutxes(t_parameters *param);

#endif