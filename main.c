#include "header.h"

void philo_thinking(t_philosopher *philo)
{
	int time;
	struct timeval current_time;
	
	gettimeofday(&current_time, NULL);
	time = current_time.tv_usec - philo->last_meal;
	printf("%d %d is thinking\n", time / 1000, philo->philo_id);
}

// void philo_eating(t_philosopher *philo)
// {
// 	int time;
// 	struct timeval current_time;
	
// 	gettimeofday(&current_time, NULL);
// 	time = current_time.tv_usec - philo->last_meal;
// 	printf("%d %d iseating\n", time / 1000, philo->philo_id);
// }

void print_philo_picked_fork(t_philosopher *philo)
{
	int				time;
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	time = current_time.tv_usec - philo->last_meal;
	printf("%d %d has taken a fork\n", time / 1000, philo->philo_id);
}

void philo_pick_forks(t_philosopher *philo)
{
	int	left_fork;
	int	right_fork;

	left_fork = philo->left_fork;
	right_fork = philo->right_fork;
	pthread_mutex_lock(&philo->param->forks[right_fork]);
		print_philo_picked_fork(philo);
	pthread_mutex_lock(&philo->param->forks[left_fork]);
		print_philo_picked_fork(philo);
}

void *philo_routine(void *ptr)
{
	t_philosopher	*philo;
	int				i;

	i = 0;
	philo = (t_philosopher *)ptr;
	if(philo->philo_id % 2 == 0)
		usleep(1000);
	while(1)
	{
		philo_thinking(philo);
		philo_pick_forks(philo);
		i++;
	}
	return (NULL);
}

void create_philos_threads(t_parameters *ptr)
{
	t_philosopher	philos[ptr->number_of_philosophers];
	struct timeval	current_meal;
	int				i;
	int				last_meal;

	ptr->forks = initialize_forks_mutxes(ptr);
	gettimeofday(&current_meal, NULL);
	last_meal = current_meal.tv_usec;
	i = 0;
	while(i < ptr->number_of_philosophers)
	{
		philos[i].philo_id = i + 1;
		philos[i].left_fork = i + 1;
		philos[i].right_fork = (((i + 1) - 2 + ptr->number_of_philosophers) % ptr->number_of_philosophers) + 1;
		philos[i].last_meal = last_meal;
		philos[i].param = ptr;
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
