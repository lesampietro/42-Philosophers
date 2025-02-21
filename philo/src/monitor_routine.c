#include "../includes/philo.h"

static bool	is_philo_dead(t_philo *philo)
{
	long	time_since_meal;

	time_since_meal = get_time_since_last_meal(philo);
	if (time_since_meal > philo->data->time_to_die)
	{
		philo->data->end_simulation = true;
		printf(BLU"%ld %d died\n"RST, get_elapsed_time(philo->data) / 1000, philo->philo_id);
		return (true);
	}
	return (false);
}

static bool	is_philo_full(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nbr)
	{
		if (!data->philos[i].is_full)
			return (false);
		i++;
	}
	data->end_simulation = true;
	return (true);
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
