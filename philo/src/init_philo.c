#include "../includes/philo.h"

static void	assign_forks_to_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nbr)
	{
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->philo_nbr];
		i++;
	}
}

static void	init_philosophers(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->philo_nbr);
	if (!data->philos)
		error_n_exit("Error: Philo memory allocation failed\n", 0);
	i = 0;
	while (i < data->philo_nbr)
	{
		data->philos[i].philo_id = i + 1;
		data->philos[i].last_meal_time = 0;
		data->philos[i].meal_count = 0;
		data->philos[i].is_full = false;
		data->philos[i].data = data;
		i++;
	}
}

static void	init_forks(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(t_fork) * data->philo_nbr);
	if (!data->forks)
		error_n_exit("Error: Fork memory allocation failed\n", 0);
	i = 0;
	while (i < data->philo_nbr)
	{
		if (pthread_mutex_init(&data->forks[i].fork, NULL))
			error_n_exit("Error: Mutex attribution failed\n", 0);
		data->forks[i].fork_id = i;
		i++;
	}
}

void	init_philo(t_data *data)
{
	struct	timeval tv;

	init_forks(data);
	init_philosophers(data);
	assign_forks_to_philos(data);
	if (gettimeofday(&tv, NULL))
		error_n_exit("Error: not able to get start time\n", 0);
	data->start_time = tv.tv_sec * 1e6 + tv.tv_usec;
}