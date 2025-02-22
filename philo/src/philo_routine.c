#include "../includes/philo.h"

static void	take_forks(t_philo *philo)
{
	if (philo->left_fork->fork_id < philo->right_fork->fork_id)
	{
		pthread_mutex_lock(&philo->left_fork->fork);
		safe_print(philo->data, philo->philo_id, "has taken a fork");
		pthread_mutex_lock(&philo->right_fork->fork);
		safe_print(philo->data, philo->philo_id, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->right_fork->fork);
		safe_print(philo->data, philo->philo_id, "has taken a fork");
		pthread_mutex_lock(&philo->left_fork->fork);
		safe_print(philo->data, philo->philo_id, "has taken a fork");
	}
}

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meal_mutex); //the thread that locks the mutex is the only one that can unlock it, and access any line of code between the lock and unlock lines;
	philo->last_meal_time = get_current_time();
	safe_print(philo->data, philo->philo_id, "is eating");
	philo->meal_count++;
	if (philo->data->max_meals != -1 && philo->meal_count >= philo->data->max_meals)
		philo->is_full = true;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	precise_sleep(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->left_fork->fork);
	pthread_mutex_unlock(&philo->right_fork->fork);
}

static void sleep_n_think(t_philo *philo)
{
	safe_print(philo->data, philo->philo_id, "is sleeping");
	precise_sleep(philo->data->time_to_sleep);
	safe_print(philo->data, philo->philo_id, "is thinking");
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg; //just a type casting, because the argument passed is void pointer
	if (philo->philo_id % 2)
		precise_sleep(1000);
	while (!is_simulation_end(philo->data))
	{
		take_forks(philo);
		eat(philo);
		sleep_n_think(philo);
	}
	return (NULL);
}

void	start_dinner(t_data *data)
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
