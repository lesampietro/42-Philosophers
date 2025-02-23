#include "../includes/philo.h"

static void	assign_forks_to_philos(t_data *data, int philo_id)
{
	data->philos[philo_id].left_fork = &data->forks[philo_id];
	if (data->philo_nbr > 1)
		data->philos[philo_id].right_fork = &data->forks[(philo_id + 1) % data->philo_nbr];
}

static void	init_philosophers(t_data *data)
{
	int	i;

	i = 0;
	data->philos = malloc(sizeof(t_philo) * data->philo_nbr);
	memset(data->philos, 0, sizeof(t_philo) * data->philo_nbr);
	while (i < data->philo_nbr)
	{
		pthread_mutex_init(&data->philos[i].meal_mutex, NULL);
		data->philos[i].id = i + 1;
		data->philos[i].data = data;
		data->philos[i].meal_count = 0;
		data->philos[i].last_meal_time = get_current_time();
		data->philos[i].start_time = data->philos[i].last_meal_time;
		assign_forks_to_philos(data, i);
		if (data->philo_nbr == 1)
			pthread_create(&data->philos[i].tid, NULL, &one_philo_routine, &data->philos[i]);
		else
		{
			pthread_create(&data->philos[i].tid, NULL, &philosopher_routine, &data->philos[i]);
		}
		i++;
	}
}

static void	init_forks(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(t_fork) * data->philo_nbr);
	memset(data->forks, 0, sizeof(t_fork) * data->philo_nbr);
	i = 0;
	while (i < data->philo_nbr)
	{
		if (pthread_mutex_init(&data->forks[i].fork, NULL))
			error_n_exit("Error: Fork init failed\n", 0, data);
		data->forks[i].fork_id = i;
		i++;
	}
}

void	init_philos(t_data *data)
{
	if(pthread_mutex_init(&data->end_mutex, NULL) \
		|| pthread_mutex_init(&data->print_mutex, NULL))
		error_n_exit("Error: Mutex protection init failed\n", 0, data);
	init_forks(data);
	init_philosophers(data);
}