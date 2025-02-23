#include "../includes/philo.h"

int	is_philo_dead(t_philo *philo)
{
	bool	is_end;

	is_end = 0;
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
		pthread_mutex_lock(&philo->meal_mutex);
		if (philo->meal_count <= philo->data->max_meals)
		{
			pthread_mutex_unlock(&philo->meal_mutex);
			return (0);
		}
		pthread_mutex_unlock(&philo->meal_mutex);
	}
	return (1);
}

int	check_philos(t_philo *philo)
{
	if (is_philo_full(philo) || is_philo_dead(philo))
		return (1);
	return (0);
}

void	monitoring(t_data *data)
{
	int i;
	long last_meal_backup;

	i = 0;
	while (i < data->philo_nbr)
	{
		pthread_mutex_lock(&data->philos[i].meal_mutex);
		last_meal_backup = get_current_time() - data->philos[i].last_meal_time;
		pthread_mutex_unlock(&data->philos[i].meal_mutex);
		if (last_meal_backup > data->time_to_die)
		{
			pthread_mutex_lock(&data->end_mutex);
			data->end_simulation = true;
			printf(RED"%ld ", (get_current_time() - data->philos->start_time));
			printf("%d died\n"RST, data->philos[i].id);
			pthread_mutex_unlock(&data->end_mutex);
			return ;
		}
		i++;
	}
}

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;

	i = 0;
	data = (t_data *)arg;
	while (1)
	{
		if(check_philos(&data->philos[i]))
			return (NULL);
		monitoring(data);
		usleep(1000);
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