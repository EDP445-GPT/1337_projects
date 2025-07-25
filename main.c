#include "header.h"

void philo_activity(t_philosopher *philo, char *str)
{
	printf("%d %d %s\n", (get_time() - philo->param->start), philo->philo_id, str);
}

void ft_sleep(unsigned long target)
{
	unsigned long time;

	time = get_time();
	while(get_time() - time < target)
		usleep(100);
}

void philo_eat(t_philosopher *philo)
{
	int	left_fork;
	int	right_fork;

	left_fork = philo->left_fork;
	right_fork = philo->right_fork;
	pthread_mutex_lock(&philo->param->forks[right_fork]);
		philo_activity(philo, "has taken a fork");
	pthread_mutex_lock(&philo->param->forks[left_fork]);
		philo_activity(philo, "has taken a fork");
	ft_sleep(philo->param->time_to_eat);
	printf();
	pthread_mutex_unlock(&philo->param->forks[right_fork]);
	pthread_mutex_unlock(&philo->param->forks[left_fork]);
}

void *philo_routine(void *ptr)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)ptr;
	if(philo->philo_id % 2 == 0)
		usleep(500);
	while(1)
	{
		philo_activity(philo, "is thinking");
		philo_pick_forks(philo);
		philo_activity(philo, "is eating");
		philo_put_forks(philo);
		philo_activity(philo, "is sleeping");
	}
	return (NULL);
}

unsigned long get_time()
{
	struct timeval	current_meal;

	gettimeofday(&current_meal, NULL);
	return(current_meal.tv_sec * 1000 + current_meal.tv_usec / 1000);
}

void create_philos_threads(t_parameters *ptr)
{
	t_philosopher	philos[ptr->number_of_philosophers];
	struct timeval	current_meal;
	int				i;
	unsigned long	start;

	ptr->forks = initialize_forks_mutxes(ptr);
	gettimeofday(&current_meal, NULL);
	ptr->start = get_time();
	i = 0;
	while(i < ptr->number_of_philosophers)
	{
		philos[i].philo_id = i + 1;
		philos[i].left_fork = i + 1;
		philos[i].right_fork = (((i + 1) - 2 + ptr->number_of_philosophers) % ptr->number_of_philosophers) + 1;
		philos[i].param = ptr;
		philos[i].last_meal = 0;
		philos[i].thread_ret = pthread_create(&philos[i].thread_id, NULL, philo_routine, (void *) &philos[i]);
		i++;
	}
	i = 0;
	while (i < ptr->number_of_philosophers)
	{
		pthread_join(philos[i].thread_id, NULL);
		i++;
	}
}

int main(int ac, char **av)
{
	t_parameters	*param;

	param = malloc(sizeof(t_parameters));
	if (ac == 5 || ac == 6)
	{
		if (!check_parameter(ac, av, param))
			return (0);
		initialize_parameters(ac, av, param);
		create_philos_threads(param);
		// printf("%d\n%d\n%d\n%d\n%d\n", param->number_of_philosophers, param->time_to_die, param->time_to_eat, param->time_to_sleep, param->must_eat);
	}
	return (0);
}
