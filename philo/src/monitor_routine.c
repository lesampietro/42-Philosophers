#include "../includes/philo.h"

int	is_philo_dead(t_philo *philo)
{
	int is_end;

	pthread_mutex_lock(&philo->data->end_mutex);
	is_end = philo->data->end_simulation;
	pthread_mutex_unlock(&philo->data->end_mutex);
	return (is_end);
}

int	is_philo_full(t_philo *philo)
{
	if (philo->data->max_meals == -1)
		return (0);
	else
	{
		if (philo->meal_count < philo->data->max_meals)
			return (0);
	}
	return (1);
}

int	check_philos(t_philo *philo)
{
	if (is_philo_full(philo) || is_philo_dead(philo))
		return (1);
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;
	long	last_meal_backup;

	i = 0;
	data = (t_data *)arg;
	while (i < data->philo_nbr)
	{
		// if(!check_philos(&data->philos[i]))
		// 	continue;
		// printf("philo %d died\n", data->philos[i].id);
		// safe_print(data, data->philos[i].id, "died");
		pthread_mutex_lock(&data->philos[i].meal_mutex);
		last_meal_backup = (long)(get_current_time - data->philos[i].last_meal_time);
		pthread_mutex_unlock(&data->philos[i].meal_mutex);
		if (last_meal_backup > data->time_to_die)
		{
			pthread_mutex_lock(&data->end_mutex);
			data->end_simulation = true;
			pthread_mutex_unlock(&data->end_mutex);
			safe_print(data, data->philos[i].id, "died");
			return (NULL);
		}
		i++;
	}
	return (NULL);
}

void	init_monitor(t_data *data)
{
	pthread_t	monitor_id;

	if (pthread_create(&monitor_id, NULL, &monitor_routine, data))
		error_n_exit("Error: Thread creation failed\n", 0, data);
	pthread_join(monitor_id, NULL);
}