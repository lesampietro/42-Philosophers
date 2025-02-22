#include "../includes/philo.h"

static void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->left_fork->fork);
		safe_print(philo->data, philo->id, "has taken a fork");
		pthread_mutex_lock(&philo->right_fork->fork);
		safe_print(philo->data, philo->id, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->right_fork->fork);
		safe_print(philo->data, philo->id, "has taken a fork");
		pthread_mutex_lock(&philo->left_fork->fork);
		safe_print(philo->data, philo->id, "has taken a fork");
	}
}

void	drop_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->left_fork->fork);
		pthread_mutex_unlock(&philo->right_fork->fork);
	}
	else
	{
		pthread_mutex_unlock(&philo->right_fork->fork);
		pthread_mutex_unlock(&philo->left_fork->fork);
	}
}

static void	eat(t_philo *philo)
{
	if (philo->data->max_meals != -1)
		philo->meal_count++;
	pthread_mutex_lock(&philo->meal_mutex); //the thread that locks the mutex is the only one that can unlock it, and access any line of code between the lock and unlock lines;
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&philo->meal_mutex);
	safe_print(philo->data, philo->id, "is eating");
	// if (philo->data->max_meals != -1 && philo->meal_count >= philo->data->max_meals)
	// 	philo->is_full = true;
	precise_sleep(philo->data->time_to_eat);
	drop_forks(philo);
}

static void sleep_n_think(t_philo *philo)
{
	safe_print(philo->data, philo->id, "is sleeping");
	precise_sleep(philo->data->time_to_sleep);
	safe_print(philo->data, philo->id, "is thinking");
	usleep(100);
}

void	*philosopher_routine(void *arg)
{
	int			i;
	t_philo		*philo;
	static void	(*f[3])(t_philo *) = {take_forks, eat, sleep_n_think};

	i = 0;
	philo = (t_philo *)arg; //just a type casting, because the argument passed is void pointer
	while (check_philos(philo))
	{
		f[i++](philo);
		if (i == 3)
			i = 0;
	}
	// if (i == 1)
	// 	drop_forks(philo);
	return (NULL);
}

void	*one_philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->left_fork->fork);
	safe_print(philo->data, philo->id, "has taken a fork");
	precise_sleep(philo->data->time_to_die);
	pthread_mutex_unlock(&philo->left_fork->fork);
	return (NULL);
}

// void	start_dinner(t_data *data)
// {
// 	int			i;
// 	// pthread_t	monitor_id;

// 	i = 0;
// 	// if (pthread_create(&monitor_id, NULL, &monitor_routine, data))
// 	// 	error_n_exit("Error: Monitor thread creation failed\n", 0, data);
// 	while (i < data->philo_nbr)
// 	{
// 		if (pthread_create(&data->philos[i].tid, NULL, &philosopher_routine, &data->philos[i])) //last parameter passes the address of the philosopher
// 			error_n_exit("Error: Thread creation failed\n", 0, data);
// 		i++;
// 	}
// 	// i = 0;
// 	// while (i < data->philo_nbr)
// 	// {
// 	// 	if (pthread_join(data->philos[i].tid, NULL))
// 	// 		error_n_exit("Error: Thread joining failed\n", 0, data);
// 	// 	i++;
// 	// }
// }
