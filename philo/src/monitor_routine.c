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
		if (philo->meal_count < philo->data->max_meals)
		{
			pthread_mutex_unlock(&philo->meal_mutex);
			return (0);
		}
		pthread_mutex_unlock(&philo->meal_mutex);
	}
	pthread_mutex_lock(&philo->data->end_mutex);
	philo->data->all_full++;
	pthread_mutex_unlock(&philo->data->end_mutex);
	return (1);
}

int monitoring_philo_full(t_philo *philo)
{
	if (philo->data->max_meals == -1)
		return (0);
	else
	{
		pthread_mutex_lock(&philo->meal_mutex);
		if (philo->meal_count < philo->data->max_meals)
		{
			pthread_mutex_unlock(&philo->meal_mutex);
			return (0);
		}
		pthread_mutex_unlock(&philo->meal_mutex);
	}
	return (1);
}

int	check_all_full(t_data *data)
{
	pthread_mutex_lock(&data->end_mutex);
	if (data->all_full == data->philo_nbr)
	{
		data->end_simulation = true;
		pthread_mutex_unlock(&data->end_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->end_mutex);
	return (0);
}

int	check_philos(t_philo *philo)
{
	if (is_philo_full(philo) || is_philo_dead(philo))
		return (1);
	return (0);
}

static void	monitor_death(t_data *data)
{
	int		i;
	long	current_time;
	long	last_meal_backup;

	i = 0;
	while (i < data->philo_nbr)
	{
		pthread_mutex_lock(&data->philos[i].meal_mutex);
		last_meal_backup = get_current_time() - data->philos[i].last_meal_time;
		pthread_mutex_unlock(&data->philos[i].meal_mutex);
		if (last_meal_backup > data->time_to_die && !monitoring_philo_full(&data->philos[i]))
		{
			pthread_mutex_lock(&data->end_mutex);
			data->end_simulation = true;
			current_time = get_current_time() - data->philos[i].start_time;
			printf(RED"%ld ", current_time);
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
		if (check_all_full(data) \
			|| is_philo_dead(&data->philos[i]))
			return (NULL);
		monitor_death(data);
		usleep(200);
		i++;
		if (i == data->philo_nbr)
			i = 0;
		if (data->end_simulation)
			return (NULL);
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