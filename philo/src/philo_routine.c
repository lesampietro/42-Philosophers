#include "../includes/philo.h"

static void	take_forks(t_philo *philo)
{
	if (philo->left_fork->fork_id < philo->right_fork->fork_id)
	{
		pthread_mutex_lock(&philo->left_fork->fork);
		printf("%ld %d has taken a fork\n", get_elapsed_time(philo->data) / 1000, philo->philo_id);
		pthread_mutex_lock(&philo->right_fork->fork);
		printf("%ld %d has taken a fork\n", get_elapsed_time(philo->data) / 1000, philo->philo_id);
	}
	else
	{
		pthread_mutex_lock(&philo->right_fork->fork);
		printf("%ld %d has taken a fork\n", get_elapsed_time(philo->data) / 1000, philo->philo_id);
		pthread_mutex_lock(&philo->left_fork->fork);
		printf("%ld %d has taken a fork\n", get_elapsed_time(philo->data) / 1000, philo->philo_id);
	}
}

static void	eat(t_philo *philo)
{
	printf("%ld %d is eating\n", get_elapsed_time(philo->data) / 1000, philo->philo_id);
	philo->last_meal_time = get_current_time();
	precise_sleep(philo->data->time_to_eat);
	philo->meal_count++;
	if (philo->data->max_meals != -1 && philo->meal_count >= philo->data->max_meals)
		philo->is_full = true;
	pthread_mutex_unlock(&philo->left_fork->fork);
	pthread_mutex_unlock(&philo->right_fork->fork);
}

static void sleep_n_think(t_philo *philo)
{
	printf("%ld %d is sleeping\n", get_elapsed_time(philo->data) / 1000, philo->philo_id);
	precise_sleep(philo->data->time_to_sleep);
	printf("%ld %d is thinking\n", get_elapsed_time(philo->data) / 1000, philo->philo_id);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->philo_id % 2)
		precise_sleep(1000);
	while (!philo->data->end_simulation && !philo->is_full)
	{
		take_forks(philo);
		eat(philo);
		sleep_n_think(philo);
	}
	return (NULL);
}

void	init_simulation(t_data *data)
{
	int			i;
	pthread_t	monitor_id;

	i = 0;
	if (pthread_create(&monitor_id, NULL, monitor_routine, data))
		error_n_exit("Error: Thread creation failed\n", 0);
	while (i < data->philo_nbr)
	{
		if (pthread_create(&data->philos[i].thread_id, NULL, philosopher_routine, &data->philos[i])) //last parameter passes the address of the philosopher
			error_n_exit("Error: Thread creation failed\n", 0);
		i++;
	}
	if (pthread_join(monitor_id, NULL))
		error_n_exit("Error: Thread joining failed\n", 0);
	i = 0;
	while (i < data->philo_nbr)
	{
		if (pthread_join(data->philos[i].thread_id, NULL))
			error_n_exit("Error: Thread joining failed\n", 0);
		i++;
	}
}
