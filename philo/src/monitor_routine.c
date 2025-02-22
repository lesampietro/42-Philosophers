#include "../includes/philo.h"

bool	is_simulation_end(t_data *data)
{
	bool is_end;

	pthread_mutex_lock(&data->end_mutex);
	is_end = data->end_simulation;
	pthread_mutex_unlock(&data->end_mutex);
	return (is_end);
}

void	check_simulation_end(t_data *data)
{
	pthread_mutex_lock(&data->end_mutex);
	data->end_simulation = true;
	pthread_mutex_unlock(&data->end_mutex);
}

static bool	is_philo_dead(t_philo *philo)
{
	long	time_since_meal;

	pthread_mutex_lock(&philo->data->meal_mutex);
	time_since_meal = get_time_since_last_meal(philo);
	pthread_mutex_unlock(&philo->data->meal_mutex);
	if (time_since_meal > philo->data->time_to_die)
	{
		check_simulation_end(philo->data);
		safe_print(philo->data, philo->philo_id, RED"died"RST);
		return (true);
	}
	return (false);
}

static bool	is_philo_full(t_data *data)
{
	int		i;
	bool	all_full;

	i = 0;
	all_full = true;
	pthread_mutex_lock(&data->meal_mutex);
	while (i < data->philo_nbr)
	{
		if (!data->philos[i].is_full)
		{
			all_full = false;
			break ;
		}
		i++;
	}
	pthread_mutex_unlock(&data->meal_mutex);
	if (all_full)
		check_simulation_end(data);
	return (all_full);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (!data->end_simulation)
	{
		i = 0;
		while (i < data->philo_nbr)
		{
			if (is_philo_dead(&data->philos[i]))
				return (NULL);
			i++;
		}
		if (data->max_meals != -1)
		{
			if (is_philo_full(data))
				return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
